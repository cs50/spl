/*
 * File: queue.h
 * -------------
 * This interface defines a queue abstraction with first-in/first-out
 * semantics.
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

#ifndef _queue_h
#define _queue_h

#include "cslib.h"
#include "generic.h"

/*
 * Type: Queue
 * -----------
 * This type defines the abstract type for a queue.
 */

typedef struct QueueCDT *Queue;

/*
 * Function: newQueue
 * Usage: queue = newQueue();
 * --------------------------
 * Allocates and returns an empty queue.
 */

Queue newQueue(void);

/*
 * Function: freeQueue
 * Usage: freeQueue(queue);
 * ------------------------
 * Frees the storage associated with the specified queue.
 */

void freeQueue(Queue queue);

/*
 * Function: enqueue
 * Usage: enqueue(queue, element);
 * -------------------------------
 * Adds an element to the end of the queue.
 */

void enqueueQueue(Queue queue, void *element);

/*
 * Function: dequeue
 * Usage: element = dequeue(queue);
 * --------------------------------
 * Removes the data value at the head of the queue and returns it
 * to the client.  If the queue is empty, <code>dequeue</code> calls
 * <code>error</code> with an appropriate message.
 */

void *dequeueQueue(Queue queue);

/*
 * Function: peek
 * Usage: element = peek(queue);
 * -----------------------------
 * Returns the data value at the head of the queue without removing it.
 * If the queue is empty, <code>peek</code> calls <code>error</code> with
 * an appropriate message.
 */

void *peekQueue(Queue queue);

/*
 * Function: isEmpty
 * Usage: if (isEmpty(queue)) . . .
 * --------------------------------
 * Tests whether the queue is empty.
 */

bool isEmptyQueue(Queue queue);

/*
 * Function: size
 * Usage: n = size(queue);
 * -----------------------
 * Returns the number of elements in the queue.
 */

int sizeQueue(Queue queue);

/*
 * Function: clear
 * Usage: clear(queue);
 * --------------------
 * Removes all elements from the queue.
 */

void clearQueue(Queue queue);

/*
 * Function: clone
 * Usage: newqueue = clone(queue);
 * -------------------------------
 * Creates a copy of the queue.  The <code>clone</code> function copies
 * only the first level of the structure and does not copy the individual
 * elements.
 */

Queue cloneQueue(Queue queue);

#endif
