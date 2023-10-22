/*
 * Boot.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Omar Abdul Qadir
 *      Release: 1
 *      Vesrion: 1.1
 */

#ifndef INC_BOOT_H_
#define INC_BOOT_H_

// Includes section
#include <avr/boot.h>
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../Inc/Config.h"
#include "../Drivers/MCAL/GI/GI_interface.h"
#include "../Drivers/MCAL/UART/UART_interface.h"
#include "../Drivers/MCAL/EEP/EEP_interface.h"
#include "../Drivers/MCAL/WDT/WDT_interface.h"

// Macros section
#define NEG_RESPONSE			0x7F
#define POS_RESPONSE			0x40
#define REPEATE_FRAME			0x7E
#define ST_BYTE					0
#define SERVICE_ID				0
#define SESSION_CONTROL_CODE	1
#define CODE_RELEASE			1
#define CODE_SIZE_BYTES			1
#define CODE_VERSION			2
#define CODE_DATA				2
#define CODE_SUB_VERSION		3
#define CODE_SIZE_PAGES			4


// Boot functions
void Boot_init( void );
u8 Boot_vProgramPage(u8 , u8* );
void Boot_vRxCallback( u8 );
u8 Boot_vMainTask( void );

#endif /* INC_BOOT_H_ */
