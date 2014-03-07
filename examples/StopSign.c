/*
 * File: StopSign.c
 * ----------------
 * This program draws a filled red octagon.
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
#include <math.h>
#include "cslib.h"
#include "gobjects.h"
#include "gwindow.h"

main() {
   GWindow gw;
   GPolygon stopSign;
   double edge;
   int i;

   printf("This program draws a red octagon.\n");
   gw = newGWindow(600, 400);
   edge = 75;
   stopSign = newGPolygon();
   addVertex(stopSign, -edge / 2, edge / 2 + edge / sqrt(2.0));
   for (i = 0; i < 8; i++) {
      addPolarEdge(stopSign, edge, 45 * i);
   }
   setFilled(stopSign, true);
   setColor(stopSign, "RED");
   addAt(gw, stopSign, getWidth(gw) / 2, getHeight(gw) / 2);
}
