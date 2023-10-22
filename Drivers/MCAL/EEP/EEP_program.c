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

//Standard libraries Section
#include "EEP_Private.h"



//Global variables

/* Implementing of the driver functions */
// EEPROM write data on specific location
u8 EEP_vWriteByte(u16 copy_u16WriteAddress, u8 copy_u8DataByte){
	/*
	 *
	 */
	if(copy_u16WriteAddress <= EEP_max_add)
	{
		EEP_EEAR = copy_u16WriteAddress;
		EEP_EEDR = copy_u8DataByte;
		while( get_bit(EEP_EECR, EEP_EEWE) == EEP_HIGH );
		set_bit(EEP_EECR, EEP_EEMWE);
		set_bit(EEP_EECR, EEP_EEWE);
		_delay_ms(10);
		return STD_TRUE;
	}
	else
	{
		return STD_FALSE;
	}
}

// EEPROM read data from specific location
u8 EEP_vReadByte(u16 copyu16ReadAddress, u8* ptr_u8DataByte){
	/*
	 *
	 */
	if(copyu16ReadAddress <= EEP_max_add)
	{
		EEP_EEAR = copyu16ReadAddress;
		while((get_bit(EEP_EECR, EEP_EEWE) == EEP_HIGH));
		set_bit(EEP_EECR, EEP_EERE);
		*ptr_u8DataByte = EEP_EEDR;
		return STD_TRUE;
	}
	else
	{
		return STD_FALSE;
	}
}
