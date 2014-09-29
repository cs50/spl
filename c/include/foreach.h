/*
 * File: foreach.h
 * ---------------
 * This interface provides a simple syntactic extension for iterators
 * that makes them much easier to read.  The general form of the
 * <code>foreach</code> statement looks like this:
 *
 *<pre>
 *    foreach (<span class=it>var</span> in <span class=it>collection</span>) {
 *       <span class=it>statements</span>
 *    }
 *</pre>
 *
 * In C, the variable <i>var</i> must be declared outside the loop.
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

#ifndef _foreach_h
#define _foreach_h

#include "cslib.h"

/*
 * Macro: foreach
 * Usage: foreach (element in collection) { . . . }
 * ------------------------------------------------
 * This macro definition creates a new statement form that simplifies
 * the use of iterators.  The variable <code>element</code> must be
 * declared in the current scope and must be compatible with the base
 * type of the collection.
 */

#define in : (void *) (
#define foreach(arg) \
    for (initForEach(1 ? (void *) &arg), 0 ? &arg)); \
         stepForEach(1 ? (void *) &arg)); )

void initForEach(void *dst, void *collection);
bool stepForEach(void *dst);

#endif
