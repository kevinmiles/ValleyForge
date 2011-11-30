/**
 * \file
 *
 * \brief Common Sensor Service Inertial Sensor Wake Event Example
 *
 * \mainpage
 *
 * \section intro Introduction
 *
 * This application demonstrates the use of sensor events generated by the 
 * accelerometer and/or gyroscope devices installed on an Atmel Sensors Xplained
 * board.  The application sets up the sensor event handler(s), then places
 * the microcontroller in a low-power sleep state.  When the specified
 * sensor event occurs, the system wakes up, reads and displays sensor data,
 * and re-enters the sleep mode.  This wake/sleep cycle repeats indefinitely.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 * Support and FAQ: http://support.atmel.no/
 *
 * \section License
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
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

#include <stdio.h>

#include <board.h>
#include <led.h>
#include <sleepmgr.h>

#include <sensors/sensor.h>


// Configuration Constants

#define USE_ACCEL        (true)     // true = init & read accel
#define ACCEL_WAKE       (true)     // true = use accel any-motion to wake up
#define ACCEL_MOT_THRESH (250)      // accel any-motion threshold (milli-g)

#define USE_GYRO         (false)    // true = init & read gyro
#define GYRO_WAKE        (false)    // true = use gyro new data to wake up
#define GYRO_SLEEP       (false)    // true = put gyro in sleep mode btn samples
#define GYRO_SAMPLE_RATE (100)      // gyro sample rate (Hz)
#define GYRO_RESTART_DELAY (50)     // gyro restart (after sleep) delay (msec)

#define USE_PRINTF       (false)
#define SCALED_DATA      (true)

#if UC3
	// UC3 Sleep Mode to use, one of: 
	//   SLEEPMGR_ACTIVE, SLEEPMGR_IDLE, SLEEPMGR_FROZEN, SLEEPMGR_STDBY,
	//   SLEEPMGR_STOP, SLEEPMGR_DEEPSTOP, SLEEPMGR_STATIC,
	//   SLEEPMGR_SHUTDOWN (UC3L only)
#  define SLEEP_MODE     (SLEEPMGR_FROZEN)   // sleep mode to use

#elif XMEGA
	// XMega Sleep Mode to use, one of: 
	//   SLEEPMGR_ACTIVE, SLEEPMGR_IDLE, SLEEPMGR_ESTDBY, SLEEPMGR_PSAVE,
	//   SLEEPMGR_STDBY, SLEEPMGR_PDOWN
#  define SLEEP_MODE     (SLEEPMGR_IDLE)     // sleep mode to use
#endif


// LED definitions
//

#if (BOARD==UC3_L0_XPLAINED)
#  define ACTIVITY_LED  LED4        // LED to show awake/operating
#  define ACCEL_LED     LED1        // LED to indicate accel interrupt
#  define GYRO_LED      LED3        // LED to indicate gyro interrupt

#elif (BOARD==UC3_A3_XPLAINED)
#  define ACTIVITY_LED  LED0        // LED to show awake/operating
#  define ACCEL_LED     LED1        // LED to indicate accel interrupt
#  define GYRO_LED      LED3        // LED to indicate gyro interrupt

#elif (BOARD==XMEGA_A1_XPLAINED) || (BOARD==XMEGA_A3BU_XPLAINED)
#  define ACTIVITY_LED  LED0        // LED to show awake/operating
#  define ACCEL_LED     LED2        // LED to indicate accel interrupt
#  define GYRO_LED      LED3        // LED to indicate gyro interrupt

#endif

// supply missing C-library constants

#if defined(XMEGA) && defined(__GNUC__)
enum {EXIT_SUCCESS, EXIT_FAILURE};
#endif

// Set up sensor data storage and data formats.
//
	sensor_t accelerometer;         // accelerometer descriptor
	volatile sensor_data_t acceleration = { .scaled = SCALED_DATA };

	sensor_t gyroscope;             // gyroscope descriptor
	volatile sensor_data_t rotation    = { .scaled = SCALED_DATA };


// Forward declarations
//

#if (USE_ACCEL == true)

/*! \internal Accelerometer Event Callback Routine
 *
 * \return  Nothing.
 */
static void acceleration_event(volatile void * in) 
{
	sensor_event_desc_t * const pin = (sensor_event_desc_t *) in;

	*((sensor_data_t *)(pin->arg)) = pin->data;     // copy sensor data

	LED_Toggle(ACCEL_LED);
}
#endif

#if (GYRO_WAKE == true)
/*! \internal Gyroscope Event Callback Routine
 *
 * \return  Nothing.
 */
static void gyro_event(volatile void * in) 
{
	sensor_event_desc_t * const pin = (sensor_event_desc_t *) in;

	*((sensor_data_t *)(pin->arg)) = pin->data;      // copy sensor data

	LED_Toggle(GYRO_LED);
}
#endif


/*! \brief Inertial sensor demo application entry
 *
 * Summarize what's demonstrated in this demonstration.
 *
 * \return  Nothing.
 */
int main(void)
{
	// Initialize the Xplained (UC3 or XMEGA) platform & sensor boards.
	//
	sensor_platform_init();

	LED_On(ACTIVITY_LED);

	// Initialize the MCU sleep manager API and specify a sleep mode.
	//
	sleepmgr_init();
	sleepmgr_lock_mode(SLEEP_MODE);


#if (USE_ACCEL == true)
	// *********** Accelerometer Initialization ************* //
	//
	// Attach acclerometer
	//
	sensor_attach(&accelerometer, SENSOR_TYPE_ACCELEROMETER, 0, 0);

	if (accelerometer.err) {
		puts("\r\nAccelerometer initialization error.");
		mdelay(5000);
		return EXIT_FAILURE;
	}

	 // Enable motion event
	 //
	sensor_event_desc_t accel_event_desc = {
		.sensor      = &accelerometer,
		.event       = SENSOR_EVENT_MOTION,
		.data.scaled = SCALED_DATA,
		.handler     = acceleration_event,
		.arg         = &acceleration,
		.enabled     = true
	};

	sensor_set_threshold(&accelerometer, SENSOR_THRESHOLD_MOTION, 
			              ACCEL_MOT_THRESH);

	sensor_add_event(&accel_event_desc);

	// Put the accelerometer into a low-power mode (if available)
	sensor_set_state(&accelerometer, SENSOR_STATE_LOW_POWER);
#endif


#if (USE_GYRO == true)
	// ************* Gyroscope Initialization ************* //
	//
	// Attach gyroscope
	//
	sensor_attach(&gyroscope, SENSOR_TYPE_GYROSCOPE, 0, 0);

	if (gyroscope.err) {
		puts("\r\nGyroscope initialization error.");
		mdelay(5000);
		return EXIT_FAILURE;
	}

	sensor_set_sample_rate(&gyroscope, GYRO_SAMPLE_RATE);

#  if (GYRO_WAKE == true)
	// Enable gyroscope new data event for wakeup
	sensor_event_desc_t gyro_event_desc = {
		.sensor      = &gyroscope,
		.event       = SENSOR_EVENT_NEW_DATA,
		.data.scaled = SCALED_DATA,
		.handler     = gyro_event,
		.arg         = &rotation,
		.enabled     = true
	};

	sensor_add_event(&gyro_event_desc);

	// Read sensor once to clear any outstanding new data interrupt
	sensor_get_rotation(&gyroscope, &rotation);

#  elif (GYRO_SLEEP == true)
	// Put gyro in low-power sleep mode until accelerometer wakes system up
	sensor_set_state(&gyroscope, SENSOR_STATE_SLEEP);
#  endif
#endif


	// ******************* Main Loop ************************ //

	while (true) {

		// Put device in low power sleep mode; wait for an interrupt to wake.
		//
		LED_Off(ACTIVITY_LED);            // turn off while asleep

		sleepmgr_enter_sleep();         // enter specified sleep mode

		// Device has woken up 
		//
		LED_On(ACTIVITY_LED);             // turn on while awake


#if ((USE_GYRO == true) && (GYRO_WAKE == false))
		// Read gyro in response to accelerometer wake

#  if (GYRO_SLEEP == true)   // if gyro uses low-power sleep mode
		sensor_set_state(&gyroscope, SENSOR_STATE_NORMAL); // wake up gyro
		mdelay(GYRO_RESTART_DELAY);     // wait for device to settle
		sensor_get_rotation(&gyroscope, &rotation);        // read gyro
		sensor_set_state(&gyroscope, SENSOR_STATE_SLEEP);  // put back to sleep

#  else                      // if gyro is always in normal mode
		sensor_get_rotation(&gyroscope, &rotation); // read gyro now
#  endif
#endif

#if (USE_PRINTF == true)
		// Print accelerometer & gyroscope values

		const char * const format = SCALED_DATA ?
			"acc = [%5d, %5d, %5d]  rot = [%5d, %5d, %5d]\r\n" :
			"acc = [%.5x, %.5x, %.5x]  rot = [%.5x, %.5x, %.5x]\r\n";

		printf(format,
			(int16_t) acceleration.axis.x,	// data from motion event handler
			(int16_t) acceleration.axis.y,
			(int16_t) acceleration.axis.z,
			
			(int16_t) rotation.axis.x,		// data from sensor_get_rotation()
			(int16_t) rotation.axis.y,		//  (if GYRO_WAKE==false), or from 
			(int16_t) rotation.axis.z);		//  gyro new data event handler
#endif

		mdelay(100);			// minimum active time = 100 msec
	}


	return EXIT_SUCCESS;
}


