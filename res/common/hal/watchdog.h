/**
 *  @addtogroup		hal
 *
 *  @file 		watchdog.h
 *  Allows control over the processor watchdog timer.
 * 
 *  @author		Zac Frank
 *
 *  @date		12-12-2011
 * 
 *  @brief
 *  This is the header file which matches watchdog.c.  Allows control over the processor watchdog timer.
 * 
 *  @section Licence
 *  LICENCE GOES HERE
 * 
 *
 * 
 *  @section Description
 *  The watchdog timer is a timer that constantly runs in the background. If the watchdog timer is active, then if it reaches its top value (set
 *  by the user) it resets the micro. This is used to reset the micro when the code goes into an endless loop or some other error occurs that stops
 *  the execution of code.
 *  If a watchdog timer is active, the user must make sure to "pat" the dog (reset the timer) at regular intervals.
 * 
 */ 

// Only include this header file once.
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the hal library.
#include "hal/hal.h"

// DEFINE PUBLIC MACROS.

/*WDTO Macro definitions*/
#define WDTO_15MS	0
#define WDTO_30MS	1
#define WDTO_60MS	2
#define WDTO_120MS	3
#define WDTO_250MS	4
#define WDTO_500MS	5
#define WDTO_1S		6
#define WDTO_2S		7

/*WDTO_4S & WDTO_8S are only valid for the AVR ATmega 2560*/
#if defined (__AVR_ATmega2560___)
	#define WDTO_4S		8
	#define WDTO_8S		9
#endif

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

//enum wdt_timeout {WDTO_15MS, WDTO_30MS, WDTO_60MS, WDTO_120MS, WDTO_250MS, WDTO_500MS, WDTO_1S, WDTO_2S, WDTO_4S, WDTO_8S};	//NB: WDT0_4s & WDT_8S are not valid options on the AT90CANxx or the ATmega16/32/64 devices

// DECLARE PUBLIC GLOBAL VARIABLES.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class watchdog
{
	public:
		// Functions.

		/**
		 * Gets run whenever the instance of class watchdog goes out of scope.
		 * Does nothing, since the watchdog class cannot be instantiated.
		 * @param Nothing
		 * @return Nothing
		 */
		 ~watchdog(void);
		
		/**
		 * Resets the watchdog timer so it doesn't overflow and trigger a system reset.
		 * @param Nothing
		 * @return Nothing
		 */
		static void pat(void);
				
		/**
		 * Sets the timeout of the watchdog timer and starts the watchdog running.
		 * 
		 * @param time_out	One of 10 possible different values for the timeout value of the watchdog
		 * @return 0 for success, -1 for error.
		 * @param Nothing
		 * @return Nothing
		 */
		static int8_t enable(uint8_t time_out);
		
		/** 
		 * Disables the watchdog timer.
		 * @param Nothing
		 * @return Nothing
		 */
		static void disable(void);
		
	private:
		// Functions.
		
		watchdog(void);	// Poisoned.

		watchdog operator =(watchdog const&);	// Poisoned.
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__WATCHDOG_H__*/

// ALL DONE.
