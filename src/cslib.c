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
 *                  |  block type string  |
 *                  +---------------------+
 *                  | size of client data |
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

typedef struct BlockHeader {
    union {
        size_t _password;
        struct BlockHeader *_chain;
    } block_union;
    char *type;
    size_t size;
    void *data;
} BlockHeader;

#define password block_union._password
#define chain block_union._chain
#define PASSWORD 314159265

/*
 * Implementation notes:
 * ---------------------
 */

/* Memory allocation implementation */

void *getBlock(size_t nbytes) {
    return getTypedBlock(nbytes, "?");
}

void *getTypedBlock(size_t nbytes, string type) {
    BlockHeader *base;

    base = (BlockHeader *) malloc(nbytes + sizeof(BlockHeader));
    if (base == NULL) error("No memory available");
    base->password = PASSWORD;
    base->type = type;
    base->size = nbytes;
    base->data = NULL;
    return (void *) ((char *) base + sizeof(BlockHeader));
}

void freeBlock(void *ptr) {
    BlockHeader *base;

    base = (BlockHeader *) ((char *) ptr - sizeof(BlockHeader));
    if (base->password == PASSWORD) {
        base->password = 0;
        free(base);
    }
}

string getBlockType(void *ptr) {
    BlockHeader *base;

    base = (BlockHeader *) ((char *) ptr - sizeof(BlockHeader));
    return (base->password == PASSWORD) ? base->type : "?";
}

void setBlockData(void *ptr, void *value) {
    BlockHeader *base;

    base = (BlockHeader *) ((char *) ptr - sizeof(BlockHeader));
    if (base->password != PASSWORD) {
        error("setBlockData: Block has not been allocated");
    }
    base->data = value;
}

void *getBlockData(void *ptr) {
    BlockHeader *base;

    base = (BlockHeader *) ((char *) ptr - sizeof(BlockHeader));
    if (base->password != PASSWORD) {
        error("getBlockData: Block has not been allocated");
    }
    return base->data;
}
