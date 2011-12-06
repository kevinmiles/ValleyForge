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
PRJ_PATH = ../../../../../..

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr3fp

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3c2512c

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = avr32_services_freertos_lwIP_example_uc3_c2_xplained.elf

# List of C source files.
CSRCS = \
       avr32/drivers/pm/power_clocks_lib.c                \
       thirdparty/lwip/lwip-1.3.2/src/api/netbuf.c        \
       avr32/drivers/pm/pm_uc3c.c                         \
       thirdparty/lwip/lwip-1.3.2/src/netif/etharp.c      \
       thirdparty/lwip/lwip-1.3.2/src/core/pbuf.c         \
       avr32/drivers/usart/usart.c                        \
       thirdparty/lwip/lwip-1.3.2/src/api/api_msg.c       \
       thirdparty/lwip/lwip-1.3.2/src/core/tcp_out.c      \
       thirdparty/freertos/source/croutine.c              \
       thirdparty/freertos/source/timers.c                \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/ip_addr.c \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/icmp.c    \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/main.c \
       thirdparty/freertos/source/queue.c                 \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/inet.c    \
       thirdparty/lwip/lwip-1.3.2/src/core/init.c         \
       thirdparty/lwip/lwip-1.3.2/src/core/tcp.c          \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/read.c \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicsmtp/BasicSMTP.c \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/printf-stdarg.c \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/partest/ParTest.c \
       thirdparty/lwip/lwip-1.3.2/src/core/memp.c         \
       avr32/drivers/intc/intc.c                          \
       thirdparty/lwip/lwip-1.3.2/src/api/netifapi.c      \
       thirdparty/freertos/demo/common/minimal/flash.c    \
       avr32/drivers/gpio/gpio.c                          \
       thirdparty/lwip/lwip-1.3.2/src/core/udp.c          \
       avr32/drivers/flashc/flashc.c                      \
       thirdparty/lwip/lwip-1.3.2/src/core/raw.c          \
       thirdparty/lwip/lwip-1.3.2/src/core/stats.c        \
       avr32/drivers/tc/tc.c                              \
       thirdparty/lwip/lwip-1.3.2/src/core/dhcp.c         \
       thirdparty/freertos/source/list.c                  \
       thirdparty/lwip/lwip-1.3.2/src/core/dns.c          \
       avr32/boards/uc3_c2_xplained/led.c                 \
       avr32/drivers/macb/macb.c                          \
       thirdparty/lwip/lwip-1.3.2/src/core/sys.c          \
       avr32/services/delay/delay.c                       \
       thirdparty/lwip/lwip-1.3.2/src/api/err.c           \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/ip_frag.c \
       thirdparty/freertos/source/portable/memmang/heap_3.c \
       thirdparty/lwip/lwip-1.3.2/src/core/netif.c        \
       avr32/drivers/scif/scif_uc3c.c                     \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicweb/BasicWEB.c \
       thirdparty/lwip/lwip-port-1.3.2/at32uc3/netif/ethernetif.c \
       thirdparty/lwip/lwip-1.3.2/src/api/tcpip.c         \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/igmp.c    \
       thirdparty/lwip/lwip-port-1.3.2/at32uc3/sys_arch.c \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/port.c \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/write.c \
       thirdparty/lwip/lwip-1.3.2/src/core/tcp_in.c       \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basictftp/BasicTFTP.c \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/autoip.c  \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/ethernet.c \
       thirdparty/lwip/lwip-1.3.2/src/api/sockets.c       \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/inet_chksum.c \
       thirdparty/lwip/lwip-1.3.2/src/api/api_lib.c       \
       thirdparty/lwip/lwip-1.3.2/src/core/mem.c          \
       thirdparty/lwip/lwip-1.3.2/src/core/ipv4/ip.c      \
       thirdparty/freertos/source/tasks.c                 \
       thirdparty/lwip/lwip-1.3.2/src/api/netdb.c

# List of assembler source files.
ASSRCS = \
       avr32/utils/startup/startup_uc3.S                  \
       avr32/utils/startup/trampoline_uc3.S               \
       thirdparty/freertos/source/portable/gcc/avr32_uc3/exception.S

# List of include paths.
INC_PATH = \
       avr32/drivers/scif                                 \
       common/boards                                      \
       avr32/drivers/macb                                 \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicsmtp \
       avr32/boards                                       \
       avr32/drivers/pm                                   \
       avr32/drivers/flashc                               \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basictftp \
       thirdparty/lwip/lwip-1.3.2/src/include             \
       avr32/drivers/tc                                   \
       avr32/components/ethernet_phy/rtl8201              \
       avr32/utils                                        \
       thirdparty/freertos/source/portable/gcc/avr32_uc3  \
       avr32/drivers/gpio                                 \
       common/utils                                       \
       thirdparty/freertos/source/include                 \
       avr32/utils/preprocessor                           \
       thirdparty/freertos/demo/common/include            \
       thirdparty/lwip/lwip-1.3.2/src/include/ipv4        \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/at32uc3c2512c_uc3_c2_xplained \
       thirdparty/freertos/demo/lwip_avr32_uc3_example    \
       avr32/drivers/cpu/cycle_counter                    \
       avr32/boards/uc3_c2_xplained                       \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network/basicweb \
       avr32/components/ethernet_phy                      \
       thirdparty/freertos/demo/lwip_avr32_uc3_example/network \
       avr32/drivers/usart                                \
       avr32/components/ethernet_phy/dp83848              \
       avr32/services/delay                               \
       thirdparty/lwip/lwip-port-1.3.2/at32uc3/include    \
       avr32/drivers/intc                                 \
       avr32/components/ethernet_phy/dummy_phy \
       ./thirdparty/freertos/demo/lwip_avr32_uc3_example/at32uc3c2512c_uc3_c2_xplained/gcc

# Additional search paths for libraries.
LIB_PATH = 

# List of libraries to use during linking.
LIBS = 

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = avr32/utils/linker_scripts/at32uc3c/2512c/gcc/link_uc3c2512c.lds

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
       -D TFTP_USED=1                                     \
       -D HTTP_USED=1                                     \
       -D FREERTOS_USED                                   \
       -D SMTP_USED=0                                     \
       -D BOARD=UC3_C2_XPLAINED

# Extra flags to use when linking
LDFLAGS = \
       -nostartfiles -Wl,-e,_trampoline