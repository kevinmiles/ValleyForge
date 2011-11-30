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
PRJ_PATH = ../../../../../../../../../..

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr1

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3b0256

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = avr32_services_usb_ms_example_evk1101_asfv1.elf

# List of C source files.
CSRCS = \
       avr32/drivers/pm/power_clocks_lib.c                \
       avr32/drivers/usbb/_asf_v1/enum/host/usb_host_enum.c \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/ushell/ushell_task.c \
       avr32/components/memory/sd_mmc/sd_mmc_spi/sd_mmc_spi.c \
       avr32/drivers/spi/spi.c                            \
       avr32/services/usb/_asf_v1/class/mass_storage/host_mem/host_mem.c \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/virtual_mem/virtual_mem.c \
       common/components/memory/data_flash/at45dbx/_asf_v1/at45dbx.c \
       avr32/drivers/usbb/_asf_v1/enum/device/usb_standard_request.c \
       avr32/drivers/usbb/_asf_v1/enum/usb_task.c         \
       avr32/drivers/usart/usart.c                        \
       avr32/services/fs/fat/file.c                       \
       avr32/drivers/intc/intc.c                          \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/enum/device/usb_descriptors.c \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/device_mass_storage_task.c \
       avr32/services/fs/fat/navigation.c                 \
       avr32/drivers/pm/pm.c                              \
       avr32/drivers/flashc/flashc.c                      \
       avr32/services/fs/fat/fat.c                        \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/enum/device/usb_specific_request.c \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/mass_storage_example.c \
       avr32/drivers/pm/pm_conf_clocks.c                  \
       common/components/memory/data_flash/at45dbx/_asf_v1/at45dbx_mem.c \
       avr32/drivers/gpio/gpio.c                          \
       avr32/drivers/usbb/_asf_v1/usb_drv.c               \
       avr32/services/fs/fat/fat_unusual.c                \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/host_mass_storage_task.c \
       avr32/services/usb/_asf_v1/class/mass_storage/scsi_decoder/scsi_decoder.c \
       avr32/boards/evk1101/led.c                         \
       avr32/drivers/usbb/_asf_v1/enum/device/usb_device_task.c \
       common/services/storage/ctrl_access/ctrl_access.c  \
       avr32/utils/debug/print_funcs.c                    \
       avr32/drivers/usbb/_asf_v1/enum/host/usb_host_task.c \
       avr32/components/memory/sd_mmc/sd_mmc_spi/sd_mmc_spi_mem.c

# List of assembler source files.
ASSRCS = \
       avr32/drivers/intc/exception.S                     \
       avr32/utils/startup/trampoline_uc3.S

# List of include paths.
INC_PATH = \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/enum/device \
       avr32/services/usb/_asf_v1/class/mass_storage/scsi_decoder \
       avr32/drivers/usbb/_asf_v1/enum/device             \
       avr32/services/fs/fat                              \
       avr32/components/memory/sd_mmc/sd_mmc_spi          \
       avr32/boards                                       \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/virtual_mem \
       avr32/drivers/pm                                   \
       avr32/services/usb/_asf_v1                         \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/ushell \
       avr32/drivers/usbb/_asf_v1                         \
       avr32/services/usb/_asf_v1/class/mass_storage/host_mem \
       avr32/utils                                        \
       avr32/boards/evk1101                               \
       avr32/drivers/gpio                                 \
       common/utils                                       \
       avr32/drivers/spi                                  \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/enum \
       avr32/drivers/cpu/cycle_counter                    \
       avr32/drivers/usbb/_asf_v1/enum                    \
       avr32/drivers/usbb/_asf_v1/enum/host               \
       avr32/services/usb/_asf_v1/class/mass_storage/examples \
       avr32/services/usb/_asf_v1/class/mass_storage/examples/conf \
       thirdparty/newlib_addons/libs/include              \
       common/boards                                      \
       common/components/memory/data_flash/at45dbx/_asf_v1 \
       avr32/drivers/usart                                \
       avr32/drivers/flashc                               \
       avr32/utils/preprocessor                           \
       avr32/utils/debug                                  \
       avr32/drivers/intc                                 \
       common/services/storage/ctrl_access \
       ./avr32/services/usb/_asf_v1/class/mass_storage/examples/prj_standalone/at32uc3b0256_evk1101/gcc

# Additional search paths for libraries.
LIB_PATH =  \
       thirdparty/newlib_addons/libs/at32ucr1            

# List of libraries to use during linking.
LIBS =  \
       newlib_addons-at32ucr1-speed_opt                  

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = avr32/utils/linker_scripts/at32uc3b/0256/gcc/link_uc3b0256.lds

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
       -D BOARD=EVK1101                                   \
       -D ACCESS_MEM_TO_RAM_ENABLED                       \
       -D SD_MMC_SPI_ENABLE                               \
       -D AT45DBX_ENABLE

# Extra flags to use when linking
LDFLAGS = \
        -Wl,-e,_trampoline
