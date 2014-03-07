/*
 * File: gtimer.h
 * --------------
 * This interface exports a general interval timer.
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

#ifndef _gtimer_h
#define _gtimer_h

#include "cslib.h"

/*
 * Type: GTimer
 * ------------
 * This type implements a simple interval timer that generates a timer
 * event with a specified frequency.
 */

typedef struct GTimerCDT *GTimer;

/*
 * Function: newGTimer
 * Usage: timer = newGTimer(milliseconds);
 * ---------------------------------------
 * Creates a timer that generates a timer event each time the specified
 * number of milliseconds has elapsed.  No events are generated until
 * the client calls <code>startTimer</code>.
 */

GTimer newGTimer(double milliseconds);

/*
 * Function: freeGTimer
 * Usage: freeGTimer(timer);
 * -------------------------
 * Frees the resources associated with the timer.
 */

void freeGTimer(GTimer timer);

/*
 * Function: startTimer
 * Usage: startTimer(timer);
 * -------------------------
 * Starts the timer.  A timer continues to generate timer events until it
 * is stopped; to achieve the effect of a one-shot timer, the simplest
 * approach is to call the <code>stop</code> function inside the event
 * handler.
 */

void startTimer(GTimer timer);

/*
 * Function: stopTimer
 * Usage: stopTimer(timer);
 * ------------------------
 * Stops the timer so that it stops generating events.
 */

void stopTimer(GTimer timer);

#endif
