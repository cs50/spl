/*
 * File: DrawRectangles.c
 * ----------------------
 * This program allows users to create rectangles on the canvas
 * by clicking and dragging with the mouse.  This version of the
 * program also allows the user to change the color of a rectangle
 * by typing the first letter of the color name or a space for black.
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

#include <math.h>
#include <stdio.h>
#include "cslib.h"
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

main() {
   GWindow gw = newGWindow(600, 400);
   GRect rect = NULL;
   bool dragging = false;
   double startX = 0.0;
   double startY = 0.0;
   while (true) {
      GEvent e = waitForEvent(MOUSE_EVENT | KEY_EVENT);
      if (getEventType(e) == MOUSE_PRESSED) {
         startX = getX(e);
         startY = getY(e);
         rect = getGObjectAt(gw, startX, startY);
         dragging = (rect != NULL);
         if (!dragging) {
            rect = newGRect(startX, startY, 0, 0);
            setFilled(rect, true);
            add(gw, rect);
         }
      } else if (getEventType(e) == MOUSE_DRAGGED) {
         double x = getX(e);
         double y = getY(e);
         if (dragging) {
            move(rect, x - startX, y - startY);
            startX = x;
            startY = y;
         } else {
            double width = fabs(x - startX);
            double height = fabs(y - startY);
            x = fmin(x, startX);
            y = fmin(y, startY);
            setBounds(rect, x, y, width, height);
         }
      } else if (getEventType(e) == MOUSE_CLICKED) {
         if (rect != NULL) sendToFront(rect);
      } else if (getEventType(e) == KEY_TYPED) {
         if (rect != NULL) {
            string color = "BLACK";
            switch (getKeyChar(e)) {
             case 'b': color = "BLUE"; break;
             case 'c': color = "CYAN"; break;
             case 'g': color = "GREEN"; break;
             case 'm': color = "MAGENTA"; break;
             case 'o': color = "ORANGE"; break;
             case 'r': color = "RED"; break;
             case 'w': color = "WHITE"; break;
             case 'y': color = "YELLOW"; break;
            }
            setColor(rect, color);
         }
      }
   }
}
