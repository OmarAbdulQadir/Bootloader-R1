/*******************************************************************/
/***               Date: 03/8/2023	Day: Thursday	             ***/
/*** 	EEPROM driver for the microcontroller ATMega 32			 ***/
/***     Created By: Omar Abdul Qadir	 Version= 1.1            ***/
/*******************************************************************/
/***         Note: All the data in the file is readable,         ***/
/***     And any editing will affect the controller's behavior,  ***/
/***          So It's not recommended to edit any data,          ***/
/***   Unless you are sure of what is the effect on behaviors.   ***/
/*******************************************************************/


#ifndef EEP_INTERFACE_H
#define EEP_INTERFACE_H
	
	// Standard libraries
	#include "../../../LIB/BIT_MATH.h"
	#include "../../../LIB/STD_TYPES.h"

	// EEPROM write data on specific location
	u8 EEP_vWriteByte(u16, u8 );
	// EEPROM read data from specific location
	u8 EEP_vReadByte(u16, u8* );

#endif	//end EEP_INTERFACE_H
