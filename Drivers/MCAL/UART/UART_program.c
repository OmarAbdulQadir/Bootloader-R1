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

// Private libraries section
#include "../../../Drivers/MCAL/UART/UART_private.h"


// Global variables
static void (*UART_Rx_callback)(u8 ) = NULL;
static void (*UART_Tx_callback)( ) = NULL;

/******************************************************************************/
/* Functions implementation section */
void UART_vInit( void ){
	/*
	 *
	 */
	// Set the buad rate
	UART_UBRRH = UART_UBRRH_val;
	UART_UBRRL = UART_UBRRL_val;

	// Configure the control and status register
	UART_UCSRB = ((UART_RXIE << UART_UCSRB_RXCIE) | (UART_TXIE << UART_UCSRB_TXCIE) | (UART_disable << UART_UCSRB_UDRIE) | (UART_enable << UART_UCSRB_RXEN) | (UART_enable << UART_UCSRB_TXEN) | (UART_disable << UART_UCSRB_UCSZ2) | (UART_disable));
	UART_UCSRC = (UART_UCSRC_mask | (UART_disable << UART_UCSRC_UMSEL) | (UART_parity_mode << UART_UCSRC_UPM) | (UART_disable << UART_UCSRC_USBS) | (UART_UCSZ_val << UART_UCSRC_UCSZ) | (UART_disable << UART_UCSRC_UCPOL));
}

u8 UART_u8IfTxAvaulable( void ){
	/*
	 *
	 */
	return get_bit(UART_UCSRA, UART_UCSRA_UDRE);
}

u8 UART_u8IfRxAvaulable( void )
{
	/*
	 *
	 */
	return get_bit(UART_UCSRA, UART_UCSRA_RXC);
}

void UART_vSendByte( u8 copy_data_byte ){
	/*
	 *
	 */
	while(UART_u8IfTxAvaulable() == 0);
	UART_UDR = copy_data_byte;
}

void UART_vReceiveByte( u8* ptr_data_byte )
{
	/*
	 *
	 */
	while(UART_u8IfRxAvaulable() == 0);
	*ptr_data_byte = UART_UDR;
}


void UART_vSetRxCallback(void (*copy_ptr_callback)( u8 )){
	/*
	 *
	 */
	UART_Rx_callback = copy_ptr_callback;
}

// UART, Rx complete
void __vector_13(void){
	/*
	 *
	 */
	if(UART_Rx_callback != NULL){
		UART_Rx_callback(UART_UDR);
	}
}

void UART_vSetTxCallback(void ( *copy_ptr_callback)( void ) )
{
	/*
	 *
	 */
	UART_Tx_callback = copy_ptr_callback;
}

// UART, Tx complete
void __vector_15(void){
	/*
	 *
	 */
	if(UART_Tx_callback != NULL){
		UART_Tx_callback( );
	}
}
