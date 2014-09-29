/*
 * File: gwindow.c
 * ---------------
 * This file implements the GWindow type, passing most calls directly
 * to the appropriate methods in the platform.h interface.
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
#include "gmath.h"
#include "gobjects.h"
#include "gtypes.h"
#include "gwindow.h"
#include "platform.h"

struct GWindowCDT {
   bool visible;
   string color;
   string title;
   double width;
   double height;
   GObject top;
};

GWindow newGWindow(double width, double height) {
   GWindow gw = newBlock(GWindow);
   gw->top = newGCompound();
   createGWindowOp(gw, width, height, gw->top);
   gw->visible = true;
   gw->color = "BLACK";
   gw->title = "Untitled";
   gw->width = width;
   gw->height = height;
   return gw;
}

void closeGWindow(GWindow gw) {
   closeGWindowOp(gw);
}

void requestFocus(GWindow gw) {
   requestFocusOp(gw);
}

void clearGWindow(GWindow gw) {
   clearOp(gw);
}

void setVisibleGWindow(GWindow gw, bool flag) {
   gw->visible = flag;
   setVisibleGWindowOp(gw, flag);
}

bool isVisibleGWindow(GWindow gw) {
   return gw->visible;
}

void drawLine(GWindow gw, double x0, double y0, double x1, double y1) {
   GObject gobj = newGLine(x0, y0, x1, y1);
   draw(gw, gobj);
   freeGObject(gobj);
}

GPoint drawPolarLine(GWindow gw, double x, double y, double r, double theta) {
   double x1, y1;

   x1 = x + r * cosDegrees(theta);
   y1 = y - r * sinDegrees(theta);
   drawLine(gw, x, y, x1, y1);
   return createGPoint(x1, y1);
}

void drawOval(GWindow gw, double x, double y, double width, double height) {
   GObject gobj;

   gobj = newGOval(x, y, width, height);
   setColor(gobj, gw->color);
   draw(gw, gobj);
   freeGObject(gobj);
}

void fillOval(GWindow gw, double x, double y, double width, double height) {
   GObject gobj;

   gobj = newGOval(x, y, width, height);
   setFilled(gobj, true);
   setColor(gobj, gw->color);
   draw(gw, gobj);
   freeGObject(gobj);
}

void drawRect(GWindow gw, double x, double y, double width, double height) {
   GObject gobj;

   gobj = newGRect(x, y, width, height);
   setColor(gobj, gw->color);
   draw(gw, gobj);
   freeGObject(gobj);
}

void fillRect(GWindow gw, double x, double y, double width, double height) {
   GObject gobj;

   gobj = newGRect(x, y, width, height);
   setFilled(gobj, true);
   setColor(gobj, gw->color);
   draw(gw, gobj);
   freeGObject(gobj);
}

void setColorGWindow(GWindow gw, string color) {
   gw->color = color;
}

string getColorGWindow(GWindow gw) {
   return gw->color;
}

double getWidthGWindow(GWindow gw) {
   return gw->width;
}

double getHeightGWindow(GWindow gw) {
   return gw->height;
}

void repaint(GWindow gw) {
   repaintOp(gw);
}

void setWindowTitle(GWindow gw, string title) {
   gw->title = title;
   setWindowTitleOp(gw, title);
}

string getWindowTitle(GWindow gw) {
   return gw->title;
}

void draw(GWindow gw, GObject gobj) {
   drawOp(gw, gobj);
}

void drawAt(GWindow gw, GObject gobj, double x, double y) {
   setLocation(gobj, x, y);
   drawOp(gw, gobj);
}

void addGWindow(GWindow gw, GObject gobj) {
   addGCompound(gw->top, gobj);
}

void addAt(GWindow gw, GObject gobj, double x, double y) {
   setLocation(gobj, x, y);
   addGCompound(gw->top, gobj);
}

void addToRegion(GWindow gw, GObject gobj, string region) {
   addToRegionOp(gw, gobj, region);
}

void removeGWindow(GWindow gw, GObject gobj) {
   removeGCompound(gw->top, gobj);
}

GObject getGObjectAt(GWindow gw, double x, double y) {
   return getGObjectCompound(gw->top, x, y);
}

void setRegionAlignment(GWindow gw, string region, string align) {
   setRegionAlignmentOp(gw, region, align);
}

void pause(double milliseconds) {
   pauseOp(milliseconds);
}
