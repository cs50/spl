/*
 * File: gevents.c
 * ---------------
 * This file implements the machine-independent functions for the event
 * types defined in the gevents.h interface.  The actual functions for
 * receiving events from the environment are implemented in the platform
 * package.
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

#include "cslib.h"
#include "gevents.h"
#include "gtypes.h"
#include "private/helpers.h"
#include <limits.h>
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

/* Constants */

#define EVENT_SUBTYPE_MASK 0xF

/* Global variables */

/* Implementation of GEvent class */

typedef struct {
    uint32_t max;
    uint32_t min;
    int num_events;
} EventRange;

struct GEventCDT {
    int eventType;
    SDL_Event event;
};

static inline EventClassType getEventClassOp(int type)
{
    return type & ~EVENT_SUBTYPE_MASK;
}

EventClassType getEventClass(GEvent e)
{
    return getEventClassOp(e->eventType);
}

EventType getEventType(GEvent e)
{
    return e->eventType;
}

double getEventTime(GEvent e)
{
    return e->event.common.timestamp;
}

int getModifiers(GEvent e)
{
    if (!(e->eventType & KEY_EVENT)) {
        error("getKeyChar: Illegal event type");
    }

    return e->event.key.keysym.mod;
}

void waitForClick()
{
    freeEvent(waitForEvent(CLICK_EVENT));
}


static bool is_wrapper(int ch, int (*is_fn)(int))
{
    return ch >= 0 && ch < UCHAR_MAX && is_fn(ch);
}

static bool isValidKey(SDL_Event const *e)
{
    int ch = e->key.keysym.sym;
    switch (ch)
    {
    case SDLK_BACKSPACE:
    case SDLK_TAB:
    case SDLK_RETURN:
    case SDLK_CLEAR:
    case SDLK_ESCAPE:
    case SDLK_PAGEUP:
    case SDLK_PAGEDOWN:
    case SDLK_END:
    case SDLK_HOME:
    case SDLK_LEFT:
    case SDLK_RIGHT:
    case SDLK_UP:
    case SDLK_DOWN:
    case SDLK_F1:
    case SDLK_F2:
    case SDLK_F3:
    case SDLK_F4:
    case SDLK_F5:
    case SDLK_F6:
    case SDLK_F7:
    case SDLK_F8:
    case SDLK_F9:
    case SDLK_F10:
    case SDLK_F11:
    case SDLK_F12:
    case SDLK_DELETE:
    case SDLK_HELP:
        return true;
    default:
        return is_wrapper(e->key.keysym.sym, isprint);
    }
}

typedef enum {
    Disabled,
    Press,
    Release,
} ButtonState;

// TODO: support more events
static int mapSDLType(SDL_Event const *e, ButtonState *click, ButtonState *key)
{
    switch (e->type) {
    case SDL_WINDOWEVENT:
        switch (e->window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            return WINDOW_CLOSED;
        case SDL_WINDOWEVENT_RESIZED:
            return WINDOW_RESIZED;
        default:
            return -1;
        }
    case SDL_KEYDOWN:
        if (!isValidKey(e)) return -1;
        if (*key == Press) *key = Release;
        return KEY_PRESSED;
    case SDL_KEYUP:
        if (!isValidKey(e)) return -1;
        return *key == Release ? KEY_TYPED : KEY_RELEASED;
    case SDL_MOUSEMOTION:
        if (e->motion.state & SDL_BUTTON_LMASK) return MOUSE_DRAGGED;
        else return MOUSE_MOVED;
    case SDL_MOUSEBUTTONDOWN:
        if (e->button.button == SDL_BUTTON_LEFT) {
            if (*click == Press) *click = Release;
            return MOUSE_PRESSED;
        } else return -1;
    case SDL_MOUSEBUTTONUP:
        if (e->button.button == SDL_BUTTON_LEFT) return *click == Release ? CLICK_EVENT : MOUSE_RELEASED;
        else return -1;
    case SDL_QUIT:
        exit(0);
    default:
        return -1;
    }

}

static int eventFilter(void *user_data, SDL_Event *e)
{
    (void) user_data;
    // Not really necessary, but required by mapSDLType
    ButtonState c = Disabled, k = Disabled;
    return mapSDLType(e, &c, &k) != -1;
}

static void setFilter(SDL_EventFilter new_filter)
{
    static bool filter_set = false;
    if (!filter_set) {
        SDL_SetEventFilter(new_filter, NULL);
        filter_set = true;
    }
}


static inline bool has_click(int mask)
{
    return mask & CLICK_EVENT && SDL_HasEvent(SDL_MOUSEBUTTONDOWN) && SDL_HasEvent(SDL_MOUSEBUTTONUP);
}

static inline bool has_win(int mask)
{
    return mask & WINDOW_EVENT && SDL_HasEvent(SDL_WINDOWEVENT);
}

static inline bool has_mouse(int mask)
{
    return mask & MOUSE_EVENT && SDL_HasEvents(SDL_MOUSEMOTION, SDL_MOUSEBUTTONUP);
}

static inline bool has_key(int mask)
{
    return mask & KEY_EVENT && SDL_HasEvents(SDL_KEYDOWN, SDL_KEYUP);
}

static inline bool has_event(int mask)
{
    SDL_PumpEvents();
    return has_click(mask) || has_win(mask) || has_mouse(mask) || has_key(mask);
}

static GEvent eventAction(int mask, int (*ev_fn)(SDL_Event*))
{
    requiresSubsystem(SDL_INIT_EVENTS);
    setFilter(eventFilter);

    // The mask can either be a composite of event classes or a single event
    // type. Determine which we are and error if we're both
    bool composite = true;
    if (mask & EVENT_SUBTYPE_MASK) { 
        composite = false;
        if (__builtin_popcount(getEventClassOp(mask)) > 1) {
            error("GEvents: Mask must either be the sum of event classes or a single event type");
        }
    }

    ButtonState click = mask & CLICK_EVENT ? Press : Disabled,
                key = mask & KEY_PRESSED ? Press : Disabled;

    GEvent ret = NULL;
    SDL_Event e;
    while (ev_fn(&e)) {
        int type = mapSDLType(&e, &click, &key);
        if (type != -1 && ((composite && type & mask) || type == mask)) {
            ret = newBlock(GEvent);
            // Compensate for the fact that MOUSE_CLICKED is not in the
            // CLICK_EVENT class because reasons
            ret->eventType = type == CLICK_EVENT ? MOUSE_CLICKED : type;
            ret->event = e;
            break;
        }

    }
    return ret;
}

GEvent waitForEvent(int mask)
{
// TODO: Figure out how to get eventAction to work with SDL_WaitEvent so this
// doesn't happen
#ifdef __EMSCRIPTEN__
    for (;;) {
        GEvent e = getNextEvent(mask);
        if (e) return e;
    }
#endif
    return eventAction(mask, SDL_WaitEvent);
}


GEvent getNextEvent(int mask)
{
    GEvent e = has_event(mask) ? eventAction(mask, SDL_PollEvent) : NULL;
    if (!e) pause(1);
    return e;
}

void freeEvent(GEvent e)
{
    freeBlock(e);
}

GWindow getGWindow(GEvent e)
{
    error("getGWindow: unimplemeted");
}

double getXGEvent(GEvent e)
{
    switch (e->event.type) {
    case SDL_MOUSEMOTION:
        return e->event.motion.x;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        return e->event.button.x;
    }
    error("getX: Illegal event type");
}

double getYGEvent(GEvent e)
{
    switch (e->event.type) {
    case SDL_MOUSEMOTION:
        return e->event.motion.y;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        return e->event.button.y;
    }
    error("getY: Illegal event type");
}

int getKeyCode(GEvent e)
{
    if (!(e->eventType & KEY_EVENT)) {
        error("getKeyCode: Illegal event type");
    }

    return e->event.key.keysym.sym;

}

char getKeyChar(GEvent e)
{
    if (!(e->eventType & KEY_EVENT)) {
        error("getKeyChar: Illegal event type");
    }
    int c = getKeyCode(e);
    return is_wrapper(c, isprint)
        ? getModifiers(e) & SHIFT_DOWN
            ? toupper(c)
            : c
        : '\0';
}
