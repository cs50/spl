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
#include "vector.h"

#include "color.h"

#if (__STDC_VERSION__ >= 201112L)
    #define static_assert(pred, msg) _Static_assert(pred, msg)
#else
    #define ASSERT_CONCAT_(a, b) a##b
    #define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
    #define static_assert(pred, _unused) enum { ASSERT_CONCAT(assertion_line, __LINE__) = 1 / (int) pred } // This error means that fuck you
#endif

static_assert(sizeof (GPoint) != sizeof (GObject),
               "SPL will not work on an architecture in which "
               "GPoint is the same size as GObject");

static_assert(sizeof (GRectangle) != sizeof (GObject),
               "SPL will not work on an architecture in which "
               "GRectangle is the same size as GObject");

bool containsGeneric(int size, ...)
{
    va_list args;

    va_start(args, size);
    if (size == sizeof(GRectangle)) {
        GRectangle r = va_arg(args, GRectangle);
        GPoint pt = va_arg(args, GPoint);
        va_end(args);
        return containsGRectangle(r, pt);
    }
    void *arg = va_arg(args, void *);
    unsigned char type = getBlockType(arg);
    if (type == GOBJECT) {
        double x = va_arg(args, double);
        double y = va_arg(args, double);
        bool result = containsGObject((GObject) arg, x, y);
        va_end(args);
        return result;
    } else {
        error("contains: Unrecognized type");
    }
}

int _getGObjectType(GObject);

void add(void *container, void *item)
{
    if (getBlockType(item) != GOBJECT) {
        error("Object to be added does not appear to be a GOBJECT");
    }

    unsigned char type = getBlockType(container);
    if (type == GWINDOW) {
        addGWindow(container, item);
    } else if (type == GOBJECT && _getGObjectType(container) == GCOMPOUND) {
        addGCompound(container, item);
    } else {
        error("add: Unrecognized type");
    }
}

void remove(void *container, void *item)
{
    if (getBlockType(item) != GOBJECT) {
        error("Object to be removed does not appear to be a GOBJECT");
    }

    unsigned char type = getBlockType(container);
    if (type == GWINDOW) {
        removeGWindow(container, item);
    } else if (type == GOBJECT && _getGObjectType(container) == GCOMPOUND) {
        removeGCompound(container, item);
    } else {
        error("remove: Unrecognized type");
    }
}

double getXGeneric(int size, ...)
{
    va_list args;
    va_start(args, size);
    if (size == sizeof(GPoint)) {
        GPoint pt = va_arg(args, GPoint);
        va_end(args);
        return getXGPoint(pt);
    } else if (size == sizeof(GRectangle)) {
        GRectangle r = va_arg(args, GRectangle);
        va_end(args);
        return getXGRectangle(r);
    }

    void *arg = va_arg(args, void *);
    va_end(args);
    unsigned char type = getBlockType(arg);
    if (type == GEVENT) {
        return getXGEvent(arg);
    } else if (type == GOBJECT) {
        return getXGObject(arg);
    } else {
        error("getX: Illegal argument type");
    }
}

double getYGeneric(int size, ...)
{
    va_list args;

    va_start(args, size);
    if (size == sizeof(GPoint)) {
        GPoint pt = va_arg(args, GPoint);
        va_end(args);
        return getYGPoint(pt);
    } else if (size == sizeof(GRectangle)) {
        GRectangle r = va_arg(args, GRectangle);
        va_end(args);
        return getYGRectangle(r);
    }
    void *arg = va_arg(args, void *);
    va_end(args);
    unsigned char type = getBlockType(arg);
    if (type == GEVENT) {
        return getYGEvent((GEvent) arg);
    } else if (type == GOBJECT) {
        return getYGObject((GObject) arg);
    } else {
        error("getY: Illegal argument type");
    }
}

double getWidthGeneric(int size, ...)
{
    va_list args;
    va_start(args, size);
    if (size == sizeof(GDimension)) {
        GDimension dim = va_arg(args, GDimension);
        va_end(args);
        return getWidthGDimension(dim);
    } else if (size == sizeof(GRectangle)) {
        GRectangle r = va_arg(args, GRectangle);
        va_end(args);
        return getWidthGRectangle(r);
    }
    void *arg = va_arg(args, void *);
    va_end(args);
    unsigned char type = getBlockType(arg);
    if (type == GWINDOW) {
        return getWidthGWindow(arg);
    } else if (type == GOBJECT) {
        return getWidthGObject((GObject) arg);
    } else {
        error("getWidth: Illegal argument type");
    }
}

double getHeightGeneric(int size, ...)
{
    va_list args;
    va_start(args, size);
    if (size == sizeof(GDimension)) {
        GDimension dim = va_arg(args, GDimension);
        va_end(args);
        return getHeightGDimension(dim);
    } else if (size == sizeof(GRectangle)) {
        GRectangle r = va_arg(args, GRectangle);
        va_end(args);
        return getHeightGRectangle(r);
    }
    void *arg = va_arg(args, void *);
    va_end(args);
    unsigned char type = getBlockType(arg);
    if (type == GWINDOW) {
        return getHeightGWindow((GWindow) arg);
    } else if (type == GOBJECT) {
        return getHeightGObject((GObject) arg);
    } else {
        error("getHeight: Illegal argument type");
    }
}


void setVisible(void *arg, bool flag)
{
    unsigned char type = getBlockType(arg);
    if (type == GOBJECT) {
        setVisibleGObject(arg, flag);
    } else if (type == GWINDOW) {
        setVisibleGWindow(arg, flag);
    } else {
        error("setVisible: Unrecognized type");
    }
}

bool isVisible(void *arg)
{
    unsigned char type = getBlockType(arg);
    if (type == GOBJECT) {
        return isVisibleGObject(arg);
    } else if (type == GWINDOW) {
        return isVisibleGWindow(arg);
    } else {
        error("isVisible: Unrecognized type");
    }
}

void setColor(void *arg, string color)
{
    Color c;

    if (!mapStringColor(color, &c)) {
        error("setColor: Unrecognized color: %s", color);
    }

    unsigned char type = getBlockType(arg);
    if (type == GOBJECT) {
        setColorGObject(arg, c);
    } else if (type == GWINDOW) {
        setColorGWindow((GWindow) arg, c);
    } else {
        error("setColor: Unrecognized type");
    }
}
