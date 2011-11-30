/**
 * \file
 *
 * \brief Autogenerated API include file for the AVR Software Framework (ASF)
 *
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
 *
 * \page License
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
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef ASF_H
#define ASF_H

/*
 * This file includes all API header files for the selected drivers from ASF.
 * Note: There might be duplicate includes required by more than one driver.
 *
 * The file is automatically generated and will be re-written when
 * running the ASF driver selector tool. Any changes will be discarded.
 */

// From module: COMPONENT - LCD - ST7565R Controller
#include <st7565r.h>

// From module: CPU - CPU specific features
#include <ccp.h>
#include <xmega_reset_cause.h>

// From module: CPU - Interrupt management
#include <interrupt.h>

// From module: CPU - PMIC - Prog. Multi-level Interrupt Controller
#include <pmic.h>

// From module: Cyclic Redundancy Check module driver
#include <crc.h>

// From module: GFX Monochrome - Monochrome Graphic Library
#include <gfx_mono.h>

// From module: GFX Monochrome - System Font
#include <sysfont.h>

// From module: GPIO - General purpose Input/Output
#include <gpio.h>

// From module: IOPORT - Input/Output Port Controller
#include <ioport.h>

// From module: MEMORY - NVM - Non Volatile Memory
#include <nvm.h>

// From module: SPI - Serial Peripheral Interface Bus
#include <usart_spi.h>
#include <xmega_usart_spi/usart_spi.h>

// From module: TIMING - Clock Control
#include <sysclk.h>

// From module: USART - Univ. Sync/Async Reciever/Transmitter
#include <usart.h>

// From module: UTILITY - Generic board support
#include <board.h>

// From module: UTILITY - XMEGA compiler driver
#include <compiler.h>
#include <parts.h>
#include <status_codes.h>

#endif // ASF_H
