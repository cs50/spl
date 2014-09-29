/*
 * File: loadobj.c
 * ---------------
 * This file implements the loadobj.h interface.
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include "cslib.h"
#include "filelib.h"
#include "loadobj.h"
#include "strlib.h"

#ifndef MAX_PATH_NAME
#  define MAX_PATH_NAME 1000
#endif

typedef struct Cell {
   void *handle;
   struct Cell *link;
} *HandleList;

HandleList handles = NULL;

void loadObject(string pathname) {
   HandleList hl;
   static char fullPath[MAX_PATH_NAME];

   hl = newBlock(HandleList);
   switch (pathname[0]) {
     case '/':
       strcpy(fullPath, pathname);
       break;
     case '~':
       strcpy(fullPath, expandPathname(pathname));
       break;
     default:
       getcwd(fullPath, MAX_PATH_NAME);
       strcat(fullPath, "/");
       strcat(fullPath, pathname);
       break;
   }
   hl->handle = dlopen(fullPath, RTLD_NOW);
   if (hl->handle == NULL) {
      freeBlock(hl);
      error("loadObject: %s", dlerror());
   }
   hl->link = handles;
   handles = hl;
}

proc findFunction(string fnname) {
   HandleList hl;
   void *fn;

   for (hl = handles; hl != NULL; hl = hl->link) {
      fn = dlsym(hl->handle, fnname);
      if (fn != NULL) return (proc) (long) fn;
   }
   error("findFunction: %s", dlerror());
}

void loadSymbols(string progname) {
   /* Empty */
}
