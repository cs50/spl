/*
 * File: loadobj.h
 * ---------------
 * This interface supports dynamic loading of functions from object files.
 * Any references in the object file to previously defined objects are
 * allowed, but no additional searching or unresolved references are
 * supported.
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

#ifndef _loadobj_h
#define _loadobj_h

#include "cslib.h"

/*
 * Function: loadObject
 * Usage: loadObject(pathname);
 * ----------------------------
 * Loads the object file into the current executable.
 */

void loadObject(string pathname);

/*
 * Function: loadSymbols
 * Usage: loadSymbols(progname);
 * -----------------------------
 * Loads the symbols from the executable program.
 */

void loadSymbols(string progname);

/*
 * Function: findFunction
 * Usage: fn = findFunction(fnname);
 * ---------------------------------
 * Looks up the function in the symbol table and returns a pointer to the
 * code.
 */

proc findFunction(string fnname);

#endif
