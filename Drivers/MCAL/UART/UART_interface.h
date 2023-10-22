/*******************************************************************/
/***               Date: 24/6/2023	Day: Saturday	             ***/
/***  UART protocol driver for the microcontroller ATMega 32 	 ***/
/***     Created By: Omar Abdul Qadir	 Version= 1.0            ***/
/*******************************************************************/
/***         Note: All the data in the file is readable,         ***/
/***     And any editing will affect the controller's behavior,  ***/
/***          So It's not recommended to edit any data,          ***/
/***   Unless you are sure of what is the effect on behaviors.   ***/
/*******************************************************************/


#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

	// Standard libraries section
	#include "../../../LIB/BIT_MATH.h"
	#include "../../../LIB/STD_TYPES.h"

	/* Function deceleration section */
	// Enable UART peripheral and configure its setting
	void UART_vInit( void );
	// Check if the UART is available to send data
	u8 UART_u8IfTxAvaulable( void );
	// Check if the UART is available to receive data
	u8 UART_u8IfRxAvaulable( void );
	// Transmit a Byte
	void UART_vSendByte( u8 );
	// Receive a Byte
	void UART_vReceiveByte( u8* );
	// Set Receive callback function
	void UART_vSetRxCallback(void ( *copy_ptr_callback)(u8 ) );
	// Set Transmit callback function
	void UART_vSetTxCallback(void ( *copy_ptr_callback)(void ) );

#endif /* end UART_INTERFACE_H */
