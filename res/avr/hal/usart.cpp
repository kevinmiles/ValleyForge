// Copyright (C) 2011  Unison Networks Ltd
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
 *  FILE: 		Usart.cpp	
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		Jared Sanson
 *
 *  DATE CREATED:	17-01-2012
 *
 *	AVR specific implementation of the USART HAL module.
 *  Supports hardware USART peripherals on all AVR chips,
 *  and the LIN-USART peripheral on ATmega64M1/C1 devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr/io.h>
#include <avr/interrupt.h>
#include <hal/spi.hpp>
#include "hal/hal.hpp"
#include "hal/gpio.hpp"
#include "hal/usart.hpp"
#include "hal/targets/avr.hpp"

#include "usart_imp.hpp"

// DEFINE PRIVATE MACROS.

#if defined(USE_USART_LIN) && defined(USE_USART0)
	// NOTE - The LIN-USART is defined as channel USART_0.
	//  I don't think there are any chips that have both available.
	#error "USART0 conflicts with LIN-USART peripheral"
#endif



////// Usart_imp Implementation //////

/**
 * Private, target specific implementation class for public Usart class.
 */

Usart_imp::Usart_imp(Usart_channel channel, Usart_pins pins, Usart_registers registers)
	: channel(channel), pins(pins), registers(registers) { }

Usart_imp::~Usart_imp(void) { }

// Called whenever someone binds to this instance
void Usart_imp::bind(void)
{
	// Enable the peripheral, if required

	// Acquire access to the pins, and configure them as required.
	// TODO - How can we dynamically bind GPIO pins??

	disable(); // Start disabled, so the module can be configured safely

	// Reset state machines
	async_rx.active = false;
	async_tx.active = false;
}

// Called whenever someone is finished with this instance
void Usart_imp::unbind(void)
{
	disable();

	// Relinquish access to the GPIO pins
	//pins.tx.unbind(); // TODO
}

#ifdef USE_SPI_USART
bool Usart_imp::mspim_inuse(void)
{
	// Check if the peripheral is currently configured for MSPIM mode
	bool enabled = (bit_read(*registers.UCSRB, TXEN_BIT) || bit_read(*registers.UCSRB, RXEN_BIT));
	bool mspim_mode = reg_read(*registers.UCSRC, UMSEL0_BIT, 2) == 0b11;
	return (enabled && mspim_mode);
}
#endif

void Usart_imp::enable(void)
{
	// Enable transceiver hardware
	*registers.UCSRB |= _BV(RXEN_BIT) | _BV(TXEN_BIT);

	// Enable interrupts
	*registers.UCSRB |= _BV(TXCIE_BIT) | _BV(RXCIE_BIT);

	// NOTE - UDRE is not enabled until it is required,
	// as it will immediately trigger the UDRE interrupt.
}

void Usart_imp::disable(void)
{
	// Disable interrupts
	*registers.UCSRB &= ~( _BV(TXCIE_BIT) | _BV(RXCIE_BIT) | _BV(UDRE_BIT) );

	// Disable transceiver hardware
	*registers.UCSRB &= ~( _BV(RXEN_BIT) | _BV(TXEN_BIT) );

	// NOTE - Transmitter is not disabled instantly.
	//  It will continue finishing any current transmission before disabling.

	// Disabling the receiver also flushes the UDR receive buffer.
}

void Usart_imp::flush(void)
{
	while (bit_read(*registers.UCSRA, RXC_BIT) == 1)
	{
		volatile uint8_t dummy __attribute__((unused)) = *registers.UDR;
	}
}


Usart_config_status Usart_imp::configure(Usart_setup_mode mode, uint32_t baud_rate, uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	Usart_config_status result = USART_CFG_FAILED;

	// Check that the USART is not being used by the SPI module
	#ifdef USE_SPI_USART
	if (mspim_inuse())
		return USART_CFG_FAILED;
	#endif

	// Disable tx/rx before configuring
	disable();

	// Set the operating mode (Async/Sync)
	result = set_mode(mode);
	if (result != USART_CFG_SUCCESS)
		return result;

	// Configure the framing
	result = set_framing(data_bits, parity, stop_bits);
	if (result != USART_CFG_SUCCESS)
		return result;

	// Configure the baud rate
	result = set_baud_rate(baud_rate);
	if (result != USART_CFG_SUCCESS)
		return result;

	// Enable tx/rx
	enable();

	return USART_CFG_SUCCESS;
}


bool Usart_imp::transmitter_ready(void)
{
	// Check if we're ready to transmit more data
	return ((bit_read(*registers.UCSRA, UDRE_BIT) == 1) && !async_tx.active);
}

bool Usart_imp::receiver_has_data(void)
{
	return ((bit_read(*registers.UCSRA, RXC_BIT) == 1) && !async_rx.active);
}


Usart_io_status Usart_imp::transmit_byte(uint8_t data)
{
	while (!transmitter_ready())
	{
		// Wait for transmit buffer to be empty
	}

	// 9 bit mode
	if (bit_read(*registers.UCSRB, UCSZ2_BIT) == 1)
	{
		uint8_t bit8 = 0; // TODO - How to feed in the 9th bit?
		bit_write(*registers.UCSRB, TXB8_BIT, bit8);
		return USART_IO_FAILED;
	}

	*registers.UDR = data;

	// We don't need to wait for it to finish, since the next time
	// this function is called it will wait until the TX buffer is free again.

	//while (((*registers.UCSRA & _BV(TXC_BIT)) == 0)) {}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_byte_async(uint8_t data)
{
	if (!transmitter_ready())
		return USART_IO_BUSY;

	// 9 bit mode
	if (bit_read(*registers.UCSRB, UCSZ2_BIT) == 1)
	{
		uint8_t bit8 = 0; // TODO - How to feed in the 9th bit?
		bit_write(*registers.UCSRB, TXB8_BIT, bit8);
		return USART_IO_FAILED;
	}

	*registers.UDR = data;

	// If the user wants to use the TX ISR to load in more data, enable it so it gets triggered.
	if (tx_isr && tx_isr_enabled)
		set_udrie(true);

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_buffer(uint8_t* data, size_t size)
{
	while (!transmitter_ready())
	{
		// Wait for transmitter
	}

	for (size_t i = 0; i < size; i++)
	{
		transmit_byte(*data++);
	}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_buffer_async(uint8_t* data, size_t size, usarttx_callback_t cb_done, void *p)
{
	if (!transmitter_ready())
		return USART_IO_BUSY;

	// Reset the state machine
	async_tx.mode = ASYNC_BUFFER;
	async_tx.buffer = data;
	async_tx.size = size;
	async_tx.index = 0;
	async_tx.cb_done = cb_done;
	async_tx.cb_p = p;
	async_tx.active = true;

	// The UDR ISR will be called as soon as this is enabled,
	// and the state machine will take over from there.
	set_udrie(true);

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_string(char *string, size_t max_len)
{
	while (!transmitter_ready())
	{
		// Wait for transmitter
	}

	size_t i = 0;
	while (*string && i < max_len)
	{
		transmit_byte((uint8_t)*string++);
		i++;
	}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_string_async(char *string, size_t max_len, usarttx_callback_t cb_done, void *p)
{
	if (!transmitter_ready())
		return USART_IO_BUSY;

	// Reset the state machine
	async_tx.mode = ASYNC_STRING;
	async_tx.buffer = (uint8_t*)string;
	async_tx.size = max_len;
	async_tx.index = 0;
	async_tx.cb_done = cb_done;
	async_tx.cb_p = p;
	async_tx.active = true;

	// The UDR ISR will be called as soon as this is enabled,
	// and the state machine will take over from there.
	set_udrie(true);

	return USART_IO_SUCCESS;
}


int16_t Usart_imp::receive_byte(void)
{
	while (!receiver_has_data())
	{
		// Wait for data
	}

	// Errors must be read before UDR
	Usart_error_status error = get_errors();
	if (error != USART_ERR_NONE)
		return (int16_t)error;

	// 9 bit mode
	if (bit_read(*registers.UCSRB, UCSZ2_BIT) == 1)
	{
		uint8_t bit8 = bit_read(*registers.UCSRB, RXB8_BIT);
		return (bit8 << 8) | (*registers.UDR);
	}

	return *registers.UDR;
}

int16_t Usart_imp::receive_byte_async(void)
{
	if (!receiver_has_data())
		return USART_IO_NODATA;

	// Errors must be read before UDR
	Usart_error_status error = get_errors();
	if (error != USART_ERR_NONE)
		return (int16_t)error;

	// 9 bit mode
	if (bit_read(*registers.UCSRB, UCSZ2_BIT) == 1)
	{
		uint8_t bit8 = bit_read(*registers.UCSRB, RXB8_BIT);
		return (bit8 << 8) | (*registers.UDR);
	}

	return *registers.UDR;
}


Usart_io_status Usart_imp::receive_buffer(uint8_t *buffer, size_t size)
{
	// No need to wait for data here, since receive_byte() will wait anyway.

	for (size_t i = 0; i < size; i++)
	{
		int16_t data = receive_byte();

		// An error occurred, abort
		if (data < 0)
		{
			return USART_IO_FAILED; // TODO - How to get the actual error status flag out?
		}

		*buffer = (uint8_t)data;
		buffer++;
	}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::receive_buffer_async(uint8_t *data, size_t size, usartrx_callback_t cb_done, void *p)
{
	if (async_rx.active)
		return USART_IO_BUSY;

	// Reset the state machine
	async_rx.buffer = data;
	async_rx.size = size;
	async_rx.index = 0;
	async_rx.cb_done = cb_done;
	async_rx.cb_p = p;
	async_rx.active = true;

	// The RX interrupt will take over from here

	return USART_IO_SUCCESS;
}


void Usart_imp::enable_interrupts(void)
{
	if (tx_isr) tx_isr_enabled = true;
	if (rx_isr) rx_isr_enabled = true;
}

void Usart_imp::disable_interrupts(void)
{
	tx_isr_enabled = false;
	rx_isr_enabled = false;
}

Usart_int_status Usart_imp::attach_interrupt(Usart_interrupt_type type, callback_t callback, void* p)
{
	switch (type)
	{
		case USART_INT_TX_COMPLETE:
		{
			if (tx_isr != NULL)
				return USART_INT_INUSE;

			tx_isr_p = p;
			tx_isr = callback;
			break;
		};

		case USART_INT_RX_COMPLETE:
		{
			if (rx_isr != NULL)
				return USART_INT_INUSE;

			rx_isr_p = p;
			rx_isr = callback;
			break;
		};

		// Unsupported interrupt type
		default:
			return USART_INT_FAILED;
	}

	return USART_INT_SUCCESS;
}

Usart_int_status Usart_imp::detach_interrupt(Usart_interrupt_type type)
{
	// Make sure to disable interrupts before we go modifying the ISR pointers!
	cli();

	switch (type)
	{
		case USART_INT_TX_COMPLETE:
		{
			// NOTE - No need to check if it's already cleared.
			tx_isr = NULL;
			tx_isr_p = NULL;
			tx_isr_enabled = false;
			break;
		};

		case USART_INT_RX_COMPLETE:
		{
			rx_isr = NULL;
			rx_isr_p = NULL;
			rx_isr_enabled = false;
			break;
		};

		// Unsupported interrupt type
		default:
		{
			sei();
			return USART_INT_FAILED;
		}
	}

	sei();
	return USART_INT_SUCCESS;
}

Usart_error_status Usart_imp::get_errors(void)
{
	// TODO - what if there are multiple errors?
	if (bit_read(*registers.UCSRA, FE_BIT))
		return USART_ERR_FRAME;
	if (bit_read(*registers.UCSRA, DOR_BIT))
		return USART_ERR_DATA_OVERRUN;
	if (bit_read(*registers.UCSRA, UPE_BIT))
		return USART_ERR_PARITY;

	return USART_ERR_NONE;
}


//// Utility Functions ////

Usart_config_status Usart_imp::set_mode(Usart_setup_mode mode)
{
	switch (mode)
	{
		case USART_MODE_ASYNCHRONOUS:
		case USART_MODE_ASYNCHRONOUS_DOUBLESPEED:
		{
			// UMSEL<1:0> = 0b00 (Asynchronous mode)
			reg_write(*registers.UCSRC, UMSEL0_BIT, 2, 0b00);

			// Enable double-speed mode
			if (mode == USART_MODE_ASYNCHRONOUS_DOUBLESPEED)
				bit_write(*registers.UCSRA, U2X_BIT, 1);

			break;
		}

		case USART_MODE_SYNCHRONOUS_MASTER:
		case USART_MODE_SYNCHRONOUS_SLAVE:
		{
			// UMSEL<1:0> = 0b01 (Synchronous mode)
			reg_write(*registers.UCSRC, UMSEL0_BIT, 2, 0b01);

			// For synchronous mode, clear the double USART transmission speed bit
			bit_write(*registers.UCSRA, U2X_BIT, 0);

			// Configure the GPIO
			Gpio_pin xck(pins.xck_address);

			// Master/slave is defined by the direction of the XCK pin
			if (mode == USART_MODE_SYNCHRONOUS_MASTER)
				xck.set_mode(GPIO_OUTPUT_PP);
			else
				xck.set_mode(GPIO_INPUT_FL);

			break;
		}

		// Unsupported configuration
		default:
			return USART_CFG_INVALID_MODE;
	}
	this->mode = mode;

	return USART_CFG_SUCCESS;
}

Usart_config_status Usart_imp::set_framing(uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	// Data bits
	if ((data_bits < 5) || (data_bits > 9))
		return USART_CFG_INVALID_DATA_BITS;

	if (data_bits == 9)
	{
		// UCSZ = 0b100
		bit_write(*registers.UCSRB, UCSZ2_BIT, 1); // 9-bit mode
		reg_write(*registers.UCSRC, UCSZ0_BIT, 2, 0b00);
	}
	else // (data_bits <= 8)
	{
		// UCSZ = 0b0xx
		uint8_t ucsz = (data_bits - 5);

		bit_write(*registers.UCSRB, UCSZ2_BIT, 0); // regular mode
		reg_write(*registers.UCSRC, UCSZ0_BIT, 2, ucsz);
	}

	// Parity
	switch (parity)
	{
		case USART_PARITY_EVEN:
			reg_write(*registers.UCSRC, UPM0_BIT, 2, 0b10);
			break;

		case USART_PARITY_ODD:
			reg_write(*registers.UCSRC, UPM0_BIT, 2, 0b11);
			break;

		case USART_PARITY_NONE:
			reg_write(*registers.UCSRC, UPM0_BIT, 2, 0b00);
			break;

		default: // Unsupported parity mode
			return USART_CFG_INVALID_PARITY;
	}

	// Stop bits
	switch (stop_bits)
	{
		case 1:
			bit_write(*registers.UCSRC, USBS_BIT, 0);
			break;

		case 2:
			bit_write(*registers.UCSRC, USBS_BIT, 1);
			break;

		default: // Invalid number of stop bits
			return USART_CFG_INVALID_STOP_BITS;
	}

	return USART_CFG_SUCCESS;
}

Usart_config_status Usart_imp::set_baud_rate(uint32_t baud_rate)
{
	// Calculate the Baud value required for the user provided Baud rate
	// Baud value = F_CPU			- 1
	// 		     --------------------
	// 		     (User_Baud_rate * K)
	//
	// Where K varies depending on which mode the USART is set to.
	//
	// Asynchronous mode (U2Xn = 0)	K = 16
	// Asynchronous mode (U2Xn = 1)	K = 8
	// Synchronous Master mode		K = 2

	uint32_t K;

	if (mode == USART_MODE_ASYNCHRONOUS)
		K = 16UL;
	else if (mode == USART_MODE_ASYNCHRONOUS_DOUBLESPEED)
		K = 8UL;
	else if (mode == USART_MODE_SYNCHRONOUS_MASTER || mode == USART_MODE_SYNCHRONOUS_SLAVE)
		K = 2UL;
	else
		return USART_CFG_INVALID_MODE;

	// Set the UBBR value according to the equation above
	uint32_t ubrr = ((((uint32_t)F_CPU / (baud_rate * K))) - 1);
	if (ubrr > 65535)
		return USART_CFG_INVALID_BAUD_RATE;

	*registers.UBRR = (uint16_t)ubrr;

	return USART_CFG_SUCCESS;
}


//// Asynchronous Interrupt Handling ////

void Usart_imp::set_udrie(bool enabled)
{
	bit_write(*registers.UCSRB, UDRIE_BIT, enabled);
}

void Usart_imp::isr_receive_byte(void)
{
	// This interrupt is triggered when a byte has been received
	// NOTE - This ISR can be used for both Usart_imp and Lin_imp,
	//  since it uses common functionality.

	if (async_rx.active)
	{
		// Check errors
		Usart_error_status error_status = get_errors();

		// Receive byte
		// NOTE - *registers.UDR points to LINDAT for Lin_imp.
		uint8_t data = *registers.UDR;

		// It doesn't matter if we write data if an error occurred,
		// since it'll get discared anyway
		async_rx.buffer[async_rx.index++] = (uint8_t) data;

		// Fully received the buffer, or an error occurred
		if ((async_rx.index == async_rx.size) || (error_status != USART_ERR_NONE))
		{
			async_rx.active = false;

			// Inform the user the data has been received
			if (async_rx.cb_done)
			{
				if (error_status != USART_ERR_NONE)
				{
					Usart_error_status error = (Usart_error_status) data;
					async_rx.cb_done(async_rx.cb_p, error, NULL, 0);
				}
				else
				{
					async_rx.cb_done(async_rx.cb_p, USART_ERR_NONE, async_rx.buffer, async_rx.index);
				}
			}

			// Call the user ISR to tell that data has finished being received
			if (rx_isr && rx_isr_enabled)
				rx_isr(rx_isr_p);
		}
	}

	// Only process user ISR if no async operations are running
	else
	{
		if (rx_isr && rx_isr_enabled)
			rx_isr(rx_isr_p);

		// Make sure the byte is read to clear the interrupt flag!
		// If this is not done, it affects the UDRE interrupt ???
		if (receiver_has_data())
		{
			volatile uint8_t data __attribute__((unused)) = *registers.UDR;
		}
	}
}

void Usart_imp::isr_transmit_complete(void)
{
	// This interrupt is triggered only when the transmission is complete
	// and there is no new data to be sent

	// Unused.
}

void Usart_imp::isr_transmit_ready(void)
{
	// This interrupt is triggered when the transmitter is ready
	// to send more data, and UDRIE is enabled.
	//
	// This interrupt must either load more data into UDR,
	// or disable the ISR, otherwise it will keep getting called!

	if (async_tx.active)
	{
		// Send the next byte
		uint8_t data = async_tx.buffer[async_tx.index++];
		bool null_char = (async_tx.mode == ASYNC_STRING && data == '\0');

		// Don't send the null char
		if (!null_char)
		{
			*registers.UDR = data;
		}

		// No more bytes to send!
		if ((async_tx.index == async_tx.size) || null_char)
		{
			// Stop async machine
			async_tx.active = false;

			// Disable the UDR interrupt
			set_udrie(false);

			//Usart_io_status status = USART_IO_SUCCESS;

			// We reached max_len before finding a null char
			//if (async_tx.mode == ASYNC_STRING && data != '\0')
			//	status = USART_IO_STRING_TRUNCATED;

			// Inform the user the data has been sent
			if (async_tx.cb_done != NULL)
				async_tx.cb_done(async_tx.cb_p, USART_ERR_NONE);

			// Call the user ISR to indicate the transmitter is free to send more data
			if (tx_isr && tx_isr_enabled)
				tx_isr(tx_isr_p);
		}
	}
	// Only process user ISR if no async operations are running
	else
	{
		// Call the user ISR, which can be used to load more data into UDR.
		// The callback should return a bool, which should be set to true
		// when the user has no more data to send.
		if (tx_isr && tx_isr_enabled)
			tx_isr(tx_isr_p);

		// Explicitly clear the UDRIE flag in case they didn't load more data
		set_udrie(false);
	}
}





////// Lin_imp Implementation //////

#ifdef USE_USART_LIN

/**
 * The ATmega64M1/C1 chips can support basic UART through the LIN peripheral.
 * This class overrides the behaviour in Usart_imp to make the LIN
 * peripheral function as a UART.
 *
 * The LIN-UART has restricted functionality, and only supports
 * 8 data bits, odd/even/no parity, and 1 stop bit
 */

Lin_imp::Lin_imp(Usart_channel channel, Usart_pins pins)
	: Usart_imp(channel, pins,
		(Usart_registers){.UDR=&LINDAT} // So the underlying async functions know where the data is.
) {}

Lin_imp::~Lin_imp(void) { }

void Lin_imp::enable(void)
{
	// Enable LIN module
	bit_write(LINCR, LENA, 1);

	// Enable interrupts
	LINENIR |= _BV(LENTXOK) | _BV(LENRXOK);
}

void Lin_imp::disable(void)
{
	bit_write(LINCR, LENA, 0);
	//TODO: Does disable clear the current configuration?

	// Disable interrupts
	LINENIR &= ~(_BV(LENTXOK) | _BV(LENRXOK));
}

void Lin_imp::flush(void)
{
	while (receiver_has_data())
	{
		volatile uint8_t __attribute__((unused)) dummy = LINDAT;
	}
}

Usart_config_status Lin_imp::configure(Usart_setup_mode mode, uint32_t baud_rate, uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	return Usart_imp::configure(mode, baud_rate, data_bits, parity, stop_bits);
}

bool Lin_imp::transmitter_ready(void)
{
	// The LBUSY flag signals that the controller is busy with UART communication.
	// TODO - Unsure if LTXOK is needed, but things seem to function fine so far...
	return (bit_read(LINSIR, LBUSY) == 0) /*&& ((LINSIR & _BV(LTXOK)) == 0)*/;
}

bool Lin_imp::receiver_has_data(void)
{
	// The LRXOK flag is set when a byte of data has been received.
	// It is cleared when the data is read from LINDAT.
	return (bit_read(LINSIR, LRXOK) == 1);
}


Usart_io_status Lin_imp::transmit_byte(uint8_t data)
{
	while (!transmitter_ready())
	{
		// Wait for transmit buffer to be empty
	}

	LINDAT = data;

	return USART_IO_SUCCESS;
}

Usart_io_status Lin_imp::transmit_byte_async(uint8_t data)
{
	if (!transmitter_ready())
		return USART_IO_BUSY;

	LINDAT = data;

	// If the user wants to use the TX ready ISR to transmit more data, trigger it.
	if (tx_isr && tx_isr_enabled)
		set_udrie(true);

	return USART_IO_SUCCESS;
}

// NOTE: The following functions do not need to be overridden:
// 	transmit_buffer()  transmit_buffer_async()
// 	transmit_string()  transmit_string_async()

int16_t Lin_imp::receive_byte(void)
{
	while (!receiver_has_data())
	{
		// Wait for data
	}

	// Errors must be read before UDR
	Usart_error_status error = get_errors();
	if (error != USART_ERR_NONE)
		return (int16_t)error;

	return LINDAT;
}

int16_t Lin_imp::receive_byte_async(void)
{
	if (!receiver_has_data())
		return USART_IO_NODATA;

	// Errors must be read before UDR
	Usart_error_status error = get_errors();
	if (error != USART_ERR_NONE)
		return (int16_t) error;

	return LINDAT;
}

// NOTE: The following functions do not need to be overridden:
// 	receive_buffer()  receive_buffer_async()

// NOTE: The following functions do not need to be overridden:
// 	enable_interrupts()  disable_interrupts()
//  attach_interrupt()  detach_interrupt()


Usart_error_status Lin_imp::get_errors(void)
{
	if (bit_read(LINERR, LOVERR))
		return USART_ERR_DATA_OVERRUN;
	if (bit_read(LINERR, LFERR))
		return USART_ERR_FRAME;
	if (bit_read(LINERR, LPERR))
		return USART_ERR_PARITY;

	// Other error flags are only relevant for LIN.

	return USART_ERR_NONE;
}

Usart_config_status Lin_imp::set_mode(Usart_setup_mode mode)
{
	// NOTE - This is called by Usart_imp::configure()

	if (mode != USART_MODE_ASYNCHRONOUS)
		return USART_CFG_INVALID_MODE;

	// Put the LIN peripheral into UART mode, with RX/TX enabled.
	reg_write(LINCR, LCMD0, 3, 0b111);

	this->mode = mode;

	return USART_CFG_SUCCESS;
}

Usart_config_status Lin_imp::set_framing(uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	// NOTE - This is called by Usart_imp::configure()

	// The LIN module only supports 8 data bits and 1 stop bit, nothing else.

	if (data_bits != 8)
		return USART_CFG_INVALID_DATA_BITS;

	if (stop_bits != 1)
		return USART_CFG_INVALID_STOP_BITS;

	switch (parity)
	{
		case USART_PARITY_NONE:
		{
			reg_write(LINCR, LCONF0, 2, 0b00); // 8-bit, no parity, listen off
			break;
		};
		case USART_PARITY_EVEN:
		{
			reg_write(LINCR, LCONF0, 2, 0b01); // 8-bit, even parity, listen off
			break;
		};
		case USART_PARITY_ODD:
		{
			reg_write(LINCR, LCONF0, 2, 0b10); // 8-bit, odd parity, listen off
			break;
		};

		default:
			return USART_CFG_INVALID_PARITY;
	}

	return USART_CFG_SUCCESS;
}

Usart_config_status Lin_imp::set_baud_rate(uint32_t baud_rate)
{
	// NOTE - This is called by Usart_imp::configure()
	// NOTE - LENA must be zero before LINBTR can be changed

	// Highest supported baud rate is: fclk/8
	// For best results, choose a baud rate fclk/(8n) for some integer n.
	// Eg, at fclk=16MHz, supported baud rates are 2Mbaud, 1M, 0.67M, 0.5M, 0.4M, 0.33M, etc.
	// Baudrates that do not lie on these values will truncate to the nearest integer, and the
	// error produced by this will be worse for fast baud rates.

	// BAUD = fclkIO / (LBT[5..0] x (LDIV[11..0] + 1))		where LDIV is 0..4095
	// LDIV[11..0] = (fclkIO / (LBT[5..0] x BAUD)) - 1		where LBT is 8..63

	const uint32_t lbt = 8;
	uint32_t ldiv = ((uint32_t)F_CPU / lbt / baud_rate) - 1;

	if (ldiv > 4095)
		return USART_CFG_INVALID_BAUD_RATE;

	LINBRR = (uint16_t)ldiv;
	LINBTR = _BV(LDISR) | (lbt & 0x3F);  // LBT

	return USART_CFG_SUCCESS;
}

void Lin_imp::set_udrie(bool enabled)
{
	// The LIN peripheral does not have a UDRE interrupt like the native USART peripheral.
	// We can emulate it by calling the transmit_ready ISR here.
	// The TXOK ISR will continue to be triggered as long as LTXOK is not cleared (Adding data to LINSIR will clear LTXOK).
	if (enabled)
	{
		// Note - set_udrie(true) should not be called from within isr_transmit_ready().
		isr_transmit_ready();
	}
	else
	{
		bit_write(LINSIR, LTXOK, 1); // Clear
	}
}


#endif // USE_USART_LIN





// DECLARE PRIVATE GLOBAL VARIABLES.

// NOTE - Instead of hard-coding specific AVR chips,
// we use constants defined in <target_config.hpp> to specify which
// peripherals are present, and which channel corresponds to each peripheral.

#ifdef USE_USART0
Usart_imp usart0_imp = Usart_imp(
	USE_USART0, // Channel
	(Usart_pins) {
		// Pins are defined in <target_config.hpp>
		.tx_address  = _IOADDR(USART0_TX_PORT, USART0_TX_PIN),
		.rx_address  = _IOADDR(USART0_RX_PORT, USART0_RX_PIN),
		.xck_address = _IOADDR(USART0_XCK_PORT, USART0_XCK_PIN)
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR    = &UDR0,
		.UCSRA  = &UCSR0A,
		.UCSRB  = &UCSR0B,
		.UCSRC  = &UCSR0C,
		.UBRR   = &UBRR0
	}
);
#endif

#ifdef USE_USART1
Usart_imp usart1_imp = Usart_imp(
	USE_USART1, // Channel
	(Usart_pins) {
		// Pins are defined in <target_config.hpp>
		.tx_address  = _IOADDR(USART1_TX_PORT, USART1_TX_PIN),
		.rx_address  = _IOADDR(USART1_RX_PORT, USART1_RX_PIN),
		.xck_address = _IOADDR(USART1_XCK_PORT, USART1_XCK_PIN)
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR    = &UDR1,
		.UCSRA  = &UCSR1A,
		.UCSRB  = &UCSR1B,
		.UCSRC  = &UCSR1C,
		.UBRR   = &UBRR1
	}
);
#endif

#ifdef USE_USART2
Usart_imp usart2_imp = Usart_imp(
	USE_USART2, // Channel
	(Usart_pins) {
		// Pins are defined in <target_config.hpp>
		.tx_address  = _IOADDR(USART2_TX_PORT, USART2_TX_PIN),
		.rx_address  = _IOADDR(USART2_RX_PORT, USART2_RX_PIN),
		.xck_address = _IOADDR(USART2_XCK_PORT, USART2_XCK_PIN)
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR	= &UDR2,
		.UCSRA	= &UCSR2A,
		.UCSRB	= &UCSR2B,
		.UCSRC	= &UCSR2C,
		.UBRR	= &UBRR2
	}
);
#endif

#ifdef USE_USART3
Usart_imp usart3_imp = Usart_imp(
	USE_USART3, // Channel
	(Usart_pins) {
		// Pins are defined in <target_config.hpp>
		.tx_address  = _IOADDR(USART3_TX_PORT, USART3_TX_PIN),
		.rx_address  = _IOADDR(USART3_RX_PORT, USART3_RX_PIN),
		.xck_address = _IOADDR(USART3_XCK_PORT, USART3_XCK_PIN)
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR	= &UDR3,
		.UCSRA	= &UCSR3A,
		.UCSRB	= &UCSR3B,
		.UCSRC	= &UCSR3C,
		.UBRR	= &UBRR3
	}
);
#endif

#ifdef USE_USART_LIN
// NOTE the use of 'Lin_imp' instead of 'Usart_imp' : The peripheral is completely different!
static Lin_imp usart_lin_imp = Lin_imp(
	USE_USART_LIN, // Channel
	(Usart_pins) {
		// Pins are defined in <target_config.hpp>
		.tx_address  = _IOADDR(USARTLIN_TX_PORT, USARTLIN_TX_PIN),
		.rx_address  = _IOADDR(USARTLIN_RX_PORT, USARTLIN_RX_PIN),
	}
);
#endif




Usart::Usart(Usart_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	imp->bind();
}

Usart::~Usart(void)
{
	imp->unbind();
}

Usart Usart::bind(Usart_channel channel)
{
	// Acquire access to the implementation instance.
	// TODO: What do we do if this fails, or if someone has already binded to the instance??

	// TODO - Check thread-safety of this. It is only guaranteed to be thread-safe under C++11??

	switch (channel)
	{

#if defined(USE_USART0) // Most AVR chips have a USART 0
		case USE_USART0:
		{
			return Usart(&usart0_imp);
		}
#endif

#if defined(USE_USART1) // Some AVR chips have multiple USARTs
		case USE_USART1:
		{
			return Usart(&usart1_imp);
		}
#endif

#if defined(USE_USART2)
		case USE_USART2:
		{
			return Usart(&usart2_imp);
		}
#endif

#if defined(USE_USART3)
		case USE_USART3:
		{
			return Usart(&usart3_imp);
		}
#endif

#if defined(USE_USART_LIN) // ATmega32M1/C1 chips only have LIN
		case USE_USART_LIN:
		{
			return Usart(&usart_lin_imp);
		}
#endif

	} // end-switch

	// If we make it to here, then something has gone very wrong (like the user maliciously cast an invalid value into a channel number).

	// Loop forever, which hopefully reboots the micro so we have a chance to recover.
	while (true)
	{
		// Consider the bad life choices that have led us to this point.
	}

	// We'll never get here.
	return Usart(static_cast<Usart_imp*>(NULL));
}

void Usart::enable()
{
	imp->enable();
}

void Usart::disable()
{
	imp->disable();
}

void Usart::flush()
{
	imp->flush();
}

Usart_config_status Usart::configure(Usart_setup_mode mode, uint32_t baud_rate, uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	return imp->configure(mode, baud_rate, data_bits, parity, stop_bits);
}

bool Usart::transmitter_ready()
{
	return imp->transmitter_ready();
}

bool Usart::receiver_has_data()
{
	return imp->receiver_has_data();
}

Usart_io_status Usart::transmit_byte(uint8_t data)
{
	return imp->transmit_byte(data);
}

Usart_io_status Usart::transmit_byte_async(uint8_t data)
{
	return imp->transmit_byte_async(data);
}

Usart_io_status Usart::transmit_buffer(uint8_t *data, size_t size)
{
	return imp->transmit_buffer(data, size);
}

Usart_io_status Usart::transmit_buffer_async(uint8_t *data, size_t size, usarttx_callback_t cb_done)
{
	return imp->transmit_buffer_async(data, size, cb_done);
}

Usart_io_status Usart::transmit_string(char *data, size_t max_len)
{
	return imp->transmit_string(data, max_len);
}

Usart_io_status Usart::transmit_string_async(char *data, size_t max_len, usarttx_callback_t cb_done)
{
	return imp->transmit_string_async(data, max_len, cb_done);
}

int16_t Usart::receive_byte(void)
{
	return imp->receive_byte();
}

int16_t Usart::receive_byte_async(void)
{
	return imp->receive_byte_async();
}

Usart_io_status Usart::receive_buffer(uint8_t *data, size_t size)
{
	return imp->receive_buffer(data, size);
}

Usart_io_status Usart::receive_buffer_async(uint8_t *data, size_t size, usartrx_callback_t cb_done)
{
	return imp->receive_buffer_async(data, size, cb_done);
}

void Usart::enable_interrupts()
{
	imp->enable_interrupts();
}

void Usart::disable_interrupts()
{
	imp->enable_interrupts();
}

Usart_int_status Usart::attach_interrupt(Usart_interrupt_type type, callback_t callback, void *p)
{
	return imp->attach_interrupt(type, callback, p);
}

Usart_int_status Usart::detach_interrupt(Usart_interrupt_type type)
{
	return imp->detach_interrupt(type);
}

Usart_error_status Usart::usart_error(void)
{
	return imp->get_errors();
}

void Usart::usart_clear_errors()
{
	imp->get_errors();
}


/** Declare the ISR handlers
 * 
 * Each USART interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs which are contained within the specific USART implementation.
 *
 * Note that the usartX_imp pointers are guaranteed to be non-NULL because the ISRs
 * are not enabled until after the pointer has been set. (see: Usart::bind() and Usart::attach_interrupt())
 * */

#ifdef USE_USART0
ISR(USART0_RX_vect)
{
	usart0_imp.isr_receive_byte();

	// NOTE - The RXC flag is automatically cleared when UDR is read,
	// but clear the RXC flag anyway as a safeguard
	bit_clear(UCSR0A, RXC_BIT);
}

ISR(USART0_TX_vect)
{
	usart0_imp.isr_transmit_complete();
	// TXC flag is cleared automatically
}

ISR(USART0_UDRE_vect)
{
	usart0_imp.isr_transmit_ready();
}
#endif

#ifdef USE_USART1
ISR(USART1_RX_vect)
{
	usart1_imp.isr_receive_byte();
	bit_clear(UCSR1A, RXC_BIT);
}

ISR(USART1_TX_vect)
{
	usart1_imp.isr_transmit_complete();
}

ISR(USART1_UDRE_vect)
{
	usart1_imp.isr_transmit_ready();
}
#endif

#ifdef USE_USART2
ISR(USART2_RX_vect)
{
	usart2_imp.isr_receive_byte();
	bit_clear(UCSR2A, RXC_BIT);
}

ISR(USART2_TX_vect)
{
	usart2_imp.isr_transmit_complete();
}

ISR(USART2_UDRE_vect)
{
	usart2_imp.isr_transmit_ready();
}
#endif

#ifdef USE_USART3
ISR(USART3_RX_vect)
{
	usart3_imp.isr_receive_byte();
	bit_clear(UCSR3A, RXC_BIT);
}

ISR(USART3_TX_vect)
{
	usart3_imp.isr_transmit_complete();
}

ISR(USART3_UDRE_vect)
{
	usart3_imp.isr_transmit_ready();
}
#endif

#ifdef USE_USART_LIN
ISR(LIN_TC_vect)
{
	if (bit_read(LINSIR, LRXOK))
	{
		usart_lin_imp.isr_receive_byte();
		return;
	}

	if (bit_read(LINSIR, LTXOK))
	{
		usart_lin_imp.isr_transmit_complete();
		usart_lin_imp.isr_transmit_ready(); // The LIN doesn't have a separate "UDRE" status flag
		return;
	}

	// LIDOK is not generated in UART mode.
}

/*ISR(LIN_ERR_vect)
{
	// Not used
}*/
#endif

// ALL DONE.
