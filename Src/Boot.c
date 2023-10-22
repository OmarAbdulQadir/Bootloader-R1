/*
 * Boot.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Omar Abdul Qadir
 *      Release: 1
 *      Vesrion: 1.2
 */

#include "../Inc/Boot.h"

// Variable for bootloader intialization and version
static u8 BootStarting[16] = "Bootloader R V.\n";
static u8 APPStarting[16] = "Application R V.";
static u8 BootVersion[4] = {0x80, 0x01, 0x01, 0x00};
// Variable for application versiona and update request
static u8 AppVersion[5] = { 0 };
// Recived frame buffer
static u8 RxFrameBuffer[FRAME_MAX_LENGTH] = { 0 };
static u8 RxFrameIndex = ST_BYTE;
static u8 RxFrame_Ready = STD_FALSE;
static u8 RxPageNo = 0;

// EEPROM Locations identifier
enum
{
	Boot_indecator,				// Indicator for the bootloader first run
	Boot_release,				// Bootloader release
	Boot_version,				// Bootloader version
	Boot_subversion,			// Bootloader sub-version
	App_indecator,				// Indicator for the application exsitance
	App_release,				// Application release
	App_version,				// Application version
	App_subversion,				// Application sub-version
	App_updateReq				// Update request indicator
}Boot_varsion_loc;

// UDS Service codes and system modes
enum
{
	Waiting_Session_Control = 0x00,
	Diagnostic_Session_Control= 0x10,
	Programming_Session= 0x03,
	Request_Download= 0x34,
	Request_Upload= 0x35,
	Transfer_Data= 0x36,
	Transfer_Exit= 0x37
};

// Mode Control variables
static u8 CurrentMode = Waiting_Session_Control;

void Boot_init( void )
{
	// EEP data container
	u8 EEP_Data = 0;
	// Initialize UART for flashing
	UART_vInit();
	#if USE_INT==1
	// Set the uart callback function
	UART_vSetRxCallback(Boot_vRxCallback);
	// Relocate the vector table
	GI_vRelocateIVT(IVT_BLD);
	// Enable the global interrupt
	GI_Enable();
	#else
	// Disable interrupt
	GI_Disable();
	#endif
	// Get the indicator value for the bootloader first run
	EEP_vReadByte(Boot_indecator, &EEP_Data);
	// Check if its the first run for the booleader
	if(EEP_Data == BootVersion[0])
	{// If not the first run
		// Print the bootloader release and version
		for(u8 i= 0; i< 16;i++)
		{
			UART_vSendByte(BootStarting[i]);
			if(i == 11)
			{
				// Release
				EEP_vReadByte(Boot_release, &EEP_Data);
				UART_vSendByte(EEP_Data+'0');
			}
			else if(i == 13)
			{
				// Version
				EEP_vReadByte(Boot_version, &EEP_Data);
				UART_vSendByte(EEP_Data+'0');
			}
			else if(i == 14)
			{
				// Sub version
				EEP_vReadByte(Boot_subversion, &EEP_Data);
				UART_vSendByte(EEP_Data+'0');
			}
		}
	}
	else
	{// If its the first run
		// Save the Bootloader release and version data
		for(u8 i= 0; i<= 3; i++)
		{
			EEP_vWriteByte(i, BootVersion[i]);
		}
		// Reset the system
		WDT_void_start(time16_3_ms);
		while(1);
	}

	// get tht indicator value for application exsitance
	for(u8 i= 0; i< 5; i++)
	{
		EEP_vReadByte(App_indecator+i, &AppVersion[i]);
	}

	// Check if there is an application || Check if there is an update request
	// Nither the application exsit nor there is an update request >> Systems intial state
	//															Wait for flashing
	// There is an application an application and no update request >> Jump to the application
	// There is an no application and there an update request >> Systems Fault return to
	//															initial state wait for flashing
	// There is an application and update request >> Reply to the request and start flashing
	if( (AppVersion[0] == 0x55) && (AppVersion[4] != 0xAA))
	{// If no flashing will happen
		// Disable the global interrupt and relocate the vector table to the application section
		// Print the bootloader release and version
		for(u8 i= 0; i< 16;i++)
		{
			UART_vSendByte(APPStarting[i]);
			if(i == 12)
			{
				// Release
				UART_vSendByte(AppVersion[1]+'0');
			}
			else if(i == 14)
			{
				// Version
				UART_vSendByte(AppVersion[2]+'0');
			}
			else if(i == 15)
			{
				// Sub version
				UART_vSendByte(AppVersion[3]+'0');
			}
		}
		#if USE_INT==1
		GI_Disable();
		GI_vRelocateIVT(IVT_APP);
		#endif
		// Jump to the application
		asm("jmp 0");
	}
	else
	{// If flashing will happen
		// Continue to the bootloader
	}
}


u8 Boot_vProgramPage(u8 copy_u8PageID, u8* ptr_u8DataBuffer)
{
	// Validate the page ID to avoid over-writing the Bootloader
	if( copy_u8PageID < MAX_PAGE_ID )
	{
		u16 word;					// Create the word container
		u32 u32PageAddress;			// Create the Page address container
		// Compute the starting adress of the page
		u32PageAddress = copy_u8PageID * PAGE_SIZE;

		// Erase the current page before flashing
	    boot_page_erase_safe(u32PageAddress);

	    // Fill the temporary page buffer
	    for (u8 i= ST_BYTE; i< PAGE_SIZE; i+=WORD_SIZE)
	    {
	        // Set up little-endian word.
	    	word = *ptr_u8DataBuffer++;
	    	word += (*ptr_u8DataBuffer++) << 8;
	        boot_page_fill_safe(u32PageAddress + i, word);
	    }
	    // Store buffer in flash page.
	    boot_page_write_safe(u32PageAddress);

	    // Reenable RWW-section again.
	    boot_rww_enable_safe();
	    // Return Successs
	    return STD_TRUE;
	}
	else
	{
		// Return Failed
		return STD_FALSE;
	}
}


void Boot_vRxCallback( u8 Copy_u8RxByte )
{
	static u8 RxFrameLength= ST_BYTE;
	// If the frame length and frame index both equals 0
	if( (RxFrameIndex == ST_BYTE) && (RxFrameLength == ST_BYTE) )
	{// then its the frame size byte
		if(Copy_u8RxByte <= FRAME_MAX_LENGTH)
		{
			// Save the size in the frame size variable
			RxFrameLength = Copy_u8RxByte;
		}
		else
		{
			// Send NG_response
			UART_vSendByte(NEG_RESPONSE);
		}
	}
	// Check if the counting index equal the frame lenght
	else if( RxFrameLength > RxFrameIndex )
	{// then save the recived byte
		RxFrameBuffer[RxFrameIndex++] = Copy_u8RxByte;
		// Check if this byte is the last in the frame
		if( RxFrameLength == RxFrameIndex )
		{// If true
			// Set Frame ready indecator
			RxFrame_Ready = STD_TRUE;
			// Reset the frame length
			RxFrameLength = ST_BYTE;
			/*
			for(u8 i= 0; i< RxFrameIndex; i++)
			{
				UART_vSendByte(RxFrameBuffer[i]);
			}
			*/
		}
		else
		{
			// Do nothing
		}
	}
	else
	{// Wrong situation
		// Send repeate
		UART_vSendByte(REPEATE_FRAME);
		// Reset the frame
		RxFrameLength = ST_BYTE;
		RxFrameIndex = ST_BYTE;
	}
}

/*
Service ID (hex)	Service	Description
0x10				Diagnostic Session Control		>1B>		Programming session ID: 03
0x34				Request Download				>4B>		Code Info: Release, Version, Sub-version, Size
0x35				Request Upload
0x36				Transfer Data					>1B>		Code Info: Size
0x37				Transfer Exit
*/

u8 Boot_vMainTask( void )
{
	static u8 PageIndex = 0;
	if(RxFrame_Ready == STD_TRUE)
	{
		// Check the current mode for the system
		if(CurrentMode == Waiting_Session_Control)
		{// In Waiting session control mode
			// Check if the received frame is Diagnostic mode frame??
			if(RxFrameBuffer[SERVICE_ID] == Diagnostic_Session_Control)
			{// If true
				// Check if there is prograamming session request??
				if(RxFrameBuffer[SESSION_CONTROL_CODE] == Programming_Session)
				{// If True
					// Transmit the system mode to Programming session
					CurrentMode = Programming_Session;
					// Send postive response
					UART_vSendByte((Diagnostic_Session_Control+POS_RESPONSE));
				}
				else
				{// Wrong session ID
					// NG response
					UART_vSendByte(NEG_RESPONSE);
				}
			}
			else
			{// Wrong service ID
				// NG response
				UART_vSendByte(NEG_RESPONSE);
			}
		}
		else if(CurrentMode == Programming_Session)
		{// In diagnostic session control mode
			// Check if the received frame Uploade or Download request
			if(RxFrameBuffer[SERVICE_ID] == Request_Download)
			{// Download request
				if((RxFrameBuffer[CODE_SIZE_PAGES] <= MAX_PAGE_ID) && (RxFrameBuffer[CODE_SIZE_PAGES] > 0))
				{
					// Save the code size
					RxPageNo = RxFrameBuffer[CODE_SIZE_PAGES];
					// Update the App info in the EEP-Rom
					EEP_vWriteByte(App_indecator, 0x55);
					EEP_vWriteByte(App_release, RxFrameBuffer[CODE_RELEASE]);
					EEP_vWriteByte(App_version, RxFrameBuffer[CODE_VERSION]);
					EEP_vWriteByte(App_subversion, RxFrameBuffer[CODE_SUB_VERSION]);
					// Transmit the system mode to Programming session
					CurrentMode = Request_Download;
					// Send postive response
					UART_vSendByte((Request_Download+POS_RESPONSE));
				}
				else
				{
					// NG response
					UART_vSendByte(NEG_RESPONSE);
				}
			}
			else if(RxFrameBuffer[SERVICE_ID] == Request_Upload)
			{// Upload request
				// NG response
				UART_vSendByte(NEG_RESPONSE);
				// reset the current mode
				CurrentMode = Waiting_Session_Control;
			}
			else
			{// Wrong service ID
				// NG response
				UART_vSendByte(NEG_RESPONSE);
			}
		}
		else if(CurrentMode == Request_Download)
		{// In download request mode
			// Check if the received frame Transfere data request
			if(RxFrameBuffer[SERVICE_ID] == Transfer_Data)
			{// first transfere data
				CurrentMode = Transfer_Data;
				if((RxFrameBuffer[CODE_SIZE_BYTES] > 0) && (RxFrameBuffer[CODE_SIZE_BYTES] <= PAGE_SIZE))
				{
					// Code size is valid start page erase - write cycle
					Boot_vProgramPage(PageIndex++, &RxFrameBuffer[CODE_DATA]);
					// Send positive response
					UART_vSendByte(Transfer_Data+POS_RESPONSE);
				}
				else
				{
					// NG response
					UART_vSendByte(NEG_RESPONSE);
				}
			}
			else
			{
				// NG response
				UART_vSendByte(NEG_RESPONSE);
			}
		}
		else if(CurrentMode == Request_Upload)
		{// In upload request mode
			// Check if the received frame
		}
		else if(CurrentMode == Transfer_Data)
		{// In data Transfer mode
			// Check if the received frame transfere data or transfere exit
			if(RxFrameBuffer[SERVICE_ID] == Transfer_Data)
			{
				if(PageIndex < RxPageNo)
				{
					if((RxFrameBuffer[CODE_SIZE_BYTES] > 0) && (RxFrameBuffer[CODE_SIZE_BYTES] <= PAGE_SIZE))
					{
						// Code size is valid start page erase - write cycle
						Boot_vProgramPage(PageIndex++, &RxFrameBuffer[CODE_DATA]);
						// Send positive response
						UART_vSendByte(Transfer_Data+POS_RESPONSE);
					}
				}
				else
				{
					// NG response
					UART_vSendByte(NEG_RESPONSE);
				}
			}
			else if(RxFrameBuffer[SERVICE_ID] == Transfer_Exit)
			{
				if(PageIndex == RxPageNo)
				{
					// Check CRC
					// Send positive response
					UART_vSendByte(Transfer_Exit+POS_RESPONSE);
					// reset the current mode
					CurrentMode = Waiting_Session_Control;
					// Return 1
					return 1;
				}
				else
				{
					// NG response
					UART_vSendByte(NEG_RESPONSE);
				}
			}
			else
			{
				// NG response
				UART_vSendByte(NEG_RESPONSE);
			}
		}
		else
		{// Wrong ID
			// NG response
			UART_vSendByte(NEG_RESPONSE);
			// reset the current mode
			CurrentMode = Waiting_Session_Control;
		}
		RxFrameIndex = ST_BYTE;
		RxFrame_Ready= ST_BYTE;
		return 0;
	}
	else
	{
		// Do nothing
		return 0;
	}
}
