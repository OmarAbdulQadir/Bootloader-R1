/*
 * main.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Omar Abdul Qadir
 *      Release: 1
 *      Version: 1.6
 */

#include "../Inc/Boot.h"
u8 Boot_finished = 0;

int main( void )
{
	// Initiate the bootloader and check if there is a flashing request or not
	Boot_init();

	// Indecator
	DIO_vInit();
	DIO_vSetPinDirection(GROUPA, PIN0, OUTPUT);
	DIO_vSetPinValue(GROUPA, PIN0, HIGH);

#if USE_INT == 0
	u8 UART_RxByte= 0;
#endif
	// Continue to flashing sequesnce
	while( 1 )
	{

#if USE_INT == 0
		UART_vReceiveByte(&UART_RxByte);
		Boot_vRxCallback(UART_RxByte);
#endif

		Boot_finished = Boot_vMainTask();
		// Exit condition
		if(Boot_finished == 1)
		{
			//Exit the bootloader superloop
			break;
		}
	}
	// Clear the Update request and Application Data
	EEP_vWriteByte(App_updateReq, 0x55);
	EEP_vWriteByte(App_indecator, 0x55);
	DIO_vSetPinValue(GROUPA, PIN0, LOW);
	// ECU Reset
	WDT_void_start(time16_3_ms);
	while(1);
}
