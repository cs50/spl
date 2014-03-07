/*
 * File: Breakout.c
 * ----------------
 * Need I say more . . .
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
#include "random.h"
#include "sound.h"

/* Size of the window */

#define WIDTH 400
#define HEIGHT 600

/* Dimensions of the paddle */
#define PADDLE_WIDTH 60
#define PADDLE_HEIGHT 10

/* Offset of the paddle up from the bottom */
#define PADDLE_Y_OFFSET 30

/* Number of bricks per row */
#define BRICKS_IN_ROW 10

/* Number of rows of bricks */
#define BRICK_ROWS 10

/* Separation between bricks */
#define BRICK_SEP 4

/* Width of a brick */
#define BRICK_WIDTH (WIDTH - (BRICKS_IN_ROW - 1) * BRICK_SEP) / BRICKS_IN_ROW

/* Height of a brick */
#define BRICK_HEIGHT 8

/* Radius of the ball in pixels */
#define BALL_RADIUS 10

/* Offset of the top brick row from the top */
#define BRICK_Y_OFFSET 70

/* Number of turns */
#define NTURNS 3

/* Pause time in milliseconds */
#define PAUSE_TIME 10.0

/* Delay between turns */
#define TURN_DELAY 500.0

/* Use sounds */
#define USE_SOUNDS true

/* Global variable */

static Sound bounce = NULL;

/* Function prototypes */

void setupBricks(GWindow gw);
string getBrickColor(int row);
void playGame(GWindow gw);
GObject getCollidingObject(GWindow gw, GObject ball);
void playBounceSound();

/* Main program */

int main() {
   GWindow gw;

   gw = newGWindow(WIDTH, HEIGHT);
   playGame(gw);
   return 0;
}

void setupBricks(GWindow gw) {
   GRect brick;
   int row, col;
   double x, y;

   for (row = 0; row < BRICK_ROWS; row++) {
      y = BRICK_Y_OFFSET + row * (BRICK_HEIGHT + BRICK_SEP);
      for (col = 0; col < BRICKS_IN_ROW; col++) {
         x = 2 + col * (BRICK_WIDTH + BRICK_SEP);
         brick = newGRect(x, y, BRICK_WIDTH, BRICK_HEIGHT);
         setFilled(brick, true);
         setColor(brick, getBrickColor(row));
         add(gw, brick);
      }
   }
}

string getBrickColor(int row) {
   switch (row) {
    case 0: case 1: return "RED";
    case 2: case 3: return "ORANGE";
    case 4: case 5: return "YELLOW";
    case 6: case 7: return "GREEN";
    case 8: case 9: return "CYAN";
    default: return "GRAY";
   }
};

void playGame(GWindow gw) {
   double width, height, r, bx, by, px, py, vx, vy;
   int nBricksRemaining, nBallsLeft;
   GObject collider = NULL;
   GOval ball;
   GRect paddle;
   GEvent e;

   setupBricks(gw);
   width = getWidth(gw);
   height = getHeight(gw);
   r = BALL_RADIUS;
   bx = width / 2 - r;
   by = height / 2 - r;
   ball = newGOval(bx, by, 2 * r, 2 * r);
   setFilled(ball, true);
   add(gw, ball);
   px = (width - PADDLE_WIDTH) / 2;
   py = height - PADDLE_HEIGHT - PADDLE_Y_OFFSET;
   paddle = newGRect(px, py, PADDLE_WIDTH, PADDLE_HEIGHT);
   setFilled(paddle, true);
   add(gw, paddle);
   nBricksRemaining = BRICKS_IN_ROW * BRICK_ROWS;
   nBallsLeft = 3;
   while (nBallsLeft > 0 && nBricksRemaining > 0) {
      waitForClick();
      nBallsLeft--;
      vx = randomReal(1, 2);
      if (randomChance(0.5)) vx = -vx;
      vy = 3.0;
      while (getY(ball) < height - r && nBricksRemaining > 0) {
         e = getNextEvent(MOUSE_EVENT);
         if (e != NULL) {
            if (getEventType(e) == MOUSE_MOVED) {
               px = getX(e) - PADDLE_WIDTH;
               if (px < 0) px = 0;
               if (px > width - PADDLE_WIDTH) px = width - PADDLE_WIDTH;
               setLocation(paddle, px, py);
            }
         } else {
            move(ball, vx, vy);
            if (getX(ball) < 0 || getX(ball) > width - 2 * r) vx = -vx;
            if (getY(ball) < 0) vy = -vy;
            GObject collider = getCollidingObject(gw, ball);
            if (collider != NULL) {
               if (USE_SOUNDS) playBounceSound();
               if (collider == paddle) {
                  vy = -vy;
                  setLocation(ball, getX(ball), getY(paddle) - 2 * r);
               } else {
                  remove(gw, collider);
                  nBricksRemaining--;
                  vy = -vy;
               }
            }
            pause(PAUSE_TIME);
         }
      }
      pause(TURN_DELAY);
      setLocation(ball, bx, by);
   }
   waitForClick();
}

GObject getCollidingObject(GWindow gw, GObject ball) {
   double x, y, d;
   GObject obj;

   x = getX(ball);
   y = getY(ball);
   d = 2 * BALL_RADIUS;
   obj = getGObjectAt(gw, x, y);
   if (obj == NULL) obj = getGObjectAt(gw, x + d, y);
   if (obj == NULL) obj = getGObjectAt(gw, x, y + d);
   if (obj == NULL) obj = getGObjectAt(gw, x + d, y + d);
   return obj;
}

void playBounceSound() {
   if (bounce == NULL) bounce = newSound("Bounce.wav");
   playSound(bounce);
}
