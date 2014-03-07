/*
 * File: DrawLines.c
 * -----------------
 * This program allows users to create lines on the graphics
 * canvas by clicking and dragging with the mouse.
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
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

int main() {
   GWindow gw;
   GObject line;
   GEvent e;

   gw = newGWindow(600, 400);
   while (true) {
      e = waitForEvent(MOUSE_EVENT);
      if (getEventType(e) == MOUSE_PRESSED) {
         line = newGLine(getX(e), getY(e), getX(e), getY(e));
         add(gw, line);
      } else if (getEventType(e) == MOUSE_DRAGGED) {
         setEndPoint(line, getX(e), getY(e));
      }
      freeEvent(e);
   }
}
