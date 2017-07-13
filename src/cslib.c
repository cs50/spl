/*
 * File: cslib.c
 * -------------
 * This file implements the general C library package.  See the
 * interface description in cslib.h for details.
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

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include "cslib.h"


/* Section 2 -- Memory allocation */

/*
 * Type: BlockHeader
 * -----------------
 * The smallest structure within the allocator is called a block and
 * consists of the actual allocated memory returned to the client, plus
 * the following header information:
 *
 *                  +---------------------+
 *     base addr -> |       password      |
 *                  +---------------------+
 *                  | client data pointer |
 *                  +---------------------+
 *   client addr -> |          .          |
 *                  |          .          |
 *                  |          .          |
 *                  +---------------------+
 *
 * The password is a special value unlikely to appear as a data value.
 */

typedef struct {
    struct {
        unsigned magic : 29;
        unsigned char type : 3;
    };
    void *data;
} BlockHeader;

#define MAGIC 314159265

void *getBlock(size_t nbytes, unsigned char type)
{
    BlockHeader *base = calloc(nbytes + sizeof (BlockHeader), 1);
    if (!base) error("No memory available");
    base->magic = MAGIC;
    base->type = type;
    return ((char *) base + sizeof(BlockHeader));
}

void freeBlock(void *ptr)
{
    BlockHeader *base = (BlockHeader *) ((char *) ptr - sizeof(BlockHeader));
    if (base->magic == MAGIC) {
        base->magic = 0;
        free(base);
    }
}

unsigned char getBlockType(void *ptr)
{
    BlockHeader *base = (BlockHeader *) ((char *) ptr - sizeof(BlockHeader));
    return (base->magic == MAGIC) ? base->type : UNKNOWN;
}

