/*
 * File: map.c
 * -----------
 * This file implements the map.h interface, which implements maps using
 * the balanced binary tree abstraction exported by the bst.h interface.
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
#include <string.h>
#include "bst.h"
#include "cmpfn.h"
#include "cslib.h"
#include "exception.h"
#include "foreach.h"
#include "generic.h"
#include "iterator.h"
#include "itertype.h"
#include "map.h"
#include "strlib.h"
#include "unittest.h"

/*
 * Type: MapCDT
 * ------------
 * This type is the concrete type used to represent the map.
 */

struct MapCDT {
   IteratorHeader header;              /* Header to enable iteration   */
   BST bst;                            /* BST that does all the work   */
};

/* Private function prototypes */

static Iterator newMapIterator(void *collection);
static void addKeyToIterator(BSTNode node, void *data);

/* Exported entries */

Map newMap() {
   Map map;

   map = newBlock(Map);
   enableIteration(map, newMapIterator);
   map->bst = newBST(string);
   return map;
}

void freeMap(Map map) {
   freeBST(map->bst);
   freeBlock(map);
}

int sizeMap(Map map) {
   return sizeBST(map->bst);
}

bool isEmptyMap(Map map) {
   return isEmptyBST(map->bst);
}

void clearMap(Map map) {
   clearBST(map->bst);
}

Map cloneMap(Map map) {
   Map newmap;

   newmap = newBlock(Map);
   enableIteration(newmap, newMapIterator);
   newmap->bst = cloneBST(map->bst);
   return newmap;
}

void putMap(Map map, string key, void *value) {
   BSTNode node;

   node = insertBSTNode(map->bst, key);
   setNodeValue(node, value);
}

void *getMap(Map map, string key) {
   BSTNode node;

   node = findBSTNode(map->bst, key);
   return (node == NULL) ? NULL : getNodeValue(node);
}

bool containsKeyMap(Map map, string key) {
   return findBSTNode(map->bst, key) != NULL;
}

void removeMap(Map map, string key) {
   removeBSTNode(map->bst, key);
}

void mapMap(Map map, proc fn, void *data) {
   Iterator it;
   BSTNode node;

   it = newNodeIterator(map->bst, INORDER);
   while (stepIterator(it, &node)) {
      fn(getKeyString(node), getNodeValue(node), data);
   }
}

/* Private functions */

static Iterator newMapIterator(void *collection) {
   Iterator iterator;

   iterator = newListIterator(sizeof(string), NULL);
   mapBST(((Map) collection)->bst, addKeyToIterator, INORDER, iterator);
   return iterator;
}

/*
 * Implementation notes: addKeyToIterator
 * --------------------------------------
 * Adds the key from the specified node to the iterator, which is
 * passed as the <code>data</code> parameter.
 */

static void addKeyToIterator(BSTNode node, void *data) {
   string key;

   key = (string) getKey(node).pointerRep;
   addToIteratorList((Iterator) data, &key);
}

/**********************************************************************/
/* Unit test for the map module                                       */
/**********************************************************************/

#ifndef _NOTEST_

void testMapModule(void) {
   Map map, map2;
   string key;
   string str;

   trace(map = newMap());
   test(size(map), 0);
   test(isEmpty(map), true);
   trace(put(map, "H", "Hydrogen"));
   test(size(map), 1);
   test(isEmpty(map), false);
   trace(put(map, "He", "Helium"));
   trace(put(map, "Al", "Aluminum"));
   test(containsKey(map, "H"), true);
   test(get(map, "H"), "Hydrogen");
   test(get(map, "He"), "Helium");
   test(get(map, "Al"), "Aluminum");
   test(containsKey(map, "Li"), false);
   test(get(map, "Li"), NULL);
   trace(put(map, "Al", "Aluminium"));
   test(get(map, "Al"), "Aluminium");
   trace(remove(map, "Al"));
   test(containsKey(map, "Al"), false);
   test(get(map, "He"), "Helium");
   trace(put(map, "Li", "Lithium"));
   test(get(map, "Li"), "Lithium");
   trace(put(map, "Be", "Beryllium"));
   test(size(map), 4);
   trace(str = "");
   trace (foreach (key in map) str = concat(str, key));
   test(str, "BeHHeLi");
   trace(str = "");
   trace(foreach (key in map) str = concat(str, get(map, key)));
   test(str, "BerylliumHydrogenHeliumLithium");
   trace(map2 = clone(map));
   trace(str = "");
   trace(foreach (key in map2) str = concat(str, get(map2, key)));
   test(str, "BerylliumHydrogenHeliumLithium");
}

#endif
