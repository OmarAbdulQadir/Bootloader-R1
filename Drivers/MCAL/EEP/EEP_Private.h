/*******************************************************************/
/***               Date: 03/6/2023	Day: Saturday	             ***/
/*** 	 ADC driver for the microcontroller ATMega 32			 ***/
/***     Created By: Omar Abdul Qadir	 Version= 1.1            ***/
/*******************************************************************/
/***         Note: All the data in the file is readable,         ***/
/***     And any editing will affect the controller's behavior,  ***/
/***          So It's not recommended to edit any data,          ***/
/***   Unless you are sure of what is the effect on behaviors.   ***/
/*******************************************************************/

#ifndef EEP_PRIVATE_H_
#define EEP_PRIVATE_H_

	#include "EEP_interface.h"
	#include <util/delay.h>

	/* EEPROM Control Register bits */
	// EEPROM Ready Interrupt Enable
	#define EEP_EERIE			3
	// EEPROM Master Write Enable
	#define EEP_EEMWE			2
	// EEPROM Write Enable
	#define EEP_EEWE			1
	// EEPROM Read Enable
	#define EEP_EERE			0


	// EEPROM Address Register
	#define EEP_EEAR		*((volatile u16*) 0x3E)
	// EEPROM Data Register
	#define EEP_EEDR		*((volatile u8 *) 0x3D)
	// EEPROM Control Register
	#define EEP_EECR		*((volatile u8 *) 0x3C)



	/* Private Macros */
	#define EEP_LOW				0
	#define EEP_HIGH			1
	#define EEP_max_add			((u16)1023u)

#endif /* EEP_PRIVATE_H_ */
