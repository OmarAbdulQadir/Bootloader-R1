/*******************************************************************/
/***               Date: 11/10/2023	Day: Tuesday	             ***/
/*** Global Interrupt driver for the microcontroller ATMega 32 	 ***/
/***     Created By: Omar Abdul Qadir	 Version= 1.0            ***/
/*******************************************************************/
/***         Note: All the data in the file is readable,         ***/
/***     And any editing will affect the controller's behavior,  ***/
/***          So It's not recommended to edit any data,          ***/
/***   Unless you are sure of what is the effect on behaviors.   ***/
/*******************************************************************/



#ifndef GI_INTERFACE_H
#define GI_INTERFACE_H

	// Standard libraries section
	#include "../../../LIB/BIT_MATH.h"
	#include "../../../LIB/STD_TYPES.h"

	#define IVT_APP				0
	#define IVT_BLD				1

	/* Function decleration section */
	// Enable Global Interrupt
	void GI_Enable( void );
	// Enable Global Interrupt
	void GI_Disable( void );
	// Relocate the vactor table
	void GI_vRelocateIVT( u8 );
	

#endif /* end GI_INTERFACE_H */
