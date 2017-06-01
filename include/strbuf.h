/*
 * File: strbuf.h
 * --------------
 * This interface defines a class that allows strings to grow by
 * concatentation.
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (C) 2013 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef _strbuf_h
#define _strbuf_h

#include <stdarg.h>
#include "cslib.h"

/*
 * Type: StringBuffer
 * ------------------
 * This type provides an efficient, memory-safe mechanism for strings
 * that grow by the addition of characters.
 */

typedef struct StringBufferCDT *StringBuffer;

/*
 * Function: newStringBuffer
 * Usage: sb = newStringBuffer();
 * ------------------------------
 * Creates a new string buffer that expands dynamically if needed.
 * The buffer is initially empty.
 */

StringBuffer newStringBuffer();

/*
 * Function: freeStringBuffer
 * Usage: freeStringBuffer(sb);
 * ----------------------------
 * Frees the storage associated with the string buffer.
 */

void freeStringBuffer(StringBuffer sb);

/*
 * Function: pushChar
 * Usage: pushChar(sb, ch);
 * ------------------------
 * Appends (pushes) the character <code>ch</code> onto the end of the
 * string buffer.
 */

void pushChar(StringBuffer sb, char ch);

/*
 * Function: popChar
 * Usage: ch = popChar(sb);
 * ------------------------
 * Pops and removes the last character from the string buffer.
 */

char popChar(StringBuffer sb);

/*
 * Function: appendString
 * Usage: appendString(sb, str);
 * -----------------------------
 * Appends the string <code>str</code> to the end of the string buffer.
 */

void appendString(StringBuffer sb, string str);

/*
 * Function: sbprintf
 * Usage: sbprintf(sb, format, ...);
 * ---------------------------------
 * Expands a <code>printf</code>-style format string and arguments onto
 * the end of the string buffer.
 */

void sbprintf(StringBuffer sb, string format, ...);

/*
 * Function: isEmpty
 * Usage: if (isEmpty(sb)) . . .
 * -----------------------------
 * Returns <code>true</code> if the string buffer is empty.
 */

bool isEmptyStringBuffer(StringBuffer vec);

/*
 * Function: size
 * Usage: n = size(sb);
 * --------------------
 * Returns the number of characters in the string buffer.
 */

int sizeStringBuffer(StringBuffer vector);

/*
 * Function: clear
 * Usage: clear(sb);
 * -----------------
 * Removes all characters from the string buffer.
 */

void clearStringBuffer(StringBuffer sb);

/*
 * Function: getString
 * Usage: str = getString(sb);
 * ---------------------------
 * Returns the string stored inside the buffer.  Clients must copy this
 * string if they need to retain it.
 */

string getString(StringBuffer sb);

/*
 * Friend function: printfCapacity
 * Usage: capacity = printfCapacity(format, args);
 * -----------------------------------------------
 * Returns a character count that will be sufficient to hold the result
 * of printing <code>format</code> with arguments substituted from the
 * <code>args</code> list.  This bound is guaranteed to be adequate but
 * is not necessarily tight.
 */

int printfCapacity(string format, va_list args);

/*
 * Friend function: sbFormat
 * Usage: sbFormat(sb, capacity, format, list);
 * --------------------------------------------
 * Works like <code>sbprintf</code> except that the list is an argument
 * list as in <code>stdarg.h</code>.  The <code>capacity</code> argument
 * is the required capacity, as returned by <code>printfCapacity</code>.
 */

void sbFormat(StringBuffer sb, int capacity, string format, va_list args);

#endif
