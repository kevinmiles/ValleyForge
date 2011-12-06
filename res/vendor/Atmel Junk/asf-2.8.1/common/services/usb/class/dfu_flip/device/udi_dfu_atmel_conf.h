/**
 * \file
 *
 * \brief Default Atmel DFU configuration for a USB Device
 * with a single interface Atmel DFU 
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

#ifndef _UDI_DFU_ATMEL_CONF_H_
#define _UDI_DFU_ATMEL_CONF_H_

#include "conf_usb.h"
#include "flip_protocol.h"

/**
 * \ingroup udi_dfu_atmel_group
 * \defgroup udi_dfu_atmel_group_conf Default Atmel DFU configuration
 * for a USB Device with a single interface Atmel DFU
 *
 * @{
 */

//! Control endpoint size
#if (FLIP_PROTOCOL_VERSION == FLIP_PROTOCOL_VERSION_2)
#define  USB_DEVICE_EP_CTRL_SIZE       64
#else
#define  USB_DEVICE_EP_CTRL_SIZE       32
#endif

//! Interface number
#define  UDI_DFU_ATMEL_IFACE_NUMBER    0

/**
 * \name UDD Configuration
 */
//@{
//! 0 endpoints used by DFU interface
#define  USB_DEVICE_MAX_EP             0
//@}

//@}

#endif // _UDI_DFU_ATMEL_CONF_H_