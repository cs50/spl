/*
 * File: generic.c
 * ---------------
 * This file implements the generic.h interface.
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
#include <stdarg.h>
#include "cslib.h"
#include "generic.h"
#include "gevents.h"
#include "gobjects.h"
#include "gtypes.h"
#include "strlib.h"
#include "vector.h"

#include "color.h"

/* Constants */

#define BUFSIZE 40

bool isEmptyGeneric(int size, ...) {
    va_list args;
    void *arg;
    bool result;
    string type;

    va_start(args, size);
    if (size == sizeof(GRectangle)) {
        result = isEmptyGRectangle(va_arg(args, GRectangle));
        va_end(args);
        return result;
    }
    arg = va_arg(args, void *);
    va_end(args);
    type = getBlockType(arg);
    if (endsWith(type, "Vector")) {
        return isEmptyVector((Vector) arg);
    } else {
        error("isEmpty: Unrecognized type %s", type);
    }
}

bool containsGeneric(int size, ...) {
    string type;
    void *arg;
    double x, y;
    bool result;
    va_list args;
    GRectangle r;
    GPoint pt;

    va_start(args, size);
    if (size == sizeof(GRectangle)) {
        r = va_arg(args, GRectangle);
        pt = va_arg(args, GPoint);
        va_end(args);
        return containsGRectangle(r, pt);
    }
    arg = va_arg(args, void *);
    type = getBlockType(arg);
    if (endsWith(type, "GObject")) {
        x = va_arg(args, double);
        y = va_arg(args, double);
        result = containsGObject((GObject) arg, x, y);
        va_end(args);
        return result;
    } else {
        error("contains: Unrecognized type %s", type);
    }
}

void add(void *arg, ...) {
    string type;
    void *value;
    va_list args;

    type = getBlockType(arg);
    if (endsWith(type, "Vector")) {
        va_start(args, arg);
        value = va_arg(args, void *);
        va_end(args);
        addVector((Vector) arg, value);
    } else if (endsWith(type, "GWindow")) {
        va_start(args, arg);
        addGWindow((GWindow) arg, va_arg(args, GObject));
        va_end(args);
    } else if (endsWith(type, "GCompound")) {
        va_start(args, arg);
        addGCompound((GWindow) arg, va_arg(args, GObject));
        va_end(args);
    } else {
        error("add: Unrecognized type %s", type);
    }
}

void remove(void *arg, ...) {
    GObject gobj;
    string type;
    int index;
    va_list args;

    type = getBlockType(arg);
    if (endsWith(type, "Vector")) {
        va_start(args, arg);
        index = va_arg(args, int);
        va_end(args);
        removeVector((Vector) arg, index);
        va_end(args);
    } else if (endsWith(type, "GWindow")) {
        va_start(args, arg);
        gobj = va_arg(args, GObject);
        va_end(args);
        removeGWindow((GWindow) arg, gobj);
    } else {
        error("remove: Unrecognized type %s", type);
    }
}

double getXGeneric(int size, ...) {
    va_list args;
    GPoint pt;
    GRectangle r;
    void *arg;
    string type;

    va_start(args, size);
    if (size == sizeof(GPoint)) {
        pt = va_arg(args, GPoint);
        va_end(args);
        return getXGPoint(pt);
    } else if (size == sizeof(GRectangle)) {
        r = va_arg(args, GRectangle);
        va_end(args);
        return getXGRectangle(r);
    }
    arg = va_arg(args, void *);
    va_end(args);
    type = getBlockType(arg);
    if (endsWith(type, "GEvent")) {
        return getXGEvent((GEvent) arg);
    } else if (endsWith(type, "GObject")) {
        return getXGObject((GObject) arg);
    } else {
        error("getX: Illegal argument type");
    }
}

double getYGeneric(int size, ...) {
    va_list args;
    GPoint pt;
    GRectangle r;
    void *arg;
    string type;

    va_start(args, size);
    if (size == sizeof(GPoint)) {
        pt = va_arg(args, GPoint);
        va_end(args);
        return getYGPoint(pt);
    } else if (size == sizeof(GRectangle)) {
        r = va_arg(args, GRectangle);
        va_end(args);
        return getYGRectangle(r);
    }
    arg = va_arg(args, void *);
    va_end(args);
    type = getBlockType(arg);
    if (endsWith(type, "GEvent")) {
        return getYGEvent((GEvent) arg);
    } else if (endsWith(type, "GObject")) {
        return getYGObject((GObject) arg);
    } else {
        error("getY: Illegal argument type");
    }
}

double getWidthGeneric(int size, ...) {
    va_list args;
    GDimension dim;
    GRectangle r;
    string type;
    void *arg;

    va_start(args, size);
    if (size == sizeof(GDimension)) {
        dim = va_arg(args, GDimension);
        va_end(args);
        return getWidthGDimension(dim);
    } else if (size == sizeof(GRectangle)) {
        r = va_arg(args, GRectangle);
        va_end(args);
        return getWidthGRectangle(r);
    }
    arg = va_arg(args, void *);
    va_end(args);
    type = getBlockType(arg);
    if (endsWith(type, "GWindow")) {
        return getWidthGWindow((GWindow) arg);
    } else if (endsWith(type, "GObject")) {
        return getWidthGObject((GObject) arg);
    } else {
        error("getWidth: Illegal argument type");
    }
}

double getHeightGeneric(int size, ...) {
    va_list args;
    GDimension dim;
    GRectangle r;
    string type;
    void *arg;

    va_start(args, size);
    if (size == sizeof(GDimension)) {
        dim = va_arg(args, GDimension);
        va_end(args);
        return getHeightGDimension(dim);
    } else if (size == sizeof(GRectangle)) {
        r = va_arg(args, GRectangle);
        va_end(args);
        return getHeightGRectangle(r);
    }
    arg = va_arg(args, void *);
    va_end(args);
    type = getBlockType(arg);
    if (endsWith(type, "GWindow")) {
        return getHeightGWindow((GWindow) arg);
    } else if (endsWith(type, "GObject")) {
        return getHeightGObject((GObject) arg);
    } else {
        error("getHeight: Illegal argument type");
    }
}


void setVisible(void *arg, bool flag) {
    string type;

    type = getBlockType(arg);
    if (endsWith(type, "GObject")) {
        setVisibleGObject((GObject) arg, flag);
    } else if (endsWith(type, "GWindow")) {
        setVisibleGWindow((GWindow) arg, flag);
    } else {
        error("setVisible: Unrecognized type %s", type);
    }
}

bool isVisible(void *arg) {
    string type;

    type = getBlockType(arg);
    if (endsWith(type, "GObject")) {
        return isVisibleGObject((GObject) arg);
    } else if (endsWith(type, "GWindow")) {
        return isVisibleGWindow((GWindow) arg);
    } else {
        error("isVisible: Unrecognized type %s", type);
    }
}

void setColor(void *arg, string color) {
    string type = getBlockType(arg);
    Color c;

    if (!mapStringColor(color, &c)) {
        error("setColor: Unrecognized color: %s", color);
    }

    if (endsWith(type, "GObject")) {
        setColorGObject((GObject) arg, c);
    } else if (endsWith(type, "GWindow")) {
        setColorGWindow((GWindow) arg, c);
    } else {
        error("setColor: Unrecognized type %s", type);
    }
}
