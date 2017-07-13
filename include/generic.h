/*
 * File: generic.h
 * ---------------
 * This interface defines those functions that apply to more than one type.
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
#ifndef _generic_h
#define _generic_h

#include <stdarg.h>
#include "cslib.h"

/* Avoid various name conflicts */

#define remove xremove

#ifdef __macosx__
#  define dequeue _dequeue
#  define enqueue _enqueue
#endif

#define getX(arg) getXGeneric(sizeof arg, arg)
#define getY(arg) getYGeneric(sizeof arg, arg)
#define getWidth(arg) getWidthGeneric(sizeof arg, arg)
#define getHeight(arg) getHeightGeneric(sizeof arg, arg)
#define toString(arg) toStringGeneric(sizeof arg, arg)
#define isEmpty(arg) isEmptyGeneric(sizeof arg, arg)
#define contains(arg, value) containsGeneric(sizeof arg, arg, value)

/*
 * Function: isEmpty
 * Usage: if (isEmpty(arg)) . . .
 * ------------------------------
 * Returns <code>true</code> if the collection is empty.
 */

bool isEmptyGeneric(int size, ...);

/*
 * Function: contains
 * Usage: if (contains(arg, ...)) . . .
 * ------------------------------------
 * Checks whether a set contains the value specified by the argument list,
 * which may vary according to the base type.
 */

bool containsGeneric(int size, ...);

/*
 * Function: add
 * Usage: add(arg, ...);
 * ---------------------
 * Adds a value to the collection.  The format of the argument list depends
 * on the collection type.  See the documentation of the individual type
 * for details.
 */

void add(void *container, void *item);

/*
 * Function: remove
 * Usage: remove(arg, ...);
 * ------------------------
 * Removes a value from the collection.  The format of the argument list
 * depends on the collection type.  See the documentation of the individual
 * type for details.
 */

void remove(void *container, void *item);

/*
 * Function: getX
 * Usage: x = getX(any);
 * ---------------------
 * Returns the x component of the value.
 */

double getXGeneric(int size, ...);

/*
 * Function: getY
 * Usage: y = getY(any);
 * ---------------------
 * Returns the y component of the value.
 */

double getYGeneric(int size, ...);

/*
 * Function: getWidth
 * Usage: width = getWidth(any);
 * -----------------------------
 * Returns the width component of the value.
 */

double getWidthGeneric(int size, ...);

/*
 * Function: getHeight
 * Usage: height = getHeight(any);
 * -------------------------------
 * Returns the height component of the value.
 */

double getHeightGeneric(int size, ...);

/*
 * Function: toString
 * Usage: str = toString(arg);
 * ---------------------------
 * Converts the argument to a string, if possible
 */

/*
 * Function: setVisible
 * Usage: setVisible(arg, flag);
 * -----------------------------
 * Sets whether the argument is visible.
 */

void setVisible(void *arg, bool flag);

/*
 * Function: isVisible
 * Usage: if (isVisible(arg)) . . .
 * --------------------------------
 * Returns <code>true</code> if the argument is visible.
 */

bool isVisible(void *arg);

/*
 * Function: setColor
 * Usage: setColor(arg, color);
 * ----------------------------
 * Sets the color of the argument.
 */

void setColor(void *arg, GColor c);

/*
 * Friend function: getTypeSizeForType
 * Usage: size = getTypeSizeForType(type);
 * ---------------------------------------
 * Returns the size in bytes for the specified type.
 */

int getTypeSizeForType(string type);

#endif
