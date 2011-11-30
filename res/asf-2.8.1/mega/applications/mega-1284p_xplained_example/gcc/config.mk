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
PRJ_PATH = ../../../..

# Microcontroller: atxmega128a1, atmega128, attiny261, etc.
MCU = atmega1284p

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = mega_applications_mega_1284p_xplained_example.elf

# C source files located from the top-level source directory
CSRCS = \
       mega/applications/mega-1284p_xplained_example/init.c \
       mega/applications/mega-1284p_xplained_example/mega_1284p_xplained_example.c \
       mega/applications/mega-1284p_xplained_example/usart.c

# Assembler source files located from the top-level source directory
ASSRCS = \
       mega/applications/mega-1284p_xplained_example/qt_asm_tiny_mega.s

# Include path located from the top-level source directory
INC_PATH = \
       common/utils                                       \
       common/boards                                      \
       mega/applications/mega-1284p_xplained_example      \
       mega/utils \
       ./mega/applications/mega-1284p_xplained_example/gcc

# Library paths from the top-level source directory
LIB_PATH =  \
       mega/applications/mega-1284p_xplained_example     

# Libraries to link with the project
LIBS =  \
       avr51g1-4qt-k-0rs                                 

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
       -D SNS1=D                                          \
       -D _SNS1_SNSK1_SAME_PORT_                          \
       -D QTOUCH_STUDIO_MASKS=1                           \
       -D BOARD=MEGA-1284P_XPLAINED                       \
       -D QT_NUM_CHANNELS=4                               \
       -D _QTOUCH_                                        \
       -D SNSK1=D                                         \
       -D _DEBUG_INTERFACE_

# Extra flags to use when linking
LDFLAGS = 
