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

// From module: AUDIO - ABDAC - Audio Bitstream DAC
#include <abdac.h>

// From module: AUDIO - Audio Mixer
#include <audio_mixer.h>

// From module: AUDIO - Audio software components
#include <audio.h>

// From module: AUDIO - Mono Audio PWM DAC
#include <pwm_dac.h>

// From module: AUDIO - TLV320AIC23B Audio Codec
#include <tlv320aic23b.h>

// From module: AUDIO - TPA6130A2 Audio Amplifier
#include <tpa6130.h>

// From module: CPU - Cycle Counter
#include <cycle_counter.h>

// From module: CPU - INTC - Interrupt Controller
#include <intc.h>

// From module: CPU - Interrupt management
#include <interrupt.h>

// From module: CPU - PM - Power Manager
#include <power_clocks_lib.h>
#include <sleep.h>

// From module: DSP - Digital signal processing library
#include <dsp.h>

// From module: EVK1105 board support
#include <led.h>

// From module: GPIO - General-Purpose Input/Output
#include <gpio.h>

// From module: MEMORY - EBI Static Memory Controller
#include <smc.h>

// From module: MEMORY - FLASHC - Flash Controller
#include <flashc.h>

// From module: MEMORY - PDCA - Peripheral DMA Controller
#include <pdca.h>

// From module: Newlib addons library
#include <nlao_cpu.h>
#include <nlao_exceptions.h>
#include <nlao_interrupts.h>
#include <nlao_io.h>
#include <nlao_usart.h>

// From module: SSC - Synchronous Serial Controller (I2S)
#include <ssc_i2s.h>

// From module: TWI - Two-Wire Interface
#include <twi.h>

// From module: USART - Univ. Sync/Async Serial Rec/Trans
#include <usart.h>

// From module: USB - Universial Serial Bus enumeration (ver. 1)
#include <usb_task.h>

// From module: USB - Universial Serial Bus host enumeration (ver. 1)
#include <usb_host_enum.h>

// From module: USB Audio protocol (from ASF ver. 1)
#include <usb_audio.h>

// From module: USB HID Class protocol (from ASF ver. 1)
#include <hid.h>

// From module: USBB - Universial Serial Bus Interface (ver. 1)
#include <usb_drv.h>

// From module: UTILITY - Compiler abstraction layer and code utilities
#include <compiler.h>
#include <status_codes.h>

// From module: UTILITY - Debug macros and functions
#include <debug.h>

// From module: UTILITY - Generic board support
#include <board.h>

// From module: UTILITY - USART Debug strings
#include <print_funcs.h>

#endif // ASF_H
