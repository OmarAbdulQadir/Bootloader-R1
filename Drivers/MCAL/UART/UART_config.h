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


#ifndef UART_CONFIG_H
#define UART_CONFIG_H

	// Config file
	#include "../../../Inc/Config.h"

	/* Configuration bits section */
	// Baud rate configuration
	#define UART_Baud_Rate		9600

	// Parity mode check
	#define UART_parity_mode	0

	// Rx Interrupt enable
	#define UART_RXIE			1

	// Tx Interrupt enable
	#define UART_TXIE			0

	/*
	 * Please note that Baud rate configurations are only right
	 * with 8MHz System frequency, And any change with the system
	 * frequency without reconfiguring this value will lead to
	 * wrong baud rate output
	 */

	/* Baud rate configuration */
	#if UART_Baud_Rate ==  2400

	#define UART_UBRRL_val		207
	#define UART_UBRRH_val		128

	#elif UART_Baud_Rate == 4800

	#define UART_UBRRL_val		103
	#define UART_UBRRH_val		0

	#elif UART_Baud_Rate == 9600

	#define UART_UBRRL_val		51
	#define UART_UBRRH_val		0

	#elif UART_Baud_Rate == 14400

	#define UART_UBRRL_val		34
	#define UART_UBRRH_val		0

	#elif UART_Baud_Rate == 19200

	#define UART_UBRRL_val		25
	#define UART_UBRRH_val		0

	#elif UART_Baud_Rate == 38400

	#define UART_UBRRL_val		12
	#define UART_UBRRH_val		0

	#elif UART_Baud_Rate == 250000

	#define UART_UBRRL_val		1
	#define UART_UBRRH_val		0

	#else

	#define UART_UBRRL_val		51
	#define UART_UBRRH_val		0

	#endif

#endif /* end UART_CONFIG_H */
