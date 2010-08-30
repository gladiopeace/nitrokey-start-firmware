/*
 * debug.c -- Debuging with virtual COM port
 *
 * Copyright (C) 2010 Free Software Initiative of Japan
 * Author: NIIBE Yutaka <gniibe@fsij.org>
 *
 * This file is a part of Gnuk, a GnuPG USB Token implementation.
 *
 * Gnuk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Gnuk is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "config.h"
#include "ch.h"
#include "gnuk.h"

static void
put_hex (uint8_t nibble)
{
  uint8_t c;

  if (nibble < 0x0a)
    c = '0' + nibble;
  else
    c = 'a' + nibble - 0x0a;

  _write (&c, 1);
}

void
put_byte (uint8_t b)
{
  put_hex (b >> 4);
  put_hex (b &0x0f);
  _write ("\r\n", 2);
}

void
put_byte_with_no_nl (uint8_t b)
{
  _write (" ", 1);
  put_hex (b >> 4);
  put_hex (b &0x0f);
}

void
put_short (uint16_t x)
{
  put_hex (x >> 12);
  put_hex ((x >> 8)&0x0f);
  put_hex ((x >> 4)&0x0f);
  put_hex (x & 0x0f);
  _write ("\r\n", 2);
}

void
put_string (const char *s)
{
  _write (s, strlen (s));
}


