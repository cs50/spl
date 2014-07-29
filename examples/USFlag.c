/*
 * File: USFlag.c
 * --------------
 * This program draws a US flag that fills the window.
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
#include "gmath.h"
#include "gobjects.h"
#include "gevents.h"
#include "gwindow.h"

/* Constants */

#define FLAG_WIDTH 740
#define FLAG_HEIGHT 400
#define FIELD_FRACTION 0.40
#define STAR_FRACTION 0.40

/* Prototypes */

static void drawStripes(GWindow gw);
static void drawField(GWindow gw);
static void drawObama(GWindow gw);
static GPolygon newGStar(double size);

int main() {
   GWindow gw = newGWindow(FLAG_WIDTH, FLAG_HEIGHT);
   drawStripes(gw);
   drawField(gw);
   waitForClick();
   drawObama(gw);
   return 0;
}

/* Draw the stripes */

static void drawStripes(GWindow gw) {
   double width = getWidth(gw);
   double height = getHeight(gw);
   double stripeHeight = height / 13;
   int i;
   for (i = 12; i >= 0; i--) {
      GRect stripe = newGRect(0, i * stripeHeight, width, stripeHeight);
      setFilled(stripe, true);
      setColor(stripe, (i % 2 == 0) ? "RED" : "WHITE");
      add(gw, stripe);
   }
}

/* Draw the star field */

static void drawField(GWindow gw) {
   double width = getWidth(gw);
   double height = getHeight(gw);
   double fieldWidth = FIELD_FRACTION * width;
   double fieldHeight = height * 7 / 13;
   GRect field = newGRect(0, 0, fieldWidth, fieldHeight);
   setColor(field, "BLUE");
   setFilled(field, true);
   add(gw, field);
   double dx = fieldWidth / 6;
   double dy = fieldHeight / 5;
   double starSize = STAR_FRACTION * fmin(dx, dy);
   int row, col;
   for (row = 0; row < 5; row++) {
      double y = (row + 0.5) * dy;
      for (col = 0; col < 6; col++) {
         GPolygon star = newGStar(starSize);
         setColor(star, "WHITE");
         setFilled(star, true);
         double x = (col + 0.5) * dx;
         addAt(gw, star, x, y);
      }
   }
   for (row = 0; row < 4; row++) {
      double y = (row + 1) * dy;
      for (col = 0; col < 5; col++) {
         GPolygon star = newGStar(starSize);
         setColor(star, "WHITE");
         setFilled(star, true);
         double x = (col + 1) * dx;
         addAt(gw, star, x, y);
      }
   }
}

/* Draw a picture of President Obama */

static void drawObama(GWindow gw) {
   double width = getWidth(gw);
   double height = getHeight(gw);
   double fieldWidth = FIELD_FRACTION * width;
   GImage obama = newGImage("Obama.png");
   double x = fieldWidth + (width - fieldWidth - getWidth(obama)) / 2;
   double y = (height - getHeight(obama)) / 2;
   addAt(gw, obama, x, y);
}

/* Create a star polygon */

static GPolygon newGStar(double size) {
   GPolygon star = newGPolygon();
   double dx = size / 2;
   double dy = dx * tanDegrees(18);
   double edge = size / 2 - dy * tanDegrees(36);
   addVertex(star, -dx, -dy);
   int angle = 0;
   int i;
   for (i = 0; i < 5; i++) {
      addPolarEdge(star, edge, angle);
      addPolarEdge(star, edge, angle + 72);
      angle -= 72;
   }
   return star;
}
