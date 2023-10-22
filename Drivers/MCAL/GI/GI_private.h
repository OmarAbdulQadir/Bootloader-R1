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


#ifndef GI_PRIVATE_H
#define GI_PRIVATE_H
	
	// Private section
	#include "../../../Drivers/MCAL/GI/GI_interface.h"

	// Global Interrupt bit
	#define GI_BIT				7

	// Interrupt vector select
	#define GI_IVSEL			1
	// Interupt vector change enable
	#define GI_IVCE				0
	
	// Status register
	#define GI_SREG				*((volatile u8 *) 0x5F)
	// Global Interrupt control register
	#define GI_GICR				*((volatile u8 *) 0x5B)


#endif /* end GI_PRIVATE_H */
