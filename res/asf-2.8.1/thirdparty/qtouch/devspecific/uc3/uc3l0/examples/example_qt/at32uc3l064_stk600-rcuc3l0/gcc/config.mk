# Copyright (C) 2009 - 2010 Atmel Corporation. All rights reserved.
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
PRJ_PATH = ../../../../../../../../..

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr3

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3l064

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = avr32_services_qtouch_devspecific_uc3_uc3l0_examples_example_qt_at32uc3l064_stk600-rcuc3l0.elf

# List of C source files.
CSRCS = \
       thirdparty/qtouch/devspecific/uc3/uc3l0/examples/example_qt/main.c \
       thirdparty/qtouch/qdebug/QDebug_at32uc3l.c         \
       avr32/drivers/pm/power_clocks_lib.c                \
       thirdparty/qtouch/devspecific/uc3/uc3l0/common/SPI_Master.c \
       avr32/drivers/usart/usart.c                        \
       avr32/drivers/tc/tc.c                              \
       avr32/drivers/scif/scif_uc3l.c                     \
       avr32/drivers/intc/intc.c                          \
       avr32/drivers/flashcdw/flashcdw.c                  \
       avr32/drivers/gpio/gpio.c                          \
       avr32/drivers/pm/pm_uc3l.c                         \
       thirdparty/qtouch/qdebug/QDebugTransport.c

# List of assembler source files.
ASSRCS = \
       avr32/utils/startup/startup_uc3.S                  \
       avr32/utils/startup/trampoline_uc3.S               \
       avr32/drivers/intc/exception.S

# List of include paths.
INC_PATH = \
       avr32/utils/preprocessor                           \
       avr32/boards/stk600/rcuc3l0                        \
       avr32/drivers/scif                                 \
       avr32/drivers/tc                                   \
       common/boards                                      \
       avr32/drivers/usart                                \
       thirdparty/qtouch/devspecific/uc3/uc3l0/common     \
       avr32/boards                                       \
       avr32/utils                                        \
       thirdparty/qtouch/devspecific/uc3/uc3l0/include    \
       common/utils                                       \
       thirdparty/qtouch/devspecific/uc3/uc3l0/examples/example_qt \
       avr32/drivers/intc                                 \
       avr32/drivers/pm                                   \
       avr32/drivers/flashcdw                             \
       thirdparty/qtouch/qdebug                           \
       avr32/drivers/gpio \
       ./thirdparty/qtouch/devspecific/uc3/uc3l0/examples/example_qt/at32uc3l064_stk600-rcuc3l0/gcc

# Additional search paths for libraries.
LIB_PATH =  \
       thirdparty/qtouch/devspecific/uc3/uc3l0/lib/gcc   

# List of libraries to use during linking.
LIBS =  \
       uc3l-qtouch-gnu                                   

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = avr32/utils/linker_scripts/at32uc3l/064/gcc/link_uc3l064.lds

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -Os

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
       -D BOARD=STK600_RCUC3L0

# Extra flags to use when linking
LDFLAGS = \
       -nostartfiles -Wl,-e,_trampoline
