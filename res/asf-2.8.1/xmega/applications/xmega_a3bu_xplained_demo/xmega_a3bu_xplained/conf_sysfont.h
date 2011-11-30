/**
 * \file
 *
 * \brief Default configurations for sysfont
 *
 * Copyright (C) 2009 - 2011 Atmel Corporation. All rights reserved.
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
#ifndef CONF_SYSFONT_H
#define CONF_SYSFONT_H

/**
 * \weakgroup gfx_mono_sysfont
 * @{
 */

#include <stdint.h>

#include "gfx_mono.h"

//! Width of each glyph, including spacer column.
#define SYSFONT_WIDTH           6
//! Height of each glyph, excluding spacer line.
#define SYSFONT_HEIGHT          7
//! Line height.
#define SYSFONT_LINESPACING     8
//! First character defined.
#define SYSFONT_FIRSTCHAR       ((uint8_t) ' ')
//! Last character defined.
#define SYSFONT_LASTCHAR        ((uint8_t) 127)

//! Define variable containing the font
#define SYSFONT_DEFINE_GLYPHS                                           \
/* Glyph data, row by row, MSB is leftmost pixel, one byte per row. */  \
static PROGMEM_DECLARE(uint8_t, sysfont_glyphs[]) = {                   \
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* "(space)" */      \
	0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20,  /* "!" */            \
	0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00,  /* """ */            \
	0x50, 0x50, 0xf8, 0x50, 0xf8, 0x50, 0x50,  /* "#" */            \
	0x20, 0x78, 0xa0, 0x70, 0x28, 0xf0, 0x20,  /* "$" */            \
	0xc0, 0xc8, 0x10, 0x20, 0x40, 0x98, 0x18,  /* "%" */            \
	0x60, 0x90, 0xa0, 0x40, 0xa8, 0x90, 0x68,  /* "&" */            \
	0x60, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00,  /* "'" */            \
	0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10,  /* "(" */            \
	0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40,  /* ")" */            \
	0x00, 0x50, 0x20, 0xf8, 0x20, 0x50, 0x00,  /* "*" */            \
	0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00,  /* "+" */            \
	0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0x40,  /* "," */            \
	0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00,  /* "-" */            \
	0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60,  /* "." */            \
	0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00,  /* "/" */            \
	0x70, 0x88, 0x98, 0xa8, 0xc8, 0x88, 0x70,  /* "0" */            \
	0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70,  /* "1" */            \
	0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xf8,  /* "2" */            \
	0xf8, 0x10, 0x20, 0x10, 0x08, 0x88, 0x70,  /* "3" */            \
	0x10, 0x30, 0x50, 0x90, 0xf8, 0x10, 0x10,  /* "4" */            \
	0xf8, 0x80, 0xf0, 0x08, 0x08, 0x88, 0x70,  /* "5" */            \
	0x30, 0x40, 0x80, 0xf0, 0x88, 0x88, 0x70,  /* "6" */            \
	0xf8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40,  /* "7" */            \
	0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70,  /* "8" */            \
	0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60,  /* "9" */            \
	0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00,  /* ":" */            \
	0x00, 0x60, 0x60, 0x00, 0x60, 0x20, 0x40,  /* ";" */            \
	0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08,  /* "<" */            \
	0x00, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0x00,  /* "=" */            \
	0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80,  /* ">" */            \
	0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20,  /* "?" */            \
	0x70, 0x88, 0x08, 0x68, 0xa8, 0xa8, 0x70,  /* "@" */            \
	0x70, 0x88, 0x88, 0x88, 0xf8, 0x88, 0x88,  /* "A" */            \
	0xf0, 0x88, 0x88, 0xf0, 0x88, 0x88, 0xf0,  /* "B" */            \
	0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70,  /* "C" */            \
	0xe0, 0x90, 0x88, 0x88, 0x88, 0x90, 0xe0,  /* "D" */            \
	0xf8, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8,  /* "E" */            \
	0xf8, 0x80, 0x80, 0xe0, 0x80, 0x80, 0x80,  /* "F" */            \
	0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x70,  /* "G" */            \
	0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88,  /* "H" */            \
	0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,  /* "I" */            \
	0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60,  /* "J" */            \
	0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x88,  /* "K" */            \
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf8,  /* "L" */            \
	0x88, 0xd8, 0xa8, 0x88, 0x88, 0x88, 0x88,  /* "M" */            \
	0x88, 0x88, 0xc8, 0xa8, 0x98, 0x88, 0x88,  /* "N" */            \
	0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,  /* "O" */            \
	0xf0, 0x88, 0x88, 0xf0, 0x80, 0x80, 0x80,  /* "P" */            \
	0x70, 0x88, 0x88, 0x88, 0xa8, 0x90, 0x68,  /* "Q" */            \
	0xf0, 0x88, 0x88, 0xf0, 0xa0, 0x90, 0x88,  /* "R" */            \
	0x78, 0x80, 0x80, 0x70, 0x08, 0x08, 0xf0,  /* "S" */            \
	0xf8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,  /* "T" */            \
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,  /* "U" */            \
	0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20,  /* "V" */            \
	0x88, 0x88, 0x88, 0xa8, 0xa8, 0xd8, 0x88,  /* "W" */            \
	0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88,  /* "X" */            \
	0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20,  /* "Y" */            \
	0xf8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xf8,  /* "Z" */            \
	0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38,  /* "[" */            \
	0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00,  /* "\" */            \
	0xe0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xe0,  /* "]" */            \
	0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00,  /* "^" */            \
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,  /* "_" */            \
	0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00,  /* "`" */            \
	0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78,  /* "a" */            \
	0x80, 0x80, 0xb0, 0xc8, 0x88, 0x88, 0xf0,  /* "b" */            \
	0x00, 0x00, 0x70, 0x80, 0x80, 0x88, 0x70,  /* "c" */            \
	0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x78,  /* "d" */            \
	0x00, 0x00, 0x70, 0x88, 0xf8, 0x80, 0x70,  /* "e" */            \
	0x30, 0x48, 0x40, 0xe0, 0x40, 0x40, 0x40,  /* "f" */            \
	0x00, 0x00, 0x78, 0x88, 0x78, 0x08, 0x30,  /* "g" */            \
	0x80, 0x80, 0xb0, 0xc8, 0x88, 0x88, 0x88,  /* "h" */            \
	0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70,  /* "i" */            \
	0x10, 0x00, 0x30, 0x10, 0x10, 0x90, 0x60,  /* "j" */            \
	0x40, 0x40, 0x48, 0x50, 0x60, 0x50, 0x48,  /* "k" */            \
	0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,  /* "l" */            \
	0x00, 0x00, 0xd0, 0xa8, 0xa8, 0x88, 0x88,  /* "m" */            \
	0x00, 0x00, 0xb0, 0xc8, 0x88, 0x88, 0x88,  /* "n" */            \
	0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70,  /* "o" */            \
	0x00, 0x00, 0xf0, 0x88, 0xf0, 0x80, 0x80,  /* "p" */            \
	0x00, 0x00, 0x68, 0x98, 0x78, 0x08, 0x08,  /* "q" */            \
	0x00, 0x00, 0xb0, 0xc8, 0x80, 0x80, 0x80,  /* "r" */            \
	0x00, 0x00, 0x70, 0x80, 0x70, 0x08, 0xf0,  /* "s" */            \
	0x40, 0x40, 0xe0, 0x40, 0x40, 0x48, 0x30,  /* "t" */            \
	0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68,  /* "u" */            \
	0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20,  /* "v" */            \
	0x00, 0x00, 0x88, 0x88, 0xa8, 0xa8, 0x50,  /* "w" */            \
	0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88,  /* "x" */            \
	0x00, 0x00, 0x88, 0x88, 0x78, 0x08, 0x70,  /* "y" */            \
	0x00, 0x00, 0xf8, 0x10, 0x20, 0x40, 0xf8,  /* "z" */            \
	0x10, 0x20, 0x20, 0x40, 0x20, 0x20, 0x10,  /* "{" */            \
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,  /* "|" */            \
	0x40, 0x20, 0x20, 0x10, 0x20, 0x20, 0x40,  /* "}" */            \
	0x00, 0x20, 0x10, 0xf8, 0x10, 0x20, 0x00,  /* "->" */           \
	0x00, 0x20, 0x40, 0xf8, 0x40, 0x20, 0x00   /* "<-" */           \
};

//! @}

#endif /* CONF_SYSFONT_H */
