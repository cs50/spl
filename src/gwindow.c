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
#include <stdint.h>
#include <assert.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "private/helpers.h"
#include "generic.h"
#include "gmath.h"
#include "gobjects.h"
#include "gtypes.h"
#include "gwindow.h"
#include "gcolor.h"



// Global list of all allocated windows. This could in theory be a dynamically
// allocated array or linked list, but for simplicity, I've capped the number
// of windows at 128. Any more than this would be ridiculous anyway. We do
// linear search, which is fine; this array will fit well within a cache line.
#define MAX_WIN 128
static GWindow windows[MAX_WIN] = {0};

void setWindow(GObject gobj, GWindow win);
static void drawOp(GObject gobj, GWindow gw);
static inline void drawGOvalOp(GWindow gw, GOval oval);
static inline void drawGRectOp(GWindow gw, GRect rect);
static inline void drawGLineOp(GWindow gw, GLine line);
static inline void drawGPolyOp(GWindow gw, GPolygon poly);

struct GWindowCDT {
    GCompound contents;
    SDL_Window *win;
    SDL_Renderer *ren;
};


GWindow newGWindow(double width, double height)
{

    requiresSubsystem(SDL_INIT_VIDEO);

    size_t idx = 0;
    for (; idx != MAX_WIN; idx++) {
    }

    if (win == WIN_END) {
        error("newGWindow: maximum number of windows created");
    }

    GWindow gw = *win = newBlock(GWindow);
    gw->contents = newGCompound();
    setWindow(gw->contents, gw);
    SDL_CreateWindowAndRenderer(width, height, 0, &gw->win, &gw->ren);
    setWindowTitle(gw, "Untitled");
    setColorGWindow(gw, WHITE);
    SDL_RenderClear(gw->ren);
    SDL_RenderPresent(gw->ren);
    return gw;
}

void closeGWindow(GWindow gw)
{
    SDL_DestroyWindow(gw->win);
    gw->win = NULL;
    SDL_DestroyRenderer(gw->ren);
    gw->ren =  NULL;
    freeGObject(gw->contents);
    gw->contents = NULL;
}

void requestFocus(GWindow gw)
{
    SDL_RaiseWindow(gw->win);
}

void clearGWindow(GWindow gw)
{
    SDL_RenderClear(gw->ren);
    SDL_RenderPresent(gw->ren);
}

void setVisibleGWindow(GWindow gw, bool flag)
{
    if (flag) SDL_ShowWindow(gw->win);
    else      SDL_HideWindow(gw->win);
}

bool isVisibleGWindow(GWindow gw)
{
    return SDL_GetWindowFlags(gw->win) & SDL_WINDOW_SHOWN;
}

void drawLine(GWindow gw, double x0, double y0, double x1, double y1)
{
    GObject gobj = newGLine(x0, y0, x1, y1);
    drawGLineOp(gw, gobj);
    SDL_RenderPresent(gw->ren);
    freeGObject(gobj);
}

GPoint drawPolarLine(GWindow gw, double x, double y, double r, double theta)
{
    double x1 = x + r * cosDegrees(theta),
           y1 = y - r * sinDegrees(theta);
    drawLine(gw, x, y, x1, y1);
    return createGPoint(x1, y1);
}

void drawOval(GWindow gw, double x, double y, double width, double height)
{
    GObject gobj = newGOval(x, y, width, height);
    setColorGObject(gobj, getColorGWindow(gw));
    drawGOvalOp(gw, gobj);
    SDL_RenderPresent(gw->ren);
    freeGObject(gobj);
}

void fillOval(GWindow gw, double x, double y, double width, double height)
{
    GObject gobj = newGOval(x, y, width, height);
    setFilled(gobj, true);
    setColorGObject(gobj, getColorGWindow(gw));
    drawGOvalOp(gw, gobj);
    SDL_RenderPresent(gw->ren);
    freeGObject(gobj);
}

void drawRect(GWindow gw, double x, double y, double width, double height)
{
    GRect r = newGRect(x,y,width,height);
    setColorGObject(r, getColorGWindow(gw));
    drawGRectOp(gw, r);
    SDL_RenderPresent(gw->ren);
    freeGObject(r);

}

void fillRect(GWindow gw, double x, double y, double width, double height)
{
    GObject gobj = newGRect(x, y, width, height);
    setFilled(gobj, true);
    setColorGObject(gobj, getColorGWindow(gw));
    drawGRectOp(gw, gobj);
    SDL_RenderPresent(gw->ren);
    freeGObject(gobj);
}

void setColorGWindow(GWindow gw, GColor c)
{
    SDL_SetRenderDrawColor(gw->ren, c.r, c.g, c.b, c.a);

}

GColor getColorGWindow(GWindow gw)
{
    GColor c;
    SDL_GetRenderDrawColor(gw->ren, &c.r, &c.g, &c.b, &c.a);
    return c;
}

double getWidthGWindow(GWindow gw)
{
    int w = 0;
    SDL_GetWindowSize(gw->win, &w, NULL);
    return w;
}

double getHeightGWindow(GWindow gw)
{
    int h = 0;
    SDL_GetWindowSize(gw->win, NULL, &h);
    return h;
}

Vector getGCompoundContents(GCompound comp);
void repaint(GWindow gw)
{
    SDL_RenderClear(gw->ren);
    GCOMPOUND_APPLY(gw->contents, drawOp, gw);
    SDL_RenderPresent(gw->ren);
}

void setWindowTitle(GWindow gw, string title)
{
    SDL_SetWindowTitle(gw->win, title);
}

string getWindowTitle(GWindow gw)
{
    return (string) SDL_GetWindowTitle(gw->win);
}

GColor getFillColor(GObject gobj);

typedef struct {
    double x1;
    double y1;
    double x2;
    double y2;
} DrawBounds;

DrawBounds getDrawBounds(GObject gobj)
{
    return (DrawBounds) {
        .x1 = round(getXGObject(gobj))
              , .y1 = round(getYGObject(gobj))
              , .x2 = round(getXGObject(gobj) + getWidthGObject(gobj))
              , .y2 = round(getYGObject(gobj) + getHeightGObject(gobj))
    };
}

static inline void drawGRectOp(GWindow gw, GRect rect)
{
    DrawBounds d = getDrawBounds(rect);
    GColor c = getColorGObject(rect);
    if (isFilled(rect)) {
        boxRGBA(gw->ren, d.x2, d.y2, d.x1, d.y1, c.r, c.g, c.b, c.a);
    } else {
        rectangleRGBA(gw->ren, d.x2, d.y2, d.x1, d.y1, c.r, c.g, c.b, c.a);
    }
}


static inline void drawGLineOp(GWindow gw, GLine line)
{
    DrawBounds d = getDrawBounds(line);
    GColor c = getColorGObject(line);
    lineRGBA(gw->ren, d.x1, d.y1, d.x2, d.y2, c.r, c.g, c.b, c.a);
}

static inline void drawGOvalOp(GWindow gw, GOval oval)
{
    GColor c = getColorGObject(oval);
    double rx = getWidthGObject(oval) / 2,
           ry = getHeightGObject(oval) / 2,
           x  = getXGObject(oval),
           y  = getYGObject(oval);

    if (isFilled(oval)) {
        GColor c = getFillColor(oval);
        filledEllipseRGBA(gw->ren, x, y, rx, ry, c.r, c.g, c.b, c.a);
    } else {
        ellipseRGBA(gw->ren, x, y, rx, ry, c.r, c.g, c.b, c.a);
    }
}


static inline void drawGPolyOp(GWindow gw, GPolygon poly)
{
    GColor    c  = getColorGObject(poly);

    Vector   v  = getVertices(poly);
    int      n  = sizeVector(v);
    int16_t *xs = malloc(n * sizeof *xs);
    int16_t *ys = malloc(n * sizeof *ys);
    if (!xs || !ys) {
        error("Memory allocation failure");
    }
    for (int i = 0; i < n; i++) {
        GPoint *p = getVector(v,i);
        xs[i] = p->x;
        ys[i] = p->y;
    }
    if (isFilled(poly)) {
        filledPolygonRGBA(gw->ren, xs, ys, n, c.r, c.g, c.b, c.a);
    } else {
        polygonRGBA(gw->ren, xs, ys, n, c.r, c.g, c.b, c.a);
    }
    free(xs);
    free(ys);
}


TTF_Font *getRealFont(GLabel label);

static void drawGLabelOp(GWindow gw, GLabel label)
{
    if (!*getLabel(label)) return;
    GColor _c = getColorGObject(label);
    SDL_Color c = {_c.r, _c.b, _c.g, _c.a };
    SDL_Surface *surface = TTF_RenderText_Solid(getRealFont(label), getLabel(label), c);
    if (!surface) {
        printf("%s\n", TTF_GetError());
        assert(false);
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(gw->ren, surface);
    SDL_Rect dim = {getXGObject(label), getYGObject(label), getWidthGObject(label), getHeightGObject(label)};
    SDL_RenderCopy(gw->ren, tex, NULL, &dim);
    SDL_FreeSurface(surface);
}


static void drawOp(GObject gobj, GWindow gw)
{
    if (getType(gobj) == GCOMPOUND) {
        GCOMPOUND_APPLY(gobj, drawOp, gw);
        return;
    }
    if (!isVisibleGObject(gobj)) return;

    GColor orig = getColorGWindow(gw);

    switch (getType(gobj)) {
    case GRECT: drawGRectOp(gw, gobj);  break;
    case GLINE: drawGLineOp(gw, gobj);  break;
    case GPOLYGON: drawGPolyOp(gw, gobj); break;
    case GOVAL: drawGOvalOp(gw, gobj); break;
    case GLABEL: drawGLabelOp(gw, gobj); break;
    default: error("Drawing is unimplemented for this type");
    }
    setColorGWindow(gw, orig);

}

void draw(GWindow gw, GObject gobj)
{
    drawOp(gobj,gw);
    repaint(gw);
    SDL_RenderPresent(gw->ren);

}

void drawAt(GWindow gw, GObject gobj, double x, double y)
{
    setLocation(gobj, x, y);
    draw(gw, gobj);
}

void addGWindow(GWindow gw, GObject gobj)
{
    if (getType(gobj) == GCOMPOUND) {
        GCOMPOUND_APPLY(gobj, setWindow, gw);
    }
    setWindow(gobj, gw);
    addGCompound(gw->contents, gobj);
    draw(gw,gobj);
}

void addAt(GWindow gw, GObject gobj, double x, double y)
{
    setLocation(gobj, x, y);
    add(gw, gobj);
}

void removeGWindow(GWindow gw, GObject gobj)
{
    removeGCompound(gw->contents, gobj);
    repaint(gw);
}

GObject getGObjectAt(GWindow gw, double x, double y)
{
    return getGObjectCompound(gw->contents, x, y);
}

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
void pause_(double milliseconds)
{
    emscripten_sleep(milliseconds);
}
#else
void pause(double milliseconds)
{
    SDL_Delay(milliseconds);
}
#endif
