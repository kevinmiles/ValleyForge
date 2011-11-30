/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief AVR32 UC3 Control Panel potentiometer sensor module.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices can be used.
 * - Supported boards:   EVK1100
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */
//_____  I N C L U D E S ___________________________________________________
#include <string.h>

#include "compiler.h"
#include "gpio.h" // Have to include gpio.h before FreeRTOS.h as long as FreeRTOS
                  // redefines the inline keyword to empty.
#include "FreeRTOS.h"

#include "datalog.h"
#include "shell.h"
#include "board.h"
#include "adc.h"
#include "sensor.h"
#include "config_file.h"
#include "fsaccess.h"

#include "BasicSMTP.h"

//_____ M A C R O S ________________________________________________________

/*! Max string length of a get config. */
#define POT_GETCONF_MAXLEN   64

/*! Path for the config file */
#define SENSOR_POT_CONFIG_FILE   "A:/CFG/POT.TXT"

//_____ D E F I N I T I O N S ______________________________________________
/*! Value for the log rate. */
unsigned int ul_pot_lograte = 5;

/*! Min value for alarm. */
static unsigned int ul_pot_min = 0;

/*! Max Value for alarm. */
static unsigned int ul_pot_max = 100;

/*! Alarm upon event. */
static bool b_pot_alarm = false;
/*! Alarm for max is pending ? */
static bool b_pot_alarm_max = pdFALSE;
/*! Alarm for min is pending ? */
static bool b_pot_alarm_min = pdFALSE;

/*! ADC cell. */
static volatile avr32_adc_t * adc= (volatile avr32_adc_t *) &AVR32_ADC;

/*! The CFG system mutex. */
extern xSemaphoreHandle   xCFGMutex;

//_____ D E C L A R A T I O N S ____________________________________________
extern int sprintf(char *out, const char *format, ...);  // From printf-stdarg.c



/*!
 *  \brief Init the potentiometer channel.
 *
 *  \return true upon success, false if error.
 */
bool b_potentiometer_init ( void )
{
portCHAR token[6];
portCHAR * percent;

   // Get the xCFGMutex.
   if( pdTRUE == x_supervisor_SemaphoreTake( xCFGMutex, 0 ) )
   {
       // get the field
       if (config_file_get_value(SENSOR_POT_CONFIG_FILE, "alarm" , token) >= 0)
       {
         // update value
         if (!strcmp(token, "on"))
         {
           b_pot_alarm = pdTRUE;
         }
       }
       if (config_file_get_value(SENSOR_POT_CONFIG_FILE, "min" , token) >= 0)
       {
         percent = strpbrk(token , "%");
         if (percent != NULL)
         {
           *percent = '\0';
         }
         sscanf(token, "%u", &ul_pot_min);
       }
       if (config_file_get_value(SENSOR_POT_CONFIG_FILE, "max" , token) >= 0)
       {
         percent = strpbrk(token , "%");
         if (percent != NULL)
         {
           *percent = '\0';
         }
         sscanf(token, "%u", &ul_pot_max);
       }
       if (config_file_get_value(SENSOR_POT_CONFIG_FILE, "lograte" , token) >= 0)
       {
         sscanf(token, "%u", &ul_pot_lograte);
       }
     // Release the xCFGMutex.
     x_supervisor_SemaphoreGive( xCFGMutex );
   }
   /* enable pin for sensor */
   gpio_enable_module_pin( ADC_POTENTIOMETER_PIN , ADC_POTENTIOMETER_FUNCTION );

   return (true);
}

/*!
 *  \brief Get the potentiometer sensor config.
 *
 *  \param ppcStringReply Input/Output. The response string. NEVER NULL AS INPUT.
 *                        A malloc for the response string is performed here;
 *                        the caller must free this string.
 *
 *  \return the status of the command execution.
 */
eExecStatus e_potentiometer_get_config( signed portCHAR **ppcStringReply )
{
   // Alloc space for the reply.
   *ppcStringReply = (signed portCHAR *)pvPortMalloc( POT_GETCONF_MAXLEN );
   if( NULL == *ppcStringReply )
   {
      *ppcStringReply = (signed portCHAR *)SHELL_ERRMSG_MEMALLOC;
      return( SHELL_EXECSTATUS_KO );
   }

   // Build the string.
   sprintf( (char *)*ppcStringReply, "lograte=%d\r\n""min=%d%%\r\n""max=%d%%\r\n""alarm=%s\r\n",
            ul_pot_lograte, ul_pot_min, ul_pot_max, ((b_pot_alarm == pdTRUE) ? "on" : "off"));

   return( SHELL_EXECSTATUS_OK );
}

/*!
 *  \brief Set the sensor config.
 *
 *  \param ppcStringReply Input/Output. The response string. NEVER NULL AS INPUT.
 *  \param ac             Input. Number of args
 *  \param av             Input. pointer to args
 *
 *  \return the status of the command execution.
 */
eExecStatus e_potentiometer_set_config( signed portCHAR **ppcStringReply, int ac, signed portCHAR *av[] )
{
portCHAR * token;

  if (config_file_set_value(SENSOR_POT_CONFIG_FILE, ac, av) != 0)
  {
    *ppcStringReply = (signed portCHAR *)SHELL_ERRMSG_CONFIGERROR;
    // return error
    return( SHELL_EXECSTATUS_KO );
  }
  if (!strcmp((char *)av[0] , "alarm"))
  {
    if (!strcmp((char *)av[1] , "on"))
    {
      b_pot_alarm = pdTRUE;
      *ppcStringReply = (signed portCHAR *)SENSOR_MSG_ALARM_ON;
      return( SHELL_EXECSTATUS_OK_NO_FREE );
    }
    else if (!strcmp( (char *)av[1], "off"))
    {
      b_pot_alarm = pdFALSE;
      *ppcStringReply = (signed portCHAR *)SENSOR_MSG_ALARM_OFF;
      return( SHELL_EXECSTATUS_OK_NO_FREE );
    }
    else
    {
      *ppcStringReply = (signed portCHAR *)SHELL_ERRMSG_CONFIGERROR;
      return( SHELL_EXECSTATUS_KO );
    }
  }
  else if (!strcmp((char *)av[0] , "lograte"))
  {
    ul_pot_lograte = atoi((char *)av[1]);
    *ppcStringReply = (signed portCHAR *)SENSOR_MSG_CONFIG_SET;
    return( SHELL_EXECSTATUS_OK_NO_FREE );
  }
  else if (!strcmp((char *)av[0] , "min"))
  {
    token = strpbrk((char *)av[1] , "%");
    if (token != NULL)
    {
      *token = '\0';
    }
    ul_pot_min = atoi((char *)av[1]);
    *ppcStringReply = (signed portCHAR *)SENSOR_MSG_CONFIG_SET;
    return( SHELL_EXECSTATUS_OK_NO_FREE );
  }
  else if (!strcmp((char *)av[0] , "max"))
  {
    token = strpbrk((char *)av[1] , "%");
    if (token != NULL)
    {
      *token = '\0';
    }
    ul_pot_max = atoi((char *)av[1]);
    *ppcStringReply = (signed portCHAR *)SENSOR_MSG_CONFIG_SET;
    return( SHELL_EXECSTATUS_OK_NO_FREE );
  }
  else

  {
    *ppcStringReply = (signed portCHAR *)SHELL_ERRMSG_CONFIGERROR;
    return( SHELL_EXECSTATUS_KO );
  }
}

/*!
 *  \brief Get the current potentiometer value.
 *
 *  \param pxLog a Log structure.
 *
 *  \return true upon success, false if error.
 */
bool b_potentiometer_get_value( xLogDef *pxLog )
{
   int i_current_val;


   /* enable channel for sensor */
   adc_enable( adc, ADC_POTENTIOMETER_CHANNEL );
   /* start conversion */
   adc_start( adc );
   /* get value for sensor */
   i_current_val = adc_get_value( adc, ADC_POTENTIOMETER_CHANNEL ) * 100 / ADC_MAX_VALUE;
   /* Disable channel for sensor */
   adc_disable( adc, ADC_POTENTIOMETER_CHANNEL );

   // Alloc memory for the log string.
   pxLog->pcStringLog = pvPortMalloc( 16*sizeof( char ) );
   if( NULL == pxLog->pcStringLog )
   {
      return( false );
   }
   pxLog->pfFreeStringLog = vPortFree; // Because pvPortMalloc() was used to
                                       // alloc the log string.

   // Build the log string.
   if( i_current_val <= ul_pot_min )
   {
      sprintf( pxLog->pcStringLog, "%3d%% | min", i_current_val );
      // if alarms have to be checked and no alarm for min was pending
      if (( b_pot_alarm == pdTRUE ) && ( b_pot_alarm_min == pdFALSE ))
      {
        // alarm has been taken into account, 
        // don't reenter this test before leaving min area
        b_pot_alarm_min = pdTRUE;
        // allow alarm if max is reached
        b_pot_alarm_max = pdFALSE;
        // post alarm to SMTP task
        v_SMTP_Post("Min Potentiometer Alarm", NULL);
      }
   }
   else if( i_current_val >= ul_pot_max )
   {
      sprintf( pxLog->pcStringLog, "%3d%% | max", i_current_val );
      // if alarms have to be checked and no alarm for max was pending
      if (( b_pot_alarm == pdTRUE ) && ( b_pot_alarm_max == pdFALSE ))
      {
        // alarm has been taken into account, 
        // don't reenter this test before leaving max area
        b_pot_alarm_max = pdTRUE;
        // allow alarm if min is reached
        b_pot_alarm_min = pdFALSE;
        // post alarm to SMTP task
        v_SMTP_Post("Max Potentiometer Alarm", NULL);
      }
   }
   else
   {
      sprintf( pxLog->pcStringLog, "%3d%%", i_current_val );
      // if alarms have to be checked
      if ( b_pot_alarm == pdTRUE )
      {
        // no alarm is pending 
        b_pot_alarm_max = pdFALSE;
        b_pot_alarm_min = pdFALSE;
      }
   }

   return( true );
}
