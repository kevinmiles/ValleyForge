/**
 * \file
 *
 * \brief AVR XMEGA TC Driver Example 1
 *
 * Copyright (C) 2010 - 2011 Atmel Corporation. All rights reserved.
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This simple example shows how to use the \ref tc_group to toggle LEDs.
 *
 * \section files Main files:
 *  - tc.c Timer XMEGA Timer Counter driver implementation
 *  - tc.h Timer XMEGA Timer Counter driver definitions
 *  - tc_example1.c example application
 *  - conf_example.h: configuration of the example
 *
 * \section driverinfo TC Driver
 * The XMEGA TC driver can be found \ref tc_group "here".
 *
 * \section deviceinfo Device Info
 * All AVR XMEGA devices with an tc can be used.
 *
 * \section exampledescription Description of the example
 * The example will configure one TC module (\ref TIMER_EXAMPLE) in normal mode and
 * use three TC interrupts (overflow, Capture/Compare Channels A and B).
 *
 * The TC is setup to use a 31250Hz resolution clock and a 31250 period value
 * resulting in a 1Hz TC overflow frequency.
 * Compare Channels A and B will be setup at 1/4 and 1/2 of the TC period.
 
 * Each callback interupts functions are setup to toggle a LED.
 *  - LED0: Toggles on TC overflow interrup
 *  - LED1 and LED2: Toggle on Compare Channel A and B interrupts
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */
#include <conf_example.h>
#include <string.h>
#include <asf.h>

/**
 * \brief Timer Counter Oveflow interrupt callback function
 *
 * This function is called when an overflow interrupt has occured on
 * TIMER_EXAMPLE and toggles LED0.
 */
static void example_ovf_interrupt_callback(void)
{
	gpio_toggle_pin(LED0_GPIO);
}

/**
 * \brief Timer Counter Capture/Compare A interrupt callback function
 *
 * This function is called when an a capture compare channel A has occured
 * TIMER_EXAMPLE and toggles LED1.
 */
static void example_cca_interrupt_callback(void)
{
	gpio_toggle_pin(LED1_GPIO);
}
/**
 * \brief Timer Counter Capture/Compare B interrupt callback function
 *
 * This function is called when an a capture compare channel B has occured
 * TIMER_EXAMPLE and toggles LED2.
 */
static void example_ccb_interrupt_callback(void)
{
	gpio_toggle_pin(LED2_GPIO);
}


int main(void)
{
	pmic_init();
	board_init();
	sysclk_init();
	sleepmgr_init();

	cpu_irq_enable();
	
	/*
	* Unmask clok for TIMER_EXAMPLE
	*/
	tc_enable(&TIMER_EXAMPLE);
	
	/*
	* Configure interrupts callback functions for TIMER_EXAMPLE
	* overflow interrupt, CCA interrupt and CCB interrupt
	*/
	tc_set_overflow_interrupt_callback(&TIMER_EXAMPLE,
			example_ovf_interrupt_callback);
	tc_set_cca_interrupt_callback(&TIMER_EXAMPLE,
			example_cca_interrupt_callback);
	tc_set_ccb_interrupt_callback(&TIMER_EXAMPLE,
			example_ccb_interrupt_callback);
			
	/*
	* Configure TC in normal mode, configure period, CCA and CCB
	* Enable both CCA and CCB channels
	*/
	
	tc_set_wgm(&TIMER_EXAMPLE, TC_WG_NORMAL);
	tc_write_period(&TIMER_EXAMPLE, TIMER_EXAMPLE_PERIOD);
	tc_write_cc(&TIMER_EXAMPLE, TC_CCA, TIMER_EXAMPLE_PERIOD / 2);
	tc_write_cc(&TIMER_EXAMPLE, TC_CCB, TIMER_EXAMPLE_PERIOD / 4);
	tc_enable_cc_channels(&TIMER_EXAMPLE,(enum tc_cc_channel_mask_enable_t)(TC_CCAEN | TC_CCBEN));
	
	/*
	* Enable TC interrupts (overflow, CCA and CCB)
	*/
	tc_set_overflow_interrupt_level(&TIMER_EXAMPLE, PMIC_LVL_LOW);
	tc_set_cca_interrupt_level(&TIMER_EXAMPLE, PMIC_LVL_LOW);
	tc_set_ccb_interrupt_level(&TIMER_EXAMPLE, PMIC_LVL_LOW);
	
	/*
	* Run TIMER_EXAMPLE at TIMER_EXAMPLE_PERIOD(31250Hz) resolution
	*/
	tc_set_resolution(&TIMER_EXAMPLE, TIMER_EXAMPLE_PERIOD);
	
	do {
		/* Go to sleep, everything is handled by interrupts. */
		sleepmgr_enter_sleep();
	} while (1);
}
