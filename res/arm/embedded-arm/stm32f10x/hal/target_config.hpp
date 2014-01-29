// Copyright (C) 2011  Unison Networks Ltd
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 * 
 * @file		target_config.h
 * Provides definitions for to be used in implementations.
 * 
 * @todo This file should really be split up and put into the implementation folders, not the general ones.
 * 
 * @author 		Zac Frank
 *
 * @date		15-12-2011
 *  
 * @section Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @brief
 * This contains device specific definitions for avr. Information such as timer size, interrupt
 * specifications and so on are defined here.
 */

// Only include this header file once.
#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>


#if defined (__STM32_F103xx__)
	enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E};
	enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15};
	
	enum CAN_CTRL {CAN_0, NB_CTRL};
	enum CAN_BUF {BUF_0, BUF_1, BUF_2, BUF_3, BUF_4, NB_BUF};
	
#else
	#error "No port/pin definitions for this configuration."
#endif

#if defined (__STM32_F103xx__)
	#	define NUM_PORTS		5	
	#	define NUM_PINS			16
									
#else
	#error "No peripheral definition for this configuration"	
#endif

#define TOTAL_PINS	NUM_PORTS * PINS_PER_PORT

// GPIO pin mode.
enum Gpio_mode {GPIO_OUTPUT_PP, GPIO_INPUT_PD, GPIO_INPUT_PU, GPIO_OUTPUT_OD, GPIO_INPUT_FL, GPIO_INPUT_ANALOG};

#endif /*__TARGET_CONFIG_H__*/
