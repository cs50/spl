/*
 * File: iterator.h
 * ----------------
 * This interface exports a polymorphic iterator abstraction for C.
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

#ifndef _iterator_h
#define _iterator_h

#include "cslib.h"

/*
 * Type: Iterator
 * --------------
 * An abstract type used to iterate over the elements of any collection.
 */

typedef struct IteratorCDT *Iterator;

/* Exported entries */

/*
 * General overview
 * ----------------
 * The <code>newIterator</code>, <code>stepIterator</code>, and
 * <code>freeIterator</code> functions make it possible to iterate
 * over the elements in any collection that supports iteration.
 * In most cases, clients will simply use the <code>foreach</code>
 * macro, which automatically invokes these methods.  They can
 * also be used as shown in the following standalone paradigm:
 *
 *<pre>
 *    iterator = newIterator(collection);
 *    while (stepIterator(iterator, &element)) {
 *       . . . body of loop . . .
 *    }
 *    freeIterator(iterator);
 *</pre>
 *
 * <p>The call to <code>stepIterator</code> advances the iterator
 * and returns the next element using the reference parameter.  The
 * <code>stepIterator</code> function returns <code>true</code> until
 * the elements are exhausted, after which it returns <code>false</code>.
 * The <code>freeIterator</code> function releases any storage
 * associated with the iterator.
 */

/*
 * Function: newIterator
 * Usage: iterator = newIterator(collection);
 * ------------------------------------------
 * Creates a new iterator for the specified collection.
 */

Iterator newIterator(void *collection);

/*
 * Function: stepIterator
 * Usage: hasMoreElements = stepIterator(iterator, &element);
 * ----------------------------------------------------------
 * Advances the iterator and stores the next element through the
 * element pointer provided as a reference parameter.  The
 * <code>stepIterator</code> function returns <code>true</code> until
 * the elements are exhausted, after which it returns <code>false</code>.
 */

bool stepIterator(Iterator iterator, void *dst);

/*
 * Function: freeIterator
 * Usage: freeIterator(iterator);
 * ------------------------------
 * Frees any storage associated with the iterator.
 */

void freeIterator(Iterator iterator);

#endif
