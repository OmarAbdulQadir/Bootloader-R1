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

// Private section
#include "GI_private.h"

/******************************************************************************/
/* Functions implementation section */
void GI_Enable( void )
{
	set_bit(GI_SREG, GI_BIT);
}


void GI_Disable( void )
{
	clr_bit(GI_SREG, GI_BIT);
}

void GI_vRelocateIVT( u8 Copy_u8Location )
{
	if(Copy_u8Location == IVT_APP)
	{
		/* Enable change of interrupt vectors */
		GI_GICR = (1<<GI_IVCE);
		/* Move interrupts to boot Flash section */
		GI_GICR = (0<<GI_IVSEL);
	}
	else
	{
		/* Enable change of interrupt vectors */
		GI_GICR = (1<<GI_IVCE);
		/* Move interrupts to boot Flash section */
		GI_GICR = (1<<GI_IVSEL);
	}
}
