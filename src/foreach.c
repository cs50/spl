/*
 * File: foreach.c
 * ---------------
 * This file implements the foreach construct.
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
#include "foreach.h"
#include "cslib.h"
#include "iterator.h"

typedef struct Cell {
   void *dst;
   Iterator iterator;
   struct Cell *link;
} Cell;

static Cell *iteratorList = NULL;

/* Entry points */

void initForEach(void *dst, void *collection) {
   Cell *cp;

   for (cp = iteratorList; cp != NULL && cp->dst != dst; cp = cp->link) {
      /* Empty */
   }
   if (cp == NULL) {
      cp = newBlock(Cell *);
      cp->dst = dst;
      cp->link = iteratorList;
      iteratorList = cp;
   } else {
      if (cp->iterator != NULL) freeIterator(cp->iterator);
   }
   cp->iterator = newIterator(collection);
}

bool stepForEach(void *dst) {
   Cell *cp;
   bool result;

   for (cp = iteratorList; cp != NULL && cp->dst != dst; cp = cp->link) {
      /* Empty */
   }
   if (cp == NULL) error("foreach iterator undefined");
   result = stepIterator(cp->iterator, dst);
   if (!result) {
      freeIterator(cp->iterator);
      cp->iterator = NULL;
   }
   return result;
}
