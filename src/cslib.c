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
#include "exception.h"
#include "cslib.h"

/* Constants */

#define MAX_MESSAGE 500

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
#define PASSWORD 314159265L

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

/* Section 3 -- error handling */

extern void unhandledError(string msg);

void error(string msg, ...) {
   va_list args;
   char errbuf[MAX_MESSAGE + 1];
   string errmsg;
   int errlen;

   va_start(args, msg);
   vsnprintf(errbuf, MAX_MESSAGE, msg, args);
   va_end(args);
   errlen = strlen(errbuf);
   if (errlen >= MAX_MESSAGE) {
      unhandledError("error message too long");
   }
   errmsg = (string) malloc(errlen + 1);
   if (errmsg == NULL) {
      errmsg = "No memory available";
   } else {
      strcpy(errmsg, errbuf);
   }
   throwException(&ErrorException, "ErrorException", errmsg);
}

/* Section 4 -- Redefine main */

#undef main

extern main_(int argc, string argv[]);

static proc exitHook = NULL;
static int argCount;
static string *argArray;

main(int argc, string argv[]) {
   int i;

   argCount = argc;
   argArray = newArray(argc + 1, string);
   for (i = 0; i < argc; i++) {
      argArray[i] = argv[i];
   }
   argArray[argc] = NULL;
   main_(argc, argv);
   if (exitHook != NULL) {
      exitHook();
   }
}

/*
 * Function: getMainArgCount
 * Usage: count = getMainArgCount();
 * ---------------------------------
 * Returns the argument count for the main program.
 */

int getMainArgCount(void) {
   return argCount;
}

/*
 * Function: getMainArgArray
 * Usage: array = getMainArgArray();
 * ---------------------------------
 * Returns a NULL-terminated copy of the argument array passed
 * to the main program.
 */

string *getMainArgArray(void) {
   return argArray;
}

/*
 * Function: setExitHook
 * Usage: setExitHook(hook);
 * -------------------------
 * Sets the global exit hook for the process.  This mechanism
 * is used by implementations of the graphics library to gain
 * control before the process exits.
 */

void setExitHook(proc hook) {
   exitHook = hook;
}
