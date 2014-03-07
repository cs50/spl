/*
 * File: TestInteractors.c
 * -----------------------
 * This program tests the various interactor classes in the graphics
 * library.
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

#include <simpio.h>
#include "cslib.h"
#include "gevents.h"
#include "ginteractors.h"
#include "gwindow.h"

int main() {
   GWindow gw = newGWindow(800, 400);
   GButton button = newGButton("Start");
   addToRegion(gw, button, "SOUTH");
   GChooser chooser = newGChooser();
   addItem(chooser, "Small");
   addItem(chooser, "Medium");
   addItem(chooser, "Large");
   addItem(chooser, "X-Large");
   addToRegion(gw, chooser, "SOUTH");
   GCheckBox chkbox = newGCheckBox("Slow");
   addToRegion(gw, chkbox, "SOUTH");
   setActionCommand(chkbox, "Check");
   GSlider slider = newGSlider(0, 100, 50);
   GDimension size = getSize(slider);
   setSize(slider, 100, getHeight(size));
   addToRegion(gw, newGLabel(" Slow"), "SOUTH");
   addToRegion(gw, slider, "SOUTH");
   GTextField field = newGTextField(10);
   addToRegion(gw, newGLabel("Fast "), "SOUTH");
   setActionCommand(field, "Start");
   addToRegion(gw, newGLabel("Text:"), "SOUTH");
   addToRegion(gw, field, "SOUTH");
   while (true) {
      GActionEvent e = waitForEvent(ACTION_EVENT);
      string cmd = getActionCommand(e);
      if (stringEqual(cmd, "Start")) {
         printf("Start: text = \"%s\", size = %s, speed = %d\n",
                getText(field), getSelectedItem(chooser), getValue(slider));
      } else if (stringEqual(cmd, "Check")) {
         printf("Check = %s\n", isSelected(chkbox) ? "true" : "false");
      }
   }
}
