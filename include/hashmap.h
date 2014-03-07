/*
 * File: hashmap.h
 * ---------------
 * This interface defines a map abstraction that associates string
 * keys with values.  The implementation uses a hash table, which
 * offers constant-time performance but does not support iterating
 * through the keys in order.
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

#ifndef _hashmap_h
#define _hashmap_h

#include "cslib.h"
#include "generic.h"
#include "iterator.h"

/*
 * Function: HashMap
 * -----------------
 * This type is the ADT used to represent a map from strings to values.
 */

typedef struct HashMapCDT *HashMap;

/* Exported entries */

/*
 * Function: newHashMap
 * Usage: map = newHashMap();
 * --------------------------
 * Allocates a new map with no entries.
 */

HashMap newHashMap(void);

/*
 * Function: freeHashMap
 * Usage: freeHashMap(map);
 * ------------------------
 * Frees the storage associated with the map.
 */

void freeHashMap(HashMap map);

/*
 * Function: size
 * Usage: n = size(map);
 * ---------------------
 * Returns the number of elements in the map.
 */

int sizeHashMap(HashMap map);

/*
 * Function: isEmpty
 * Usage: if (isEmpty(map)) . . .
 * ------------------------------
 * Returns <code>true</code> if the map has no entries.
 */

bool isEmptyHashMap(HashMap map);

/*
 * Function: clear
 * Usage: clear(map);
 * ------------------
 * Removes all entries from the map.
 */

void clearHashMap(HashMap map);

/*
 * Function: clone
 * Usage: newmap = clone(map);
 * ---------------------------
 * Creates a copy of the map.  The <code>clone</code> function copies
 * only the first level of the structure and does not copy the individual
 * elements.
 */

HashMap cloneHashMap(HashMap map);

/*
 * Function: put
 * Usage: put(map, key, value);
 * ----------------------------
 * Associates <code>key</code> with <code>value</code> in the map.
 * Each call to <code>put</code> supersedes any previous definition
 * for <code>key</code>.
 */

void putHashMap(HashMap map, string key, void *value);

/*
 * Function: get
 * Usage: void *value = get(map, key);
 * -----------------------------------
 * Returns the value associated with <code>key</code> in the map,
 * or <code>NULL</code>, if no such value exists.
 */

void *getHashMap(HashMap map, string key);

/*
 * Function: containsKey
 * Usage: if (containsKey(map, key)) . . .
 * ---------------------------------------
 * Checks to see if the map contains the specified key.
 */

bool containsKeyHashMap(HashMap map, string key);

/*
 * Function: remove
 * Usage: remove(map, key);
 * ------------------------
 * Removes the key and its value from the map.
 */

void removeHashMap(HashMap map, string key);

/*
 * Function: map
 * Usage: map(map, fn, data);
 * --------------------------
 * Iterates through the map and calls the function <code>fn</code> on
 * each entry.  The callback function takes the following arguments:
 *
 *<ul>
 *  <li>The key string
 *  <li>The associated value
 *  <li>The <code>data</code> pointer
 *</ul>
 *
 * The <code>data</code> pointer allows the client to pass state
 * information to the function <code>fn</code>, if necessary.  If no such
 * information is required, this argument should be <code>NULL</code>.
 */

void mapHashMap(HashMap map, proc fn, void *data);

#endif
