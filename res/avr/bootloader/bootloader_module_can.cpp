// Copyright (C) 2013  Unison Networks Ltd
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/********************************************************************************************************************************
 *
 *  FILE: 		bootloader_module_can.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	30-11-2012
 *
 *	Provides a bootloader module which only supports CAN programming.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <avr/interrupt.h>

// Include can message ids.
#include "can_messages.h"

// DEFINE PRIVATE MACROS.

// Bootloader information.

#define BOOTLOADER_START_ADDRESS <<<TC_INSERTS_BOOTLOADER_START_ADDRESS_HERE>>>

// CAN peripheral information.
#if defined (__AVR_AT90CAN128__)
	#define NUMBER_OF_MOB_PAGES 15
#else
	#define NUMBER_OF_MOB_PAGES 6
#endif

// CAN Baud rate values.
#define CAN_BAUD_RATE <<<TC_INSERTS_CAN_BAUD_RATE_HERE>>>
#define CLK_SPEED_IN_MHZ <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>

#if (CLK_SPEED_IN_MHZ == 16)
	#if (CAN_BAUD_RATE == 1000)
		#define CAN_BAUD_RATE_CONFIG_1	0x02
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 500)
		#define CAN_BAUD_RATE_CONFIG_1	0x06
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 250)
		#define CAN_BAUD_RATE_CONFIG_1	0x0E
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 200)
		#define CAN_BAUD_RATE_CONFIG_1	0x12
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 125)
		#define CAN_BAUD_RATE_CONFIG_1	0x1E
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 100)
		#define CAN_BAUD_RATE_CONFIG_1	0x26
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
 	#else
 		#error "Invalid CAN baud rate."
	#endif
#elif (CLK_SPEED_IN_MHZ == 8)
	#if (CAN_BAUD_RATE == 1000)
		#define CAN_BAUD_RATE_CONFIG_1	0x00
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x12
	#elif (CAN_BAUD_RATE == 500)
		#define CAN_BAUD_RATE_CONFIG_1	0x02
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 250)
		#define CAN_BAUD_RATE_CONFIG_1	0x06
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 200)
		#define CAN_BAUD_RATE_CONFIG_1	0x08
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 125)
		#define CAN_BAUD_RATE_CONFIG_1	0x0E
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
	#elif (CAN_BAUD_RATE == 100)
		#define CAN_BAUD_RATE_CONFIG_1	0x12
		#define CAN_BAUD_RATE_CONFIG_2	0x04
		#define CAN_BAUD_RATE_CONFIG_3	0x13
 	#else
 		#error "Invalid CAN baud rate."
	#endif
#else
 	#error "CAN bootloader module does not have a CAN baud rate configuration for this CPU clock rate."
#endif

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// Time in units of MODULE_EVENT_PERIOD (in ms) between sending out ALERT_UPLOADER messages while the bootloader is waiting for communications to begin.
const uint16_t ALERT_UPLOADER_TIMEOUT = 50;

// Time in units of MODULE_EVENT_PERIOD (in ms) between the last message arriving, and the bootloader giving up and assuming it has lost comms.
const uint16_t COMMS_TIMEOUT = 1000;

const uint8_t NODE_ID = <<<TC_INSERTS_NODE_ID_HERE>>>;

// State flags.
bool communication_started;
bool communication_recent;
bool ready_to_send_page;
bool message_confirmation_success; 
bool write_details_stored;

// Flag indicating an error has occurred.  Currently, once an error occurs, there is no way to clear it other than a reset.
bool error;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
 *	Initializes the CAN peripheral for the selected CAN communication.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void init_can(void);

/**
 *	Sends a message on the CAN network.
 *
 *	NOTE - Message details are defined in the tranmit_message object.
 *
 *	TAKES:		transmission_message		object containing the message identifier, DLC and data to send.
 *
 *	RETURNS:	Nothing.
 */
void transmit_CAN_message(bootloader_module_can::Message_info& transmit_message);

/**
 *	Resets the CAN peripheral to default settings.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void reset_can(void);

/**
 *	Sends a confirmation message to the uploader.
 * 
 *	NOTE - The message contains one byte informing the uploader whether the message received 
 *			was valid(1) or invalid(0).
 *
 *	TAKES:		confirmation_successful		the validity of the previously received message
 *
 *	RETURNS:	Nothing.
 */
void confirm_reception(bool confirmation_successful);

// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_can::~bootloader_module_can()
{
	// All done.
	return;
}

void bootloader_module_can::init(void)
{	
	// Initialize the CAN controller.
	init_can();
	
	// All done.
	return;
}

void bootloader_module_can::exit(void)
{
	// Reset the CAN controller so that application code finds it untouched.
	reset_can();

	// All done.
	return;
}

void bootloader_module_can::event_idle()
{
	// Send the buffer once the flash page has been copied to it.
	if (!buffer.ready_to_read && ready_to_send_page)
	{
		ready_to_send_page = false;
		send_flash_page(buffer);
	}

	// Check if we've recieved a new message.
	if (reception_message.message_received)
	{		
		// Handle the incoming message.
		filter_message(buffer);
	}	
	
	// All done.
	return;
}

void bootloader_module_can::event_periodic()
{
	// Number of ticks since an alert uploader message was last issued.
	static uint16_t alert_ticks = 0;

	// Check if we've started communications yet.
	if (!communication_started)
	{
		// We haven't started communication yet, so we post a messages every so often to alert the uploader that we're ready.

		// Increment the number of ticks since we last posted an alert.
		alert_ticks++;

		// Check if we're due to post another message.
		if (alert_ticks >= ALERT_UPLOADER_TIMEOUT)
		{
			// Send the ALERT_UPLOADER message.
			alert_uploader();

			// Reset the number of alert ticks since the last message.
			alert_ticks = 0;
		}
	}
	else
	{
		// Reset the alert ticks.
		alert_ticks = 0;
	}

	// Number of ticks since a message was last received.
	static uint16_t comms_ticks = 0;

	if (communication_started && !communication_recent)
	{
		// Increment the number of ticks since we've heard from the uploader.
		comms_ticks++;

		// Check if it seems like the comms have died.
		if (comms_ticks >= COMMS_TIMEOUT)
		{
			// Reset the comms timeout
			comms_ticks = 0;
		}
	}
	else
	{
		// Clear the comms timeout.
		comms_ticks = 0;

		// We're back to square one again.
		communication_started = false;

		// Change the status of the bootloader.
		if (!error)
		{
			set_bootloader_state(IDLE);
		}
	}

	// Communications have no longer been received 'recently'.
	communication_recent = false;
	 
	// All done.
	return;
}

void get_bootloader_module_information(Shared_bootloader_module_constants* bootloader_module_information)
{
	bootloader_module_information->node_id = NODE_ID;
	bootloader_module_information->baud_rate = CAN_BAUD_RATE;
	
	// All done.
	return;
}
	// Avoids name mangling for the shared jumptable.
extern "C" void get_bootloader_module_information_BL(Shared_bootloader_module_constants* bootloader_module_information)
{
	get_bootloader_module_information(bootloader_module_information);
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void confirm_reception(bool confirmation_successful)
{
	module.transmission_message.dlc = 1;
	
	// Reply to the uploader whether the received message was successful or not.
	if (confirmation_successful)
	{
		module.transmission_message.message[0] = 1;
	}
	else
	{
		module.transmission_message.message[0] = 0;
	}
	
	// Confirmation message will have the same ID as the message it is confirming.
	module.transmission_message.message_type = module.reception_message.message_type;
	
	transmit_CAN_message(module.transmission_message);

	// All done.
	return;
}

void init_can(void)
{
	uint8_t mob_number = 0;

	// Reset the CAN controller.
	CANGCON = (1 << SWRES);
	
	// Reset all of the MObs as they have no default value upon reset.
	for (mob_number = 0; mob_number < NUMBER_OF_MOB_PAGES; mob_number++)
	{
		// Select CAN page.
		CANPAGE = (mob_number << 4);
		CANSTMOB = 0x00; // Clear all flags.
		CANCDMOB = 0x00; // Disables MObs.
	}
	
	// Set up bit timing.
	CANBT1 = CAN_BAUD_RATE_CONFIG_1;
	CANBT2 = CAN_BAUD_RATE_CONFIG_2;
	CANBT3 = CAN_BAUD_RATE_CONFIG_3;

	// Id's for reception.
	uint16_t id = CANID_BASE_ID;

	// Choose the MObs to set up.
	//
	// MOB NUMBER 0 - Reception MOb.
	mob_number = 0;
	CANPAGE = (mob_number << 4);
	
	CANIDT1 = id >> 3;; // Set MOb ID.
	CANIDT2 = id << 5;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	
	CANIDM1 = 0xFE; // Set MOb masking ID.
	CANIDM2 = 0x00; // At the moment are filtering first two hex numbers e.g id=0x123, filter = 0x12z - where z can be any number.
	CANIDM3 = 0x00;
	CANIDM4 = 0x00;
	
	CANCDMOB = ((1 << CONMOB1) | 8); // Enable the MOb for reception of 8 data bytes, 
	                                 //in standard format(11 bit identifier) with no automatic reply.

	// MOB NUMBER 1 - Transmission MOb.
	mob_number = 1;
	CANPAGE = (mob_number << 4);
	
	CANIDT1 = 0x00; // Set MOb ID.
	CANIDT2 = 0x00; // Will be set by bootloader before transmission.
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;

	CANIDM1 = 0x00; // Set MOb masking ID.
	CANIDM2 = 0x00;
	CANIDM3 = 0x00;
	CANIDM4 = 0x00;
	
	// Enable the interupts for the MObs enabled.
	CANIE1 = 0x00;
	CANIE2 = (1 << IEMOB0); // Enable interupts on MOb0 (interupt occurs on reception of message).

	// Enable general interupts.
	CANGIE = ((1 << ENIT) | (1 << ENRX)); // Enable receive interupt through CAN_IT.

	// Enable can communication.
	CANGCON = (1 << ENASTB); // Sets the AVR pins to Tx and Rx.
	
	// All done.
	return;
}

void transmit_CAN_message(bootloader_module_can::Message_info& transmit_message)
{
	// Select tranmitting MOB.
	uint8_t mob_number = 1;
	CANPAGE = (mob_number << 4); // MOb1.
	
	// Wait until MOb1 is ready to use.
	while (CANEN2 & (1 << ENMOB1))
	{
		// Do nothing.
	}
	
	// Clear interupt flags.
	CANSTMOB = 0x00;
	
	// Set message id.
	CANIDT4 = 0x00;
	CANIDT3 = 0x00;
	CANIDT2 = (transmit_message.message_type << 5);
	CANIDT1 = (transmit_message.message_type >> 3);
	
	// Set message.
	for (uint8_t i = 0; i < transmit_message.dlc; i++)
	{
		CANMSG = transmit_message.message[i];
	}
	
	// Enable tranmission with desired message length.
	CANCDMOB = ((1 << CONMOB0) | (transmit_message.dlc));
	
	// Wait until the message has sent or an error occured.
	// When the termination is not present on the bus the bootloader seems to get stuck in this loop and reset due to watchdog timeouts or similar.
	// This does not seem to set any of the error flags in the MOB even though it should.
	// TODO - determine why the bootloader gets stuck here and ensure that it does not.
	while (((CANSTMOB & (1 << TXOK)) == 0) && ((CANSTMOB & (1 << AERR)) == 0) && ((CANSTMOB & (1 << BERR)) == 0))
	{
		// Do nothing.
	}
	
	//If the loop exited but did not do so due to a TXOK condition we set the error state.
	if (!(CANSTMOB & (1 << TXOK)))
	{
		// Change the bootloader status to indicate an error.
		set_bootloader_state(ERROR);

		// Set our own error flag.
		error = true;
	}

	// Disable transmit.
	CANCDMOB = 0x00;
	
	// Clear interupt flags.
	CANSTMOB = 0x00;

	// All done.
	return;
}

void reset_can(void)
{
	// Just disable the CAN controller.  The rest doesn't matter.
	CANGCON = (1 << SWRES);

	// All done.
	return;
}

// IMPLEMENT PRIVATE CLASS FUNCTIONS.

void bootloader_module_can::request_reset_procedure()
{
	confirm_reception(message_confirmation_success); // Always successful.
	
	if (reception_message.message[0] == 0)
	{
		reboot_to_bootloader();

		// We will never reach here.
	}
	else
	{
		reboot_to_application();

		// We will never reach here.
	}

	// We will never reach here.
	return;
}

void bootloader_module_can::get_info_procedure(void)
{	
	transmission_message.dlc = 6;
	transmission_message.message_type = CANID_GET_INFO;
	
	// Insert Device signaure.
	uint8_t device_signature[4];
	get_device_signature(device_signature);
	
	transmission_message.message[0] = device_signature[0];
	transmission_message.message[1] = device_signature[1];
	transmission_message.message[2] = device_signature[2];
	transmission_message.message[3] = device_signature[3];
	
	// Insert bootloader version.
	uint16_t bootloader_version = get_bootloader_version();
	
	transmission_message.message[4] = static_cast<uint8_t>(bootloader_version >> 8);
	transmission_message.message[5] = static_cast<uint8_t>(bootloader_version);
	
	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

void bootloader_module_can::write_memory_procedure(Firmware_page& current_firmware_page)
{
	// Store the 32 bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
								 ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
								 ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
								 (static_cast<uint32_t>(reception_message.message[3])));

	// Store the 16 bit code_length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
										(static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in message details.
	if ((current_firmware_page.code_length > SPM_PAGESIZE) || (current_firmware_page.page >= BOOTLOADER_START_ADDRESS))
	{
		// Message failure.
		message_confirmation_success = false;
		write_details_stored = false;
	}
	else
	{
		// Message success.
		write_details_stored = true;
		current_firmware_page.current_byte = 0;
	}

	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::write_data_procedure(Firmware_page& current_firmware_page)
{
	// Only write to buffer if a memory address and code length have been provided.
	if (write_details_stored)
	{
		// Check for possible array overflow.
		if ((current_firmware_page.current_byte + reception_message.dlc) > current_firmware_page.code_length)
		{
			reception_message.dlc = current_firmware_page.code_length - current_firmware_page.current_byte; // Limit the dlc.
		}

		// Store data from received message(message data of 7 bytes) into the buffer(byte by byte).
		for (uint8_t i = 0; i < reception_message.dlc; i++)
		{
			current_firmware_page.data[current_firmware_page.current_byte + i] = reception_message.message[i];
		}

		// Increment the current byte in buffer.
		current_firmware_page.current_byte += reception_message.dlc;

		// Check if the buffer is ready to be written to the flash.
		if (current_firmware_page.current_byte >= (current_firmware_page.code_length))
		{
			current_firmware_page.ready_to_write = true;
			current_firmware_page.current_byte = 0;
			write_details_stored = false;
		}
	}
	else
	{
		// Message failure.
		message_confirmation_success = false;
	}

	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::read_memory_procedure(Firmware_page& current_firmware_page)
{	
	// Store the 32 bit page number.
	current_firmware_page.page = (((static_cast<uint32_t>(reception_message.message[0])) << 24) |
								 ((static_cast<uint32_t>(reception_message.message[1])) << 16) |
								 ((static_cast<uint32_t>(reception_message.message[2])) << 8) |
								 (static_cast<uint32_t>(reception_message.message[3])));

	// Store the 16 bit code_length.
	current_firmware_page.code_length = (((static_cast<uint16_t>(reception_message.message[4])) << 8) | 
										(static_cast<uint16_t>(reception_message.message[5])));

	// Check for errors in message details.
	if ((current_firmware_page.code_length > SPM_PAGESIZE) || (current_firmware_page.page >= BOOTLOADER_START_ADDRESS))
	{
		// Message failure.
		message_confirmation_success = false;
	}
	else
	{
		// Message success.
		current_firmware_page.ready_to_read = true;
		ready_to_send_page = true; // Allow sending the flash page once it is read.
	}
	
	confirm_reception(message_confirmation_success);

	// All done.
	return;
}

void bootloader_module_can::send_flash_page(Firmware_page& current_firmware_page)
{
	transmission_message.message_type = CANID_READ_DATA;
	current_firmware_page.current_byte = 0;
	reception_message.confirmed_send = false;
	
	// Send the flash page in 8 byte messages, confirmation message must be received from uploader after each message.
	while (current_firmware_page.current_byte < current_firmware_page.code_length)
	{
		// Determine the length of message, just in case we are closer than 8 bytes and need to send a smaller message.
		transmission_message.dlc = (current_firmware_page.code_length - current_firmware_page.current_byte);
		if (transmission_message.dlc > 8)
		{
			transmission_message.dlc = 8;
		}

		// Create message.
		for (uint8_t i = 0; i < transmission_message.dlc; i++)
		{
			transmission_message.message[i] = current_firmware_page.data[current_firmware_page.current_byte + i];
		}

		// Increment the current_byte for next iteration.
		current_firmware_page.current_byte += transmission_message.dlc;		
		
		transmit_CAN_message(transmission_message);
		
		// Wait for confirmation message to return from uploader or a uploader command message.
		while (!reception_message.confirmed_send && !reception_message.message_received)
		{
			// Do nothing.
		}
		
		// Exits the sending of the flash page if an uploader command message is received.
		// Allows the uploader to stop the reading if it sees a message is lost.
		if (reception_message.message_received)
		{
			// Abort sending the flash page.
			break;
			
		}

		reception_message.confirmed_send = false;
	}

	// All done.
	return;
}

void bootloader_module_can::filter_message(Firmware_page& current_firmware_page)
{
	// NOTE - Testing the NODE_ID shouldn't actually be required, because the ISR should have filtered other messages out.

	// NOTE - We test the NODE_ID first, then the actual message type, solely because it makes the code a little tidier.

	// If this message is intended for this node, then data[0] should match our own NODE_ID.
	if (reception_message.dlc < 1)
	{
		// This can't possibly be a message for us, because it doesn't have any data, and all our messages should.
		reception_message.message_received = false;
		return;
	}
	else
	{
		// This might be a message for us; check if the NODE_ID matches.
		if (reception_message.message[0] != NODE_ID)
		{
			// This isn't a message for us, because the ID doesn't match.
			reception_message.message_received = false;
			return;
		}
	}
	// Else, it might be a message for us, depending on what the actual message ID is.

	// NOTE - If a message is intended for us, we BREAK, but if its not one of ours, we RETURN.

	// Determine the corresponding behavior for the received message.
	switch (reception_message.message_type)
	{
		case CANID_REQUEST_RESET:
			request_reset_procedure();
			break;

		case CANID_GET_INFO:
			get_info_procedure();
			break;
			
		case CANID_WRITE_MEMORY:
			write_memory_procedure(current_firmware_page);
			break;

		case CANID_WRITE_DATA:
			write_data_procedure(current_firmware_page);
			break;

		case CANID_READ_MEMORY:
			read_memory_procedure(current_firmware_page);
			break;

		default:
			// This message isn't for us, because it's not an ID which we recognise.
			reception_message.message_received = false;
			return;
	}

	// Now that we've handled the message, don't need to worry about it again.
	reception_message.message_received = false;

	// We've now started communications.
	communication_started = true;
	communication_recent = true;

	// Change the status of the bootloader.
	if (!error)
	{
		set_bootloader_state(COMMUNICATING);
	}

	// Restart the bootloader timeout, so we don't reboot halfway through a transfer.
	set_bootloader_timeout(false);
	set_bootloader_timeout(true);
	
	// All done.
	return;
}

void bootloader_module_can::alert_uploader(void)
{
	// Assemble the message to send.
	transmission_message.message_type = CANID_HOST_ALERT;
	transmission_message.dlc = 1;
	transmission_message.message[0] = NODE_ID;

	// Actually send the message.
	transmit_CAN_message(transmission_message);

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

/**
 * ISR for interupts from CAN controller.
 * This routine only operates on received messages, it reads the ID, DLC and data from the CAN controller into a Message_info object.
 * The ISR also sets a flag to tell Bootloader that a new message has been received, or that a confirmation message has been received.
 */
#if defined (__AVR_AT90CAN128__)
ISR(CANIT_vect)
#else
ISR(CAN_INT_vect)
#endif
{
	// Save curent MOb page for current operations. 
	uint8_t saved_MOb = CANPAGE;

	// Select the reception MOb0.
	uint8_t mob_number = 0;
	CANPAGE = (mob_number << 4);
	
	// Check that the interrupt was from message reception.
	if (CANSTMOB & (1 << RXOK))
	{
		// Check node ID, if not the same exit ISR.
		// Node ID is the first byte of data,  checking this will then auto increment to second byte of can message.
		if (CANMSG == NODE_ID)
		{
			// Store message id.
			module.reception_message.message_type = ((CANIDT1 << 3) | (CANIDT2 >> 5));
			
			// A confirmation message received.
			if (module.reception_message.message_type == CANID_READ_DATA)
			{
				module.reception_message.confirmed_send = true;
			}				
			// A uploader command message received.
			else
			{
				// Store dlc.
				module.reception_message.dlc = ((CANCDMOB & 0x0F) - 1); // Minus 1 as the first byte was taken up by the node ID.
				if (module.reception_message.dlc > 7)
				{
					module.reception_message.dlc = 7; // Check is required as CAN controller may give greater than 8 dlc value.
				}

				// Store the message.
				for (uint8_t i = 0; i < module.reception_message.dlc; i++)
				{
					// NOTE - The CANPAGE index auto increments, accessing CANMSG will increment to next byte for next iteration.
					module.reception_message.message[i] = CANMSG; 
				}
			
				// Tell Bootloader that the message was received.
				module.reception_message.message_received = true;
				
				// Default the message confirmation to successful
				message_confirmation_success = true;
			}
		}
	}

	// Reset status flags.
	CANSTMOB = 0x00;

	// Reenable reception for MOb0.
	CANCDMOB = ((1 << CONMOB1) | (8));

	// Restore previous MOb page.
	CANPAGE = saved_MOb;

	// All done.
	return;
}
	
// ALL DONE.
