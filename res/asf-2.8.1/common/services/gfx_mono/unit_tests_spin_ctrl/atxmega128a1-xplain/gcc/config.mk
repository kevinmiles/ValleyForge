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
MCU = atxmega128a1

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = common_services_gfx_mono_unit_tests_spinctrl_xplain.elf

# C source files located from the top-level source directory
CSRCS = \
       common/services/clock/xmega/sysclk.c               \
       common/services/gfx_mono/unit_tests_spin_ctrl/unit_tests.c \
       common/services/serial/usart_serial.c              \
       xmega/drivers/ioport/ioport.c                      \
       common/services/gfx_mono/gfx_mono_text.c           \
       common/utils/stdio/read.c                          \
       common/services/gfx_mono/gfx_mono_spinctrl.c       \
       common/services/gfx_mono/gfx_mono_null.c           \
       xmega/drivers/usart/usart.c                        \
       common/services/gfx_mono/gfx_mono_generic.c        \
       common/utils/stdio/write.c                         \
       xmega/boards/xplain/init.c                         \
       common/utils/unit_test/suite.c                     \
       common/services/gfx_mono/gfx_mono_framebuffer.c    \
       common/services/gfx_mono/sysfont.c

# Assembler source files located from the top-level source directory
ASSRCS = \
       xmega/drivers/cpu/ccp.s

# Include path located from the top-level source directory
INC_PATH = \
       common/services/serial                             \
       xmega/drivers/pmic                                 \
       common/services/clock                              \
       common/services/gpio                               \
       common/utils/stdio/stdio_serial                    \
       common/boards                                      \
       xmega/utils                                        \
       common/services/gfx_mono                           \
       xmega/drivers/ioport                               \
       xmega/utils/preprocessor                           \
       xmega/drivers/usart                                \
       xmega/boards                                       \
       common/services/gfx_mono/unit_tests_spin_ctrl/atxmega128a1-xplain \
       common/services/gfx_mono/unit_tests_spin_ctrl      \
       common/utils                                       \
       xmega/boards/xplain                                \
       xmega/drivers/cpu \
       ./common/services/gfx_mono/unit_tests_spin_ctrl/atxmega128a1-xplain/gcc

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
       -D _ASSERT_ENABLE_                                 \
       -D TEST_SUITE_DEFINE_ASSERT_MACRO                  \
       -D BOARD=XPLAIN

# Extra flags to use when linking
LDFLAGS =  \
       -Wl,--section-start=.BOOT=0x20000                 
