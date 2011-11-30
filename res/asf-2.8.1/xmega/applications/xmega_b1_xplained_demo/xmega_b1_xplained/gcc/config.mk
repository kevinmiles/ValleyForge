# Copyright (C) 2010 Atmel Corporation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
# from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
# Atmel AVR product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = ../../../../..

# Microcontroller: atxmega128a1, atmega128, attiny261, etc.
MCU = atxmega128b1

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = xmega_application_xmega_b1_xplained_demo_xmega_b1_xplained.elf

# C source files located from the top-level source directory
CSRCS = \
       xmega/applications/xmega_b1_xplained_demo/ui.c     \
       xmega/drivers/usart/usart.c                        \
       xmega/drivers/usb/usb_device.c                     \
       xmega/drivers/adc/adc.c                            \
       common/components/memory/data_flash/at45dbx/at45dbx_mem.c \
       common/services/usb/udc/udc.c                      \
       common/services/usb/class/composite/device/udi_composite_desc.c \
       common/services/clock/xmega/sysclk.c               \
       common/components/memory/data_flash/at45dbx/at45dbx.c \
       xmega/applications/xmega_b1_xplained_demo/main.c   \
       common/services/sleepmgr/xmega/sleepmgr.c          \
       xmega/drivers/nvm/nvm.c                            \
       xmega/drivers/lcd/lcd.c                            \
       xmega/drivers/ioport/ioport.c                      \
       common/services/usb/class/hid/device/generic/udi_hid_generic.c \
       xmega/applications/xmega_b1_xplained_demo/usb_hid_com.c \
       xmega/boards/xmega_b1_xplained/init.c              \
       common/services/storage/ctrl_access/ctrl_access.c  \
       common/services/usb/class/msc/device/udi_msc.c     \
       xmega/components/display/c42048a/c42048a_full_matrix0/c42048a.c \
       xmega/applications/xmega_b1_xplained_demo/adc_sensors.c \
       xmega/drivers/tc/tc.c                              \
       common/services/usb/class/hid/device/udi_hid.c     \
       common/services/spi/xmega_usart_spi/usart_spi.c

# Assembler source files located from the top-level source directory
ASSRCS = \
       xmega/drivers/cpu/ccp.s                            \
       xmega/drivers/nvm/nvm_asm.s

# Include path located from the top-level source directory
INC_PATH = \
       common/services/usb/class/hid                      \
       xmega/drivers/pmic                                 \
       xmega/drivers/ioport                               \
       xmega/components/display/c42048a/c42048a_full_matrix0 \
       common/components/memory/data_flash/at45dbx        \
       xmega/utils                                        \
       common/services/usb/class/msc                      \
       common/services/usb/class/hid/device/generic       \
       xmega/applications/xmega_b1_xplained_demo/xmega_b1_xplained \
       xmega/drivers/usart                                \
       xmega/drivers/nvm                                  \
       common/services/sleepmgr                           \
       common/utils                                       \
       common/services/usb/class/composite/device         \
       xmega/drivers/adc                                  \
       common/services/usb/class/msc/device               \
       common/services/clock                              \
       xmega/boards/xmega_b1_xplained                     \
       common/services/usb/udc                            \
       common/services/usb                                \
       xmega/drivers/tc                                   \
       xmega/boards                                       \
       common/services/gpio                               \
       xmega/applications/xmega_b1_xplained_demo          \
       common/services/usb/class/hid/device               \
       xmega/drivers/usb                                  \
       common/services/spi                                \
       common/boards                                      \
       xmega/utils/preprocessor                           \
       xmega/drivers/lcd                                  \
       xmega/drivers/sleep                                \
       xmega/drivers/cpu                                  \
       common/services/storage/ctrl_access \
       ./xmega/applications/xmega_b1_xplained_demo/xmega_b1_xplained/gcc

# Library paths from the top-level source directory
LIB_PATH = 

# Libraries to link with the project
LIBS = 

# Additional options for debugging. By default the common Makefile.in will
# add -gdwarf-2.
DBGFLAGS = 

# Optimization settings
OPTIMIZATION = -Os

# Extra flags used when creating an EEPROM Intel HEX file. By default the
# common Makefile.in will add -j .eeprom
# --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0.
EEPROMFLAGS = 

# Extra flags used when creating an Intel HEX file. By default the common
# Makefile.in will add -R .eeprom -R .usb_descriptor_table.
FLASHFLAGS = 

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = 

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -D ACCESS_USB_ENABLED                              \
       -D BOARD=XMEGA_B1_XPLAINED                         \
       -D AT45DBX_ENABLE

# Extra flags to use when linking
LDFLAGS = 
