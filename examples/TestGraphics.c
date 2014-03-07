/*
 * File: TestGraphics.c
 * --------------------
 * This file tests the JBE graphics package from C.
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
   double width, height;
   GWindow gw;

   gw = newGWindow(500, 300);
   width = getWidth(gw);
   height = getHeight(gw);
   drawLine(gw, 0, height / 2, width / 2, 0);
   drawLine(gw, width / 2, 0, width, height / 2);
   drawLine(gw, width, height / 2, width / 2, height);
   drawLine(gw, width / 2, height, 0, height / 2);
   setColor(gw, "BLUE");
   fillRect(gw, width / 4, height / 4, width / 2, height / 2);
   setColor(gw, "GRAY");
   fillOval(gw, width / 4, height / 4, width / 2, height / 2);
}
