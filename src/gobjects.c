#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
/*
 * File: gobjects.c
 * ----------------
 * This file implements both the gobjects.h and ginteractors.h interfaces.
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

#include "generic.h"
#include "gmath.h"
#include "gobjects.h"
#include "gwindow.h"
#include "color.h"
#include "private/sdl_helpers.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include <SDL_ttf.h>

/* Constants */

#define LINE_TOLERANCE 1.5
#define ARC_TOLERANCE 2.5
#define DEFAULT_CORNER 10

/*
 * Type: GArcCDT
 * -------------
 * This type holds the extra information needed for a GArc.
 */

struct GArcCDT {
    double start;
    double sweep;
};

/*
 * Type: GLabelCDT
 * ---------------
 * This type holds the extra information needed for a GLabel.
 */

struct GLabelCDT {
    TTF_Font *font;
    char *str;
};

/*
 * Type: GPolygonCDT
 * -----------------
 * This type holds the extra information needed for a GPolygon.
 */

struct GPolygonCDT {
    Vector vertices;
    double cx;
    double cy;
};

/*
 * Type: GCompoundCDT
 * ------------------
 * This type holds the extra information needed for a GCompound.
 */

struct GCompoundCDT {
    Vector contents;
};

/*
 * Type: G3DRectCDT
 * ----------------
 * This type holds the extra information needed for a G3DRect.
 */

struct G3DRectCDT {
    bool raised;
};

struct GInteractorCDT {
    char *actionCommand;
    char *label;
};

struct GRoundRectCDT {
    double corner;
};


/*
 * Type: GObjectCDT
 * ----------------
 * This structure is the common concrete type for all GObjects.
 */

struct GObjectCDT {
    union {
        struct GArcCDT arcRep;
        struct GLabelCDT labelRep;
        struct G3DRectCDT g3dRectRep;
        struct GPolygonCDT polygonRep;
        struct GCompoundCDT compoundRep;
        struct GRoundRectCDT roundRectRep;
    };
    GObject parent;
    GWindow win;
    double x;
    double y;
    double width;
    double height;
    int type;
    Color color;
    Color fillColor;
};

/* Prototypes that are sometimes missing from math.h */

double fmin(double x, double y);
double fmax(double x, double y);

/* Private function prototypes */

static GRectangle getBoundsGLine(GLine line);
static GRectangle getBoundsGLabel(GLabel label);
static GRectangle getBoundsGArc(GArc arc);
static GRectangle getBoundsGPolygon(GPolygon poly);

static bool containsGOval(GOval oval, double x, double y);
static bool containsGLine(GLine line, double x, double y);
static bool containsGArc(GArc arc, double x, double y);
static bool containsGPolygon(GArc arc, double x, double y);

static bool containsAngle(GArc arc, double theta);
static double dsq(double x0, double y0, double x1, double y1);

Vector getGCompoundContents(GCompound compound);
static void recalcCompDimension(GObject restrict compound);

static inline void repaintObj(GObject gobj) {
    if (gobj->win) repaint(gobj->win);
}

/* GObject operations */

static GObject newGObject(int type) {
    GObject gobj = newBlock(GObject);
    gobj->type = type;
    gobj->x = 0;
    gobj->y = 0;
    gobj->width = 0;
    gobj->height = 0;
    gobj->color.full = BLACK;
    gobj->fillColor.full = 0;
    gobj->parent = NULL;
    gobj->win = NULL;
    return gobj;
}

void freeGObject(GObject gobj) {
    if (gobj->type == GPOLYGON) {
        Vector v = gobj->polygonRep.vertices;
        int n = sizeVector(v);
        for (int i = 0; i < n; i++) {
            freeBlock(getVector(v,i));
        }
        freeVector(v);
    } else if (gobj->type == GCOMPOUND) {
        freeVector(gobj->compoundRep.contents);
    }
    
    freeBlock(gobj);
}

double getXGObject(GObject gobj) {
    return gobj->x;
}

double getYGObject(GObject gobj) {
    return gobj->y;
}

GPoint getLocation(GObject gobj) {
    return createGPoint(gobj->x, gobj->y);
}

static inline void setLocationOp(GObject gobj, double x, double y) {
    if (gobj->type == GCOMPOUND) {
        GCOMPOUND_APPLY(gobj, setLocationOp, x, y);
        recalcCompDimension(gobj);
    } else {
        gobj->x = x;
        gobj->y = y;
    }
}
void setLocation(GObject gobj, double x, double y) {
    if (gobj->type != GCOMPOUND && round(gobj->x) == round(x) && round(gobj->y) == round(y))
        return;
    setLocationOp(gobj, x, y);
    repaintObj(gobj);
}

void setWindow(GObject gobj, GWindow win) {
    gobj->win = win;
}

void move(GObject gobj, double dx, double dy) {
    setLocation(gobj, gobj->x + dx, gobj->y + dy);
}

double getWidthGObject(GObject gobj) {
    return getBounds(gobj).width;
}

double getHeightGObject(GObject gobj) {
    return getBounds(gobj).height;
}

GDimension getSize(GObject gobj) {
    GRectangle bounds = getBounds(gobj);
    return createGDimension(bounds.width, bounds.height);
}

GRectangle getBounds(GObject gobj) {
    switch (gobj->type) {
    case GARC:     return getBoundsGArc(gobj);
    case GLINE:    return getBoundsGLine(gobj);
    case GLABEL:   return getBoundsGLabel(gobj);
    case GPOLYGON: return getBoundsGPolygon(gobj);
    default:       return createGRectangle(gobj->x, gobj->y, gobj->width, gobj->height);
    }
}

static inline void setColorGObjectOp(GObject gobj, Color col) {
    if (gobj->type == GCOMPOUND)
        GCOMPOUND_APPLY(gobj, setColorGObjectOp, col);
    
    col.a = gobj->color.a;
    gobj->color = col;
}
void setColorGObject(GObject gobj, Color col) {
    col.a = gobj->color.a;
    if (col.full == gobj->color.full)
        return;
    setColorGObjectOp(gobj, col);
    repaintObj(gobj);
}

string getColorGObject(GObject gobj) {
    return (string) mapColorString(gobj->color);
}

static inline void setVisibleGObjectOp(GObject gobj, bool flag) {
    if(gobj->type == GCOMPOUND)
        GCOMPOUND_APPLY(gobj, setVisibleGObjectOp, flag);
    gobj->color.a = flag ? 255 : 0;
}

void setVisibleGObject(GObject gobj, bool flag) {
    if (gobj->type != GCOMPOUND && isVisibleGObject(gobj) == flag) return;
    setVisibleGObjectOp(gobj, flag);
    repaintObj(gobj);
}


bool isVisibleGObject(GObject gobj) {
    return gobj->color.a != 0;
}

static inline void sendGObject(GObject gobj, void (*send)(Vector, int)) {
    if (!gobj->parent) return;
    Vector gobjs = getGCompoundContents(gobj->parent);
    int index = -1;
    for (int i = sizeVector(gobjs)-1; i >=  0; i--) {
        GObject g = getVector(gobjs,i); 
        if (g == gobj) {
            index = i;
            break;
        }
    }
    send(gobjs, index);
    repaintObj(gobj);
}

void sendBackward(GObject gobj) {
    sendGObject(gobj, sendBackwardVector);
}

void sendToBack(GObject gobj) {
    sendGObject(gobj, sendToBackVector);
}

void sendForward(GObject gobj) {
    sendGObject(gobj, sendForwardVector);
}

void sendToFront(GObject gobj) {
    sendGObject(gobj, sendToFrontVector);
}

bool containsGObject(GObject gobj, double x, double y) {
    switch (gobj->type) {
    case GOVAL:    return containsGOval(gobj,x,y);
    case GARC:     return containsGArc(gobj,x,y);
    case GPOLYGON: return containsGPolygon(gobj,x,y);
    default:       return x >= gobj->x && y >= gobj->y && x <= gobj->x + gobj->width
                          && y <= gobj->y + gobj->height;
    }
}

Color getRealGObjectColor(GObject gobj) {
    return gobj->color;
}

Color getRealGObjectFillColor(GObject gobj) {
    return gobj->fillColor;
}

int getRealType(GObject gobj) {
    return gobj->type;
}

string getType(GObject gobj) {
    switch (gobj->type) {
        case GARC: return "GArc";
        case GCOMPOUND: return "GCompound";
        case GIMAGE: return "GImage";
        case GLABEL: return "GLabel";
        case GLINE: return "GLine";
        case GOVAL: return "GOval";
        case GPOLYGON: return "GPolygon";
        case GRECT: return "GRect";
        case G3DRECT: return "G3DRect";
        case GROUNDRECT: return "GRoundRect";
        default: error("Attempting to call getType on an object with unexpected type");
    }
}

GObject getParent(GObject gobj) {
    return gobj->parent;
}

static inline void setSizeOp(GObject gobj, double width, double height) {
    if (gobj->type == GCOMPOUND) {
        GCOMPOUND_APPLY(gobj, setSizeOp, width, height);
        recalcCompDimension(gobj);
    } else if ((gobj->type & (GRECT | GOVAL | GIMAGE )) == 0) {
        error("setSize: Illegal GObject type");
    } else {
        gobj->width = width;
        gobj->height = height;
    }
    
}

void setSize(GObject gobj, double width, double height) {
    if (gobj->type != GCOMPOUND 
            && round(gobj->width) == round(width) 
            && round(gobj->height) == round(gobj->height))
        return;
    setSizeOp(gobj, width, height);
    repaintObj(gobj);
}


void setBounds(GObject gobj, double x, double y, double width, double height) {
    setSizeOp(gobj, width, height);
    setLocationOp(gobj, x, y);
    repaintObj(gobj);
}


static inline void setFilledOp(GObject gobj, bool flag) {
    if (gobj->type == GCOMPOUND) 
        GCOMPOUND_APPLY(gobj, setFilledOp, flag);
    else if ((gobj->type & (G3DRECT | GARC | GOVAL | GPOLYGON | GRECT | GROUNDRECT)) == 0)
        error("setFilled: Illegal GObject type");

    gobj->fillColor.a = flag ? 255 : 0;
}
void setFilled(GObject gobj, bool flag) {
    if (gobj->type != GCOMPOUND && flag == isFilled(gobj))
        return;
    setFilledOp(gobj, flag);
    repaintObj(gobj);
}

bool isFilled(GObject gobj) {
    return gobj->fillColor.a != 0;
}

static inline void setFillColorOp(GObject gobj, Color c) {
    if (gobj->type == GCOMPOUND)
        GCOMPOUND_APPLY(gobj, setFillColorOp, c);
    c.a = gobj->fillColor.a;
    gobj->fillColor = c;

}
void setFillColor(GObject gobj, string color) {
    Color c = {.full = 0};
    assert(mapStringColor(color, &c));

    if (gobj->type != GCOMPOUND && gobj->fillColor.full == c.full) {
        return;
    }

    c.a = gobj->fillColor.a;
    if (c.full == gobj->fillColor.full) return;

    gobj->fillColor.full = c.full;
    repaintObj(gobj);
}

string getFillColor(GObject gobj) {
    return (string) mapColorString(gobj->fillColor);
}

/*
 * Implementation notes: GRect
 * ---------------------------
 * This section of the implementation includes the subclasses.
 */

GRect newGRect(double x, double y, double width, double height) {
    GObject rect = newGObject(GRECT);
    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
    return rect;
}

GRoundRect newGRoundRect(double x, double y, double width, double height,
        double corner) {
    GObject rect = newGObject(GROUNDRECT);
    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
    rect->roundRectRep.corner = corner;
    return rect;
}

G3DRect newG3DRect(double x, double y, double width, double height,
        bool raised) {
    GObject rect = newGObject(G3DRECT);
    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
    rect->g3dRectRep.raised = raised;
    return rect;
}

void setRaised(G3DRect rect, bool raised) {
    if (isRaised(rect) == raised) return;
    rect->g3dRectRep.raised = raised;
    repaintObj(rect);
}

bool isRaised(G3DRect rect) {
    return rect->g3dRectRep.raised;
}

/*
 * Implementation notes: GOval
 * ---------------------------
 * The GOval class requires only the constructor.
 */

GOval newGOval(double x, double y, double width, double height) {
    GOval oval = newGObject(GOVAL);
    oval->x = x;
    oval->y = y;
    oval->width = width;
    oval->height = height;
    return oval;
}

static bool containsGOval(GOval oval, double x, double y) {
    double rx = oval->width / 2,
           ry = oval->height / 2;
    if (rx == 0 || ry == 0) return false;

    double dx = x - (oval->x + rx),
           dy = y - (oval->y + ry);

    return (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1.0;
}

/*
 * Implementation notes: GLine
 * ---------------------------
 * The GLine type uses the width and height fields to specify the
 * displacement from the start point to the end point.  These values
 * may be negative.  This type also includes functions to set the
 * start and end points.
 */

GLine newGLine(double x0, double y0, double x1, double y1) {
    GLine line = newGObject(GLINE);
    line->x = x0;
    line->y = y0;
    line->width = x1 - x0;
    line->height = y1 - y0;
    return line;
}

void setStartPoint(GLine line, double x, double y) {
    if (line->type != GLINE) error("setStartPoint: Illegal argument type");
    if (round(line->x) == round(x) && round(line->y) == round(y)) return;
    line->width += line->x - x;
    line->height += line->y - y;
    line->x = x;
    line->y = y;
    repaintObj(line);
}

void setEndPoint(GObject line, double x, double y) {
    if (line->type != GLINE) error("setStartPoint: Illegal argument type");
    double nWidth  = x - line->x,
           nHeight = y - line->y;
    if (round(nWidth) == round(line->width) && round(nHeight) == round(nHeight)) return;
    line->width = nWidth;
    line->height = nHeight;
    repaintObj(line);
}

GPoint getStartPoint(GObject gobj) {
    if (gobj->type != GLINE) {
        return createGPoint(gobj->x, gobj->y);
    }
    error("getStartPoint: Illegal argument type");
}

GPoint getEndPoint(GObject gobj) {
    if (gobj->type != GLINE) {
        return createGPoint(gobj->x + gobj->width, gobj->y + gobj->height);
    }
    error("getEndPoint: Illegal argument type");
}

static GRectangle getBoundsGLine(GLine line) {
    return createGRectangle(fmin(line->x, line->x + line->width),
            fmin(line->x, line->x + line->width),
            fabs(line->width), fabs(line->height));
}

static bool containsGLine(GLine line, double x, double y) {
    double x0 = line->x,
           y0 = line->y,
           tsq = LINE_TOLERANCE * LINE_TOLERANCE;
    if (dsq(x, y, x0, y0) < tsq) return true;

    double x1 = x0 + line->width,
           y1 = y0 + line->height;
    if (dsq(x, y, x1, y1) < tsq) return true;
    if (x < fmin(x0, x1) - LINE_TOLERANCE) return false;
    if (x > fmax(x0, x1) + LINE_TOLERANCE) return false;
    if (y < fmin(y0, y1) - LINE_TOLERANCE) return false;
    if (y > fmax(y0, y1) + LINE_TOLERANCE) return false;
    if ((float) (x0 - x1) == 0 && (float) (y0 - y1) == 0) return false;
    double u = ((x - x0) * (x1 - x0) + (y - y0) * (y1 - y0)) / dsq(x0, y0, x1, y1);
    return dsq(x, y, x0 + u * (x1 - x0), y0 + u * (y1 - y0)) < tsq;
}

/*
 * Implementation notes: GArc
 * --------------------------
 * Parts of the GArc implementation appear in the general GObject code
 * because the functions are often overloaded.
 */

GArc newGArc(double x, double y, double width, double height,
        double start, double sweep) {
    GObject arc = newGObject(GARC);
    arc->x = x;
    arc->y = y;
    arc->width = width;
    arc->height = height;
    arc->arcRep.start = start;
    arc->arcRep.sweep = sweep;
    return arc;
}

void setStartAngle(GArc arc, double start) {
    if (getStartAngle(arc) == start) return;
    arc->arcRep.start = start;
    repaintObj(arc);
}

double getStartAngle(GArc arc) {
    return arc->arcRep.start;
}

void setSweepAngle(GArc arc, double sweep) {
    if (getSweepAngle(arc) != sweep) return;
    arc->arcRep.sweep = sweep;
    repaintObj(arc);
}

double getSweepAngle(GArc arc) {
    return arc->arcRep.sweep;
}

void setFrameRectangle(GArc arc, double x, double y,
        double width, double height) {
    if (arc->x == x && arc->y == y && arc->width == width && arc->height == height) return;
    arc->x = x;
    arc->y = y;
    arc->width = width;
    arc->height = height;
    repaintObj(arc);
}

GRectangle getFrameRectangle(GArc arc) {
    return createGRectangle(arc->x, arc->y, arc->width, arc->height);
}

static GRectangle getBoundsGArc(GArc arc) {

    double rx = arc->width / 2,
           ry = arc->height / 2,
           cx = arc->x + rx,
           cy = arc->y + ry,
           p1x = cx + cosDegrees(arc->arcRep.start) * rx,
           p1y = cy - sinDegrees(arc->arcRep.start) * ry,
           p2x = cx + cosDegrees(arc->arcRep.start + arc->arcRep.sweep) * rx,
           p2y = cy - sinDegrees(arc->arcRep.start + arc->arcRep.sweep) * ry,
           xMin = fmin(p1x, p2x),
           xMax = fmax(p1x, p2x),
           yMin = fmin(p1y, p2y),
           yMax = fmax(p1y, p2y);

    if (containsAngle(arc, 0)) xMax = cx + rx;
    if (containsAngle(arc, 90)) yMin = cy - ry;
    if (containsAngle(arc, 180)) xMin = cx - rx;
    if (containsAngle(arc, 270)) yMax = cy + ry;
    if (isFilled(arc)) {
        xMin = fmin(xMin, cx);
        yMin = fmin(yMin, cy);
        xMax = fmax(xMax, cx);
        yMax = fmax(yMax, cy);
    }
    return createGRectangle(xMin, yMin, xMax - xMin, yMax - yMin);
}

static bool containsGArc(GArc arc, double x, double y) {
    double rx = arc->width / 2,
           ry = arc->height / 2;
    if (rx == 0 || ry == 0) return false;
    double dx = x - (arc->x + rx),
           dy = y - (arc->y + ry);
    double r = (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry);
    if (isFilled(arc)) {
        if (r > 1.0) return false;
    } else {
        double t = ARC_TOLERANCE / ((rx + ry) / 2);
        if (fabs(1.0 - r) > t) return false;
    }
    return containsAngle(arc, atan2(-dy, dx) * 180 / PI);
}

static bool containsAngle(GArc arc, double theta) {
    double start, sweep;

    start = fmin(arc->arcRep.start,
            arc->arcRep.start + arc->arcRep.sweep);
    sweep = fabs(arc->arcRep.sweep);
    if (sweep >= 360) return true;
    theta = (theta < 0) ? 360 - fmod(-theta, 360) : fmod(theta, 360);
    start = (start < 0) ? 360 - fmod(-start, 360) : fmod(start, 360);
    if (start + sweep > 360) {
        return theta >= start || theta <= start + sweep - 360;
    } else {
        return theta >= start && theta <= start + sweep;
    }
}

/*
 * Implementation notes: GLabel
 * ----------------------------
 */

#define FONTS_DIR "assets/"
#define DEFAULT_FONT "arial-12"

typedef struct {
    char *path;
    int size;
    int opts;
} FontInfo;

static inline FontInfo parseFont(string str) {
    FontInfo f = {};
    string s = strchrnul(str, '-');
    assert(s != str);
    assert(asprintf(&f.path, "%s%.*s.ttf", FONTS_DIR, (int) (s - str), str) != -1);
    if (!s++) return f;

    char *style = NULL;
    f.size = strtol(s, &style, 10);
    if (!*style++) return f;
    bool stop = false;
    while (!stop) { 
        switch (*style++) {
        case 'b' : f.opts |= TTF_STYLE_BOLD;            break;
        case 'i' : f.opts |= TTF_STYLE_ITALIC;          break;
        case 'u' : f.opts |= TTF_STYLE_UNDERLINE;       break;
        case 's' : f.opts |= TTF_STYLE_STRIKETHROUGH;   break;
        case '\0': stop = true;                         break;
        default  : assert(false);
        }
    }
    return f;
}

static inline void freeFontInfo(FontInfo *f) {
    free(f->path);
    *f = (FontInfo) {};

}

static inline void updateLabelSize(GLabel label) {
    int h,w;
    assert(TTF_SizeText(label->labelRep.font, label->labelRep.str, &w, &h) != -1);
    label->height = h;
    label->width = w;
}


GLabel newGLabel(char *str) {
    requiresFonts();
    GObject label = newGObject(GLABEL);
    label->labelRep.str = strdup(str);
    setFont(label, DEFAULT_FONT);
    return label;
}

void setFont(GLabel label, string font) {
    FontInfo info = parseFont(font);
    label->labelRep.font = TTF_OpenFont(info.path, info.size ? info.size : 12);
    freeFontInfo(&info);

    assert(label->labelRep.font);
    updateLabelSize(label);
    repaintObj(label);
}

TTF_Font *getRealFont(GLabel label) {
    return label->labelRep.font;
}

string getFont(GLabel label) {
    return label->labelRep.font ? TTF_FontFaceFamilyName(label->labelRep.font) : NULL;
}

void setLabel(GLabel label, char *str) {
    free(label->labelRep.str);
    label->labelRep.str = strdup(str);
    updateLabelSize(label);
    repaintObj(label);
}


char *getLabel(GLabel label) {
    return label->labelRep.str;
}

double getFontAscent(GLabel label) {
    return TTF_FontAscent(label->labelRep.font);
}

double getFontDescent(GLabel label) {
    return TTF_FontDescent(label->labelRep.font);
}

static GRectangle getBoundsGLabel(GLabel label) {
    return createGRectangle(label->x, label->y - getFontAscent(label),
            label->width, label->height);
}

/*
GImage newGImage(char *filename) {
    GPolygon image;
    GDimension size;

    image = newGObject(GIMAGE);
    size = createGImageOp(image, filename);
    image->width = size.width;
    image->height = size.height;
    return image;
}
*/

GPolygon newGPolygon(void) {
    GPolygon poly = newGObject(GPOLYGON);
    poly->polygonRep.vertices = newVector();
    poly->polygonRep.cx = NAN;
    poly->polygonRep.cy = NAN;
    return poly;
}

GPoint getCenterPolygon(GPolygon poly) {
    return createGPoint(poly->polygonRep.cx, poly->polygonRep.cy);
}

static void addVertexOp(GPolygon poly, double x, double y) {
    GPoint *p = newBlock(GPoint *);
    Vector verts = getVertices(poly);
    int numVert = sizeVector(verts);
    poly->polygonRep.cx = (poly->polygonRep.cx * numVert + x) / (numVert + 1);
    poly->polygonRep.cy = (poly->polygonRep.cy * numVert + y) / (numVert + 1);
    p->x = x;
    p->y = y;
    addVector(verts, p);
}

void addVertex(GPolygon poly, double x, double y) {
    addVertexOp(poly, x, y);
    repaintObj(poly);
}

static inline void addEdgeOp(GPolygon poly, double dx, double dy) {
    Vector verts = getVertices(poly);
    GPoint *last = getVector(verts, sizeVector(verts)-1);
    addVertexOp(poly, last->x + dx, last->y + dy);
}

void addEdge(GPolygon poly, double dx, double dy) {
    addEdgeOp(poly,dx,dy);
    repaintObj(poly);
}

void addPolarEdge(GPolygon poly, double r, double theta) {
    addEdgeOp(poly, r * cosDegrees(theta), -r * sinDegrees(theta));
    repaintObj(poly);
}

Vector getVertices(GPolygon poly) {
    return poly->polygonRep.vertices;
}

static GRectangle getBoundsGPolygon(GPolygon poly) {
    double xMin = 0,
           xMax = 0,
           yMin = 0,
           yMax = 0;

    Vector v = poly->polygonRep.vertices;
    int n = sizeVector(v);
    for (int i = 0; i < n; i++) {
        GPoint *ps = getVector(v, i);
        if (i == 0 || ps->x < xMin) xMin = ps->x;
        if (i == 0 || ps->y < yMin) yMin = ps->y;
        if (i == 0 || ps->x > xMax) xMax = ps->x;
        if (i == 0 || ps->y > yMax) yMax = ps->y;
    }
    return createGRectangle(xMin, yMin, xMax - xMin, yMax - yMin);
}

static bool containsGPolygon(GPolygon poly, double x, double y) {
    Vector v = poly->polygonRep.vertices;
    size_t n = sizeVector(v);
    if (n < 2) return false;

    GPoint *p0 = getVector(v,0);
    double x0 = p0->x,
           y0 = p0->y;

    GPoint *p1 = getVector(v, n-1);
    if (p0->x == p1->x && p0->y == p1->y) n--;

    size_t crossings = 0;
    for (size_t i = 1; i <= n; i++) {
        p1 = getVector(v, i % n);
        double x1 = p1->x,
               y1 = p1->y;
        if ((y0 > y) != (y1 > y) && x - x0 < (x1 - x0) * (y - y0) / (y1 - y0)) {
            crossings++;
        }
        x0 = x1;
        y0 = y1;
    }
    return crossings & 1;
}

/*
 * Implementation notes: GCompound
 * -------------------------------
 * The GCompound type stores the individual components in a vector
 * that runs from back to front in the z direction.
 */

#define GCOMP_INIT_CAP 8
GCompound newGCompound(void) {
    GCompound gcompound = newGObject(GCOMPOUND);
    gcompound->compoundRep.contents = newVector();
    return gcompound;
}


static void addCompDimension(GObject restrict gobj, GObject restrict compound) {
    if (!compound->width) {
        compound->x = gobj->x;
        compound->width = gobj->x;
    } else if (gobj->x < compound->x) {
        compound->width += compound->x - gobj->x;
        compound->x = gobj->x;
    } else if (gobj->x + gobj->width > compound->x + compound->width) {
        compound->width = gobj->x + gobj->width - compound->x;
    }

    if (!compound->height) {
        compound->y = gobj->y;
        compound->height = gobj->height;
    } else if (gobj->y > compound->y) {
        compound->height += gobj->y - compound->y;
    } else if (gobj->y - gobj->height < compound->y - compound->height) {
        compound->height = compound->y - gobj->y + gobj->height;
    }
}

// TODO: Don't loop through vector if not necessary
static void recalcCompDimension(GObject restrict compound) {
    compound->x = compound->y = compound->width = compound->height = 0;
    GCOMPOUND_APPLY(compound, addCompDimension, compound);
}

void addGCompound(GObject compound, GObject gobj) {
    if (compound->type != GCOMPOUND) {
        error("add: First argument is not a GCompound");
    }
    if (gobj->win != compound->win) error("Adding objects to multiple windows not supported");
    gobj->win = compound->win;
    gobj->parent = compound;
    addCompDimension(gobj, compound);
    addVector(compound->compoundRep.contents, gobj);
}

void removeGCompound(GCompound compound, GObject gobj) {
    if (compound->type != GCOMPOUND) {
        error("remove: First argument is not a GCompound");
    }

    Vector v = compound->compoundRep.contents;
    int n = sizeVector(v);
    for (int i = 0; i < n; i++) {
        GObject g = getVector(v,i);
        if (g == gobj) {
            removeVector(v,i);
            recalcCompDimension(compound);
            break;
        }
    }
}

Vector getGCompoundContents(GCompound compound) {
    return compound->compoundRep.contents;
}

GObject getGObjectCompound(GCompound compound, double x, double y) {

    Vector v = compound->compoundRep.contents;
    int n = sizeVector(v);
    for (int i = 0; i < n; i++) {
        GObject g = getVector(v,i);
        if (containsGObject(g, x, y)) return g;
    }
    return NULL;
}


static double dsq(double x0, double y0, double x1, double y1) {
    return (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
}

