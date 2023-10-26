/*******************************************************************/
/***               Date: 25/10/2023	Day: Wednesday               ***/
/***    Digital I/O driver for the microcontroller ATMega 32     ***/
/***     Created By: Omar Abdul Qadir	 Version= 4.0            ***/
/*******************************************************************/
/***         Note: All the data in the file is readable,         ***/
/***     And any editing will affect the controller's behavior,  ***/
/***          So It's not recommended to edit any data,          ***/
/***   Unless you are sure of what is the effect on behaviors.   ***/
/*******************************************************************/

//Private libraries Section
#include "DIO_private.h"
static volatile u8* DIO_PINx_REF[4] = {DIO_PINA, DIO_PINB, DIO_PINC, DIO_PIND};
static volatile u8* DIO_DDRx_REF[4] = {DIO_DDRA, DIO_DDRB, DIO_DDRC, DIO_DDRD};
static volatile u8* DIO_PORTx_REF[4] = {DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD};
static u8 Init = LOW;

/*************************************************************************************/
/* This function assign the intial value of each port according to the config file	 */
/* Input: Nothing																	 */
/* Return: Nothing																	 */
/*************************************************************************************/
void DIO_vInit( void )
{

	if(DDRA_init != 0x00)
		*(DIO_DDRx_REF[GROUPA]) = DDRA_init;
	if(DDRB_init != 0x00)
		*(DIO_DDRx_REF[GROUPB]) = DDRB_init;
	if(DDRC_init != 0x00)
		*(DIO_DDRx_REF[GROUPC]) = DDRC_init;
	if(DDRD_init != 0x00)
		*(DIO_DDRx_REF[GROUPD]) = DDRD_init;

	if(PORTA_init != 0x00)
		*(DIO_PORTx_REF[GROUPA]) = PORTA_init;
	if(PORTB_init != 0x00)
		*(DIO_PORTx_REF[GROUPB]) = PORTB_init;
	if(PORTC_init != 0x00)
		*(DIO_PORTx_REF[GROUPC]) = PORTC_init;
	if(PORTD_init != 0x00)
		*(DIO_PORTx_REF[GROUPD]) = PORTD_init;

	Init = HIGH;
}

/*************************************************************************************/
/* This function assign certain direction for the selected port						 */
/* Input: Port ID, Direction Value													 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPortDirection( u8 copy_u8PortID , u8 copy_u8PortDirection )
{
	// Validate port ID and port direction within limits
	if( (copy_u8PortID <= GROUPD) && (copy_u8PortDirection <= PORT_MAX) && (Init == HIGH) )
	{
		// Set assign the port direction to the DDR register
		*(DIO_DDRx_REF[copy_u8PortID]) = copy_u8PortDirection;
		// Return Sucess
		return STD_TRUE;
	}
	else
	{
		// Return aild
		return STD_FALSE;
	}
}


/*************************************************************************************/
/* This function assign certain direction for the selected pin						 */
/* Input: Port ID, Pin ID, Direction Value											 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPinDirection( u8 copy_u8PortID , u8 copy_u8PinID , u8 copy_u8PinDirection )
{
	// Validate port ID, Pin ID and  within limits
	if( (copy_u8PortID <= GROUPD) && (copy_u8PinID <= PIN7) && (Init == HIGH) )
	{
		switch(copy_u8PinDirection)
		{
		case OUTPUT:
			// Set pin's bit in the DDR register
			set_bit(*(DIO_DDRx_REF[copy_u8PortID]), copy_u8PinID);
			break;
		case INPUT:
			// Clear pin's bit in the DDR register
			clr_bit(*(DIO_DDRx_REF[copy_u8PortID]), copy_u8PinID);
			break;
		default:
			// Return faild
			return STD_FALSE;
			break;
		}
		// Return Sucess
		return STD_TRUE;
	}
	else
	{
		// Return faild
		return STD_FALSE;
	}
}

/*************************************************************************************/
/* This function assign certain output for the selected port						 */
/* Input: Port ID, output Value														 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPortValue( u8 copy_u8PortID , u8 copy_u8PortValue )
{
	// Validate port ID and port direction within limits
	if( (copy_u8PortID <= GROUPD) && (copy_u8PortValue <= PORT_MAX) && (Init == HIGH) )
	{
		// Assign the port value in the port register
		*(DIO_PORTx_REF[copy_u8PortID]) = copy_u8PortValue;
		// Return Sucess
		return STD_TRUE;
	}
	else
	{
		// Return aild
		return STD_FALSE;
	}
}

/*************************************************************************************/
/* This function assign certain output for the selected pin							 */
/* Input: Port ID, Pin ID, Output Value												 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPinValue( u8 copy_u8PortID , u8 copy_u8PinID , u8 copy_u8PinValue )
{
	// Validate port ID, Pin ID and  within limits
	if( (copy_u8PortID <= GROUPD) && (copy_u8PinID <= PIN7) && (Init == HIGH) )
	{
		switch(copy_u8PinValue)
		{
		case HIGH:
			// Set pin's bit in the port register
			set_bit(*(DIO_PORTx_REF[copy_u8PortID]), copy_u8PinID);
			break;
		case LOW:
			// Clear pin's bit in the port register
			clr_bit(*(DIO_PORTx_REF[copy_u8PortID]), copy_u8PinID);
			break;
		default:
			// Return faild
			return STD_FALSE;
			break;
		}
		// Return Sucess
		return STD_TRUE;
	}
	else
	{
		// Return faild
		return STD_FALSE;
	}
}

/*************************************************************************************/
/* This function get the input value of certain port in a gevin variable			 */
/* Input: Port ID, poniter to variable												 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_u8GetPortValue( u8 copy_u8PortID , u8* ptr_u8PortValue )
{
	// Validate port ID and port direction within limits
	if( copy_u8PortID <= GROUPD && (Init == HIGH) )
	{
		// Save the port in value to the gevin variable
		*ptr_u8PortValue = *(DIO_PINx_REF[copy_u8PortID]);
		// Return Sucess
		return STD_TRUE;
	}
	else
	{
		// Return aild
		return STD_FALSE;
	}
}

/*************************************************************************************/
/* This function get the input value of certain pin in a gevin variable				 */
/* Input: Port ID, Pin ID, poniter to variable										 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_u8GetPinValue( u8 copy_u8PortID , u8 copy_u8PinID , u8* ptr_u8PinValue )
{
	// Validate port ID, Pin ID and  within limits
	if( (copy_u8PortID <= GROUPD) && (copy_u8PinID <= PIN7) && (Init == HIGH) )
	{
		*ptr_u8PinValue = get_bit(*(DIO_PINx_REF[copy_u8PortID]), copy_u8PinID);
		// Return Sucess
		return STD_TRUE;
	}
	else
	{
		// Return aild
		return STD_FALSE;
	}
}
