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

/**
 * -----------------------------------------------------------------------------------------------------
 * @addtogroup		I2C Library
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @file		I2C_platform.hpp
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @brief 		Header file containing platform dependent types and enums for the I2C module.
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @author		Kevin Gong
 *
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @date		1-12-2014
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @section 	Licence
 *
 * Copyright (C) 2014  Unison Networks Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @section 	Description
 *
 * [See BRIEF]
 * -----------------------------------------------------------------------------------------------------
 */


#ifndef __I2C_PLATFORM_H__
#define __I2C_PLATFORM_H__

// REQUIRED HEADER FILES.
#include <stdint.h>

# define MAX_SCL_CPU_RATIO     16

# define READ     1
# define WRITE     0

# define TWCR_START       (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|(0<<TWWC)
# define TWCR_DATA_NAK       (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)
# define TWCR_DATA_ACK       (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|(0<<TWWC)
# define TWCR_STOP       (1<<TWEN)|(0<<TWIE)|(1<<TWINT)|(0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|(0<<TWWC)

//////////////////////// Insert io.h data here if decided to not use avr/io.h /////////////////////////

/******************************************************************************************************/

// TODO: get addresses on the power management board

#endif /*__I2C_PLATFORM_H__*/

// ALL DONE.
