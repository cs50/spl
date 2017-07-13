/*
 * File: cslib.h
 * -------------
 * This interface defines a basic set of definitions that are shared
 * among all interfaces in the package.  These basic definitions include:
 *
 *<ol>
 *  <li>Declarations for several new &ldquo;primitive&rdquo; types used
 *      throughout the libraries as fundamental types.
 *
 *  <li>A function for error handling.
 *
 *  <li>A flexible set of functions for memory allocation.
 *</ol>
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

#ifndef _cslib_h
#define _cslib_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include  "gcolor.h"

#if __STDC_VERSION__ == 201112L
#   define NORETURN _Noreturn
#elif defined _GNUC
#   define NORETURN __attribute__((noreturn))
#else
#   define NORETURN
#endif

#ifdef _GNUC
#   define ATTR(X) __attribute__((X)) 
#else
#   define ATTR(X)
#endif

/* Section 1 -- Define new "primitive" types */

/*
 * Type: string
 * ------------
 * This type is defined to be identical with <code>char *</code>.
 */

typedef char *string;

/* Section 2 -- Memory allocation */

// Types we need to be generic over
enum {
    UNKNOWN,
    GOBJECT,
    GWINDOW,
    GEVENT,
    VECTOR,
};

/*
 * General notes
 * -------------
 * These functions provide a common interface for memory allocation.
 * All functions in the library that allocate memory do so using
 * <code>getBlock</code> and <code>freeBlock</code>.  Even though the
 * ANSI standard defines <code>malloc</code> and <code>free</code> for
 * the same purpose, using <code>getBlock</code> and <code>freeBlock</code>
 * provides greater compatibility with non-ANSI implementations, automatic
 * out-of-memory error detection, limited type checking, and the possibility
 * of installing a garbage-collecting allocator.
 */

/*
 * Function: getBlock
 * Usage: ptr = getBlock(nbytes);
 * ------------------------------
 * Allocates a block of memory of the given size.  If no memory is
 * available, <code>getBlock</code> generates an error.
 */

void *getBlock(size_t nbytes, unsigned char type);

/*
 * Function: freeBlock
 * Usage: freeBlock(ptr);
 * ----------------------
 * Frees the memory associated with <code>ptr</code>, which must have
 * been allocated using <code>getBlock</code>, <code>newBlock</code>, or
 * <code>newArray</code>.  If the block appears to be in static memory
 * or allocated by <code>malloc</code>, the call to <code>freeBlock</code>
 * has no effect.
 */

void freeBlock(void *ptr);

/*
 * Function: getBlockType
 * Usage: type = getBlockType(ptr);
 * --------------------------------
 * Returns a string indicating the type of the block.  If the block is
 * created using the <code>newBlock</code> macro, the string is the type
 * argument.  If the block is created using <code>newArray</code>, the
 * string consists of the base type followed by the string <code>"[]"</code>.
 * In all other cases, the type is returned as <code>"?"</code>.  This
 * string is constant and should not be freed.
 */

unsigned char getBlockType(void *ptr);


/*
 * Macro: newBlock
 * Usage: ptr = (type) newBlock(type);
 * -----------------------------------
 * Allocates enough space to hold an object of the type to which
 * <code>type</code> points (note that <code>type</code> must be
 * a pointer type).  Note that <code>newBlock</code> is different from
 * the <code>new</code> operator used in C++; the former takes a
 * pointer type and the latter takes the target type.
 */


// Defined in src/typemap.gperf
unsigned char mapType(char const *str);

#define newBlock(type) getBlock(sizeof *((type) NULL), mapType(#type))

/* Section 3 -- error handling */

#define error(FMT, ...) do { error_msg(FMT, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)

#define error_msg(FMT, ...)                                 \
    do {                                                    \
        fprintf(stderr, FMT, ##__VA_ARGS__);                \
        fprintf(stderr, "\n");                              \
    } while (false)
#endif
