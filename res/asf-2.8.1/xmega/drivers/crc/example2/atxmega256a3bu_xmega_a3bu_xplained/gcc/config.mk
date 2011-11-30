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
PRJ_PATH = ../../../../../..

# Microcontroller: atxmega128a1, atmega128, attiny261, etc.
MCU = atxmega256a3bu

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = xmega_drivers_crc_example2_xmega_a3bu_xplained.elf

# C source files located from the top-level source directory
CSRCS = \
       common/services/clock/xmega/sysclk.c               \
       xmega/drivers/nvm/nvm.c                            \
       common/services/gfx_mono/gfx_mono_c12832_a1z.c     \
       xmega/drivers/ioport/ioport.c                      \
       common/services/gfx_mono/gfx_mono_text.c           \
       common/services/gfx_mono/sysfont.c                 \
       xmega/boards/xmega_a3bu_xplained/init.c            \
       xmega/drivers/crc/example2/example2.c              \
       xmega/drivers/usart/usart.c                        \
       common/services/gfx_mono/gfx_mono_generic.c        \
       common/services/spi/xmega_usart_spi/usart_spi.c    \
       common/components/display/st7565r/st7565r.c        \
       xmega/drivers/crc/crc.c                            \
       common/services/gfx_mono/gfx_mono_framebuffer.c

# Assembler source files located from the top-level source directory
ASSRCS = \
       xmega/drivers/nvm/nvm_asm.s                        \
       xmega/drivers/cpu/ccp.s

# Include path located from the top-level source directory
INC_PATH = \
       xmega/drivers/cpu                                  \
       xmega/drivers/pmic                                 \
       xmega/boards/xmega_a3bu_xplained                   \
       common/services/clock                              \
       xmega/drivers/crc                                  \
       common/services/spi                                \
       xmega/drivers/crc/example2/atxmega256a3bu_xmega_a3bu_xplained \
       xmega/utils                                        \
       common/services/gfx_mono                           \
       xmega/drivers/ioport                               \
       xmega/utils/preprocessor                           \
       xmega/drivers/usart                                \
       common/utils                                       \
       xmega/boards                                       \
       xmega/drivers/nvm                                  \
       common/boards                                      \
       common/services/gpio                               \
       common/components/display/st7565r                  \
       xmega/drivers/crc/example2 \
       ./xmega/drivers/crc/example2/atxmega256a3bu_xmega_a3bu_xplained/gcc

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
       -D CONFIG_NVM_IGNORE_XMEGA_A3_D3_REVB_ERRATA       \
       -D GFX_MONO_C12832_A1Z=1                           \
       -D BOARD=XMEGA_A3BU_XPLAINED

# Extra flags to use when linking
LDFLAGS =  \
       -Wl,--section-start=.BOOT=0x40000                 
