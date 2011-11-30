/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file ******************************************************************
 *
 * \brief Bufferization player configuration template file
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with a USB module can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ***************************************************************************/

/* Copyright (C) 2006-2008, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CONF_BUFF_PLAYER_H_
#define _CONF_BUFF_PLAYER_H_

//! Maximal number of buffers.
#define BUFF_PLAYER_MAX_BUF_CNT     64
//! The starting address of the memory dedicated for the bufferization.

#if BOARD == EVK1104
#define BUFF_PLAYER_ADDRESS_START   ((void *) ( AVR32_INTRAM0_ADDRESS))
//! The size of the memory dedicated for the bufferization.
#define BUFF_PLAYER_MEMORY_SIZE     (AVR32_INTRAM0_SIZE+AVR32_INTRAM1_SIZE)
#else
//! Other Board use SDRAM for audio buffer
//! The starting address of the memory dedicated for the bufferization.
#define BUFF_PLAYER_ADDRESS_START   ((void *) (AVR32_EBI_CS1_ADDRESS + (1024*1024*16)))                                                  
//! The size of the memory dedicated for the bufferization.
#define BUFF_PLAYER_MEMORY_SIZE     (128*1024)
#endif

#endif // _CONF_BUFF_PLAYER_H_
