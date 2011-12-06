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
PRJ_PATH = ../../../../../../../../../..

# Microcontroller: atxmega128a1, atmega128, attiny261, etc.
MCU = atxmega128b1

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = common_services_usb_class_hid_device_keyboard_example_example_xmega_b1_xplained.elf

# C source files located from the top-level source directory
CSRCS = \
       common/services/clock/xmega/sysclk.c               \
       xmega/drivers/ioport/ioport.c                      \
       common/services/usb/class/hid/device/kbd/example/main.c \
       common/services/usb/class/hid/device/kbd/udi_hid_kbd_desc.c \
       common/services/sleepmgr/xmega/sleepmgr.c          \
       common/services/usb/class/hid/device/kbd/example/atxmega128b1_xmega_b1_xplained/ui.c \
       xmega/boards/xmega_b1_xplained/init.c              \
       common/services/usb/class/hid/device/kbd/udi_hid_kbd.c \
       xmega/drivers/nvm/nvm.c                            \
       xmega/drivers/usb/usb_device.c                     \
       common/services/usb/udc/udc.c                      \
       common/services/usb/class/hid/device/udi_hid.c

# Assembler source files located from the top-level source directory
ASSRCS = \
       xmega/drivers/cpu/ccp.s                            \
       xmega/drivers/nvm/nvm_asm.s

# Include path located from the top-level source directory
INC_PATH = \
       common/services/clock                              \
       xmega/boards/xmega_b1_xplained                     \
       xmega/boards                                       \
       xmega/drivers/ioport                               \
       common/services/usb/class/hid/device               \
       xmega/drivers/usb                                  \
       common/boards                                      \
       common/services/usb/class/hid/device/kbd           \
       xmega/drivers/nvm                                  \
       xmega/utils/preprocessor                           \
       xmega/utils                                        \
       common/services/usb/udc                            \
       common/services/usb                                \
       common/services/gpio                               \
       common/utils                                       \
       common/services/usb/class/hid/device/kbd/example/atxmega128b1_xmega_b1_xplained \
       common/services/usb/class/hid                      \
       common/services/sleepmgr                           \
       xmega/drivers/sleep                                \
       common/services/usb/class/hid/device/kbd/example   \
       xmega/drivers/cpu \
       ./common/services/usb/class/hid/device/kbd/example/atxmega128b1_xmega_b1_xplained/gcc

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
       -D BOARD=XMEGA_B1_XPLAINED

# Extra flags to use when linking
LDFLAGS = 