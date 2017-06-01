/*
 * File: pqueue.h
 * --------------
 * This interface defines a queue abstraction that dequeues elements
 * in priority order.  In keeping with traditional English usage,
 * lower priority numbers have higher priority, so that priority 1
 * items appear before priority 2 items.
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

#ifndef _pqueue_h
#define _pqueue_h

#include "cslib.h"
#include "generic.h"

/*
 * Type: PriorityQueue
 * -------------------
 * This type defines the abstract type for a queue.
 */

typedef struct PriorityQueueCDT *PriorityQueue;

/*
 * Function: newPriorityQueue
 * Usage: pq = newPriorityQueue();
 * -------------------------------
 * Allocates and returns an empty priority queue.
 */

PriorityQueue newPriorityQueue(void);

/*
 * Function: freePriorityQueue
 * Usage: freePriorityQueue(pq);
 * -----------------------------
 * Frees the storage associated with the specified priority queue.
 */

void freePriorityQueue(PriorityQueue pq);

/*
 * Function: enqueue
 * Usage: enqueue(pq, value, priority);
 * ------------------------------------
 * Adds a value to the queue in the order specified by <code>priority</code>.
 * In C, the <code>priority</code> argument must have type <code>double</code>,
 * which means that constants used to express priorities in the call to the
 * generic <code>enqueue</code> function must include a decimal point.
 */

void enqueuePriorityQueue(PriorityQueue pq, void *value, double priority);

/*
 * Function: dequeue
 * Usage: value = dequeue(pq);
 * ---------------------------
 * Removes the data value at the head of the queue and returns it
 * to the client.  If the queue is empty, <code>dequeue</code> calls
 * <code>error</code> with an appropriate message.
 */

void *dequeuePriorityQueue(PriorityQueue pq);

/*
 * Function: peek
 * Usage: value = peek(pq);
 * ------------------------
 * Returns the data value at the head of the queue without removing it.
 * If the queue is empty, <code>peek</code> calls <code>error</code> with
 * an appropriate message.
 */

void *peekPriorityQueue(PriorityQueue pq);

/*
 * Function: peekPriority
 * Usage: priority = peekPriority(pq);
 * -----------------------------------
 * Returns the priority of the first entry in the queue, without
 * removing it.
 */

double peekPriority(PriorityQueue pq);

/*
 * Function: isEmpty
 * Usage: if (isEmpty(pq)) . . .
 * -----------------------------
 * Tests whether the queue is empty.
 */

bool isEmptyPriorityQueue(PriorityQueue pq);

/*
 * Function: size
 * Usage: n = size(pq);
 * --------------------
 * Returns the number of values in the queue.
 */

int sizePriorityQueue(PriorityQueue pq);

/*
 * Function: clear
 * Usage: clear(pq);
 * -----------------
 * Removes all values from the queue.
 */

void clearPriorityQueue(PriorityQueue pq);

/*
 * Function: clone
 * Usage: newpq = clone(pq);
 * -------------------------
 * Creates a copy of the priority queue.  The <code>clone</code> function
 * copies only the first level of the structure and does not copy the
 * individual elements.
 */

PriorityQueue clonePriorityQueue(PriorityQueue pq);

#endif
