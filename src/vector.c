/*
 * File: vector.c
 * --------------
 * This file implements the vector.h interface.
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
#include <string.h>
#include "cslib.h"
#include "generic.h"
#include "vector.h"

/*
 * Constant: INITIAL_CAPACITY
 * --------------------------
 * This constant defines the initial capacity of the array.
 * Any positive value will work correctly, although changing
 * this parameter can affect performance.  Making this value
 * larger postpones the first reallocation but causes vectors
 * to consume more memory.
 */

#define INITIAL_CAPACITY 10

/*
 * Type: VectorCDT
 * ---------------
 * The type VectorCDT is the concrete representation of the type
 * Vector defined by the interface.
 */

struct VectorCDT {
    void **elements;
    int count;
    int capacity;
};

/* Private function prototypes */

static void expandCapacity(Vector vector);

/* Exported entries */

Vector newVector(void)
{
    Vector vector = newBlock(Vector);
    vector->elements = calloc(INITIAL_CAPACITY, sizeof *vector->elements);
    if (!vector->elements) error("Memory allocation failure");
    vector->count = 0;
    vector->capacity = INITIAL_CAPACITY;
    return vector;
}

void freeVector(Vector vector)
{
    free(vector->elements);
    freeBlock(vector);
}

bool isEmptyVector(Vector vector)
{
    return vector->count == 0;
}

int sizeVector(Vector vector)
{
    return vector->count;
}

void clearVector(Vector vector)
{
    vector->count = 0;
}

void *getVector(Vector vector, int index)
{
    if (index < 0 || index >= vector->count) {
        error("get: Index value out of range");
    }
    return vector->elements[index];
}

void setVector(Vector vector, int index, void *value)
{
    if (index < 0 || index >= vector->count) {
        error("get: Index value out of range");
    }
    vector->elements[index] = value;
}

void addVector(Vector vector, void *value)
{
    if (vector->count == vector->capacity) {
        expandCapacity(vector);
    }
    vector->elements[vector->count++] = value;
}

void insert(Vector vector, int index, void *value)
{
    if (index < 0 || index > vector->count) {
        error("insert: Index value out of range");
    }
    if (vector->count == vector->capacity) {
        expandCapacity(vector);
    }
    void **inserted = vector->elements + index;
    memmove(inserted+1, inserted, (vector->count++ - index) * sizeof (void*));
    *inserted = value;
}

void insertAt(Vector vector, int index, void *value)
{
    insert(vector, index, value);
}

void removeVector(Vector vector, int index)
{
    if (index < 0 || index >= vector->count) {
        error("remove: Index value out of range");
    }
    void **removed = vector->elements + index;
    memmove(removed, removed+1, (--vector->count - index) * sizeof (void *));
}

void removeAt(Vector vector, int index)
{
    removeVector(vector, index);
}


int findVector(Vector vector, void *value)
{
    void **vend = vector->elements + vector->count;
    for (void **vitem = vector->elements; vitem != vend; vitem++) {
        if (*vitem == value) return vitem - vector->elements;
    }
    return -1;
}

/* Private functions */

static void expandCapacity(Vector vector)
{
    void **array;
    int i, newCapacity;

    newCapacity = vector->capacity * 2;
    array = calloc(newCapacity, sizeof *array);
    for (i = 0; i < vector->count; i++) {
        array[i] = vector->elements[i];
    }
    freeBlock(vector->elements);
    vector->elements = array;
    vector->capacity = newCapacity;
}


#define swap(X,Y) do { __typeof__(X) T = X; X = Y; Y = T; } while (0);
void sendForwardVector(Vector vector, int index)
{
    if (index < 0 || index >= vector->count-1) return;
    swap(vector->elements[index], vector->elements[index+1]);
}

void sendToFrontVector(Vector vector, int index)
{
    if (index < 0 || index >= vector->count-1) return;
    void *temp = vector->elements[index];
    removeVector(vector, index);
    addVector(vector, temp);
}

void sendBackwardVector(Vector vector, int index)
{
    if (index <= 0 || index >= vector->count) return;
    swap(vector->elements[index], vector->elements[index+1]);
}

void sendToBackVector(Vector vector, int index)
{
    if (index <= 0 || index >= vector->count) return;
    void *temp = vector->elements[index];
    memmove(vector->elements + 1, vector->elements, index * sizeof (void *));
    *vector->elements = temp;
}
