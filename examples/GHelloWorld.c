/*
 * File: GHelloWorld.c
 * -------------------
 * This program implements Hello World using the graphics window.
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
#include "cslib.h"
#include "gobjects.h"
#include "gwindow.h"

main() {
   GWindow gw;
   GLabel label;
   double x, y;

   printf("This program draws the 'hello, world' message.\n");
   gw = newGWindow(600, 400);
   label = newGLabel("hello, world");
   setFont(label, "SansSerif-36");
   x = (getWidth(gw) - getWidth(label)) / 2;
   y = (getHeight(gw) + getFontAscent(label)) / 2;
   setLocation(label, x, y);
   add(gw, label);
}
