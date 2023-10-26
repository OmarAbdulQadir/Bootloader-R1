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


#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

//Standard libraries Section
#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPES.h"

/* Defining global macros */
#define GROUPA				0
#define GROUPB				1
#define GROUPC				2
#define GROUPD				3
	
#define PIN0				0
#define PIN1				1
#define PIN2				2
#define PIN3				3
#define PIN4				4
#define PIN5				5
#define PIN6				6
#define PIN7				7

#define INPUT				0
#define OUTPUT				1

#define LOW					0
#define HIGH				1


/*************************************************************************************/
/* This function assign the intial value of each port according to the config file	 */
/* Input: Nothing																	 */
/* Return: Nothing																	 */
/*************************************************************************************/
void DIO_vInit( void );

/*************************************************************************************/
/* This function assign certain direction for the selected port						 */
/* Input: Port ID, Direction Value													 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPortDirection( u8 , u8 );

/*************************************************************************************/
/* This function assign certain direction for the selected pin						 */
/* Input: Port ID, Pin ID, Direction Value											 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPinDirection( u8 , u8 , u8 );

/*************************************************************************************/
/* This function assign certain output for the selected port						 */
/* Input: Port ID, output Value														 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPortValue( u8 , u8 );

/*************************************************************************************/
/* This function assign certain output for the selected pin							 */
/* Input: Port ID, Pin ID, Output Value												 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_vSetPinValue( u8 , u8 , u8 );

/*************************************************************************************/
/* This function get the input value of certain port in a gevin variable			 */
/* Input: Port ID, poniter to variable												 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_u8GetPortValue( u8 , u8* );

/*************************************************************************************/
/* This function get the input value of certain pin in a gevin variable				 */
/* Input: Port ID, Pin ID, poniter to variable										 */
/* Return: STD_TRUE, STD_FALSE														 */
/*************************************************************************************/
u8 DIO_u8GetPinValue( u8 , u8 , u8* );


#endif	//end DIO_INTERFACE_H
