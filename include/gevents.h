/*
 * File: gevents.h
 * ---------------
 * This interface defines the event structure used in the graphics libraries.
 * The structure of this package is adapted from the Java event model and
 * is compatible with the C++ <code>StanfordCPPLib</code> package.
 * <include src="pictures/TypeHierarchies/GEventHierarchy.html">
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

#ifndef _gevents_h
#define _gevents_h

#include "cslib.h"
#include "generic.h"
#include "gwindow.h"
#include <SDL2/SDL_events.h>

/*
 * Type: EventClassType
 * --------------------
 * This enumeration type defines the event classes.  The element values
 * are each a single bit and can be added or ORed together to generate
 * an event mask.  The <code>CLICK_EVENT</code> class responds only to
 * the MOUSE_CLICKED event type.  The <code>ANY_EVENT</code> class
 * selects any event.
 */

typedef enum {
   KEY_EVENT    = 0x010,
   WINDOW_EVENT = 0x020,
   MOUSE_EVENT  = 0x040,
   CLICK_EVENT  = 0x080,
   ANY_EVENT    = 0x1F0,
} EventClassType;

/*
 * Type: EventType
 * ---------------
 * This enumeration type defines the event types for all events.
 */

typedef enum {
   WINDOW_CLOSED    = WINDOW_EVENT + 1,
   WINDOW_RESIZED   = WINDOW_EVENT + 2,
   MOUSE_CLICKED    = MOUSE_EVENT + 1,
   MOUSE_PRESSED    = MOUSE_EVENT + 2,
   MOUSE_RELEASED   = MOUSE_EVENT + 3,
   MOUSE_MOVED      = MOUSE_EVENT + 4,
   MOUSE_DRAGGED    = MOUSE_EVENT + 5,
   KEY_PRESSED      = KEY_EVENT + 1,
   KEY_RELEASED     = KEY_EVENT + 2,
   KEY_TYPED        = KEY_EVENT + 3,
} EventType;

/*
 * Type: ModifierCodes
 * -------------------
 * This enumeration type defines a set of constants used to check whether
 * modifiers are in effect.
 */

typedef enum {
   SHIFT_DOWN     = KMOD_SHIFT,
   CTRL_DOWN      = KMOD_CTRL,
   META_DOWN      = KMOD_GUI,
   ALT_DOWN       = KMOD_ALT,
} ModifierCodes;

/*
 * Type: KeyCodes
 * --------------
 * This type defines the names of the key codes returned in a key event.
 */

typedef enum {
   BACKSPACE_KEY = SDLK_BACKSPACE,
   TAB_KEY = SDLK_TAB,
   ENTER_KEY = SDLK_RETURN,
   CLEAR_KEY = SDLK_CLEAR,
   ESCAPE_KEY = SDLK_ESCAPE,
   PAGE_UP_KEY = SDLK_PAGEUP,
   PAGE_DOWN_KEY = SDLK_PAGEDOWN,
   END_KEY = SDLK_END,
   HOME_KEY = SDLK_HOME,
   LEFT_ARROW_KEY = SDLK_LEFT,
   UP_ARROW_KEY = SDLK_UP,
   RIGHT_ARROW_KEY = SDLK_RIGHT,
   DOWN_ARROW_KEY = SDLK_DOWN,
   F1_KEY = SDLK_F1,
   F2_KEY = SDLK_F2,
   F3_KEY = SDLK_F3,
   F4_KEY = SDLK_F4,
   F5_KEY = SDLK_F5,
   F6_KEY = SDLK_F6,
   F7_KEY = SDLK_F7,
   F8_KEY = SDLK_F8,
   F9_KEY = SDLK_F9,
   F10_KEY = SDLK_F10,
   F11_KEY = SDLK_F11,
   F12_KEY = SDLK_F12,
   DELETE_KEY = SDLK_DELETE,
   HELP_KEY = SDLK_HELP
} KeyCodes;

/*
 * Type: GEvent
 * ------------
 * This abstract type is used to represent an event of any type.  This
 * file defines names for the subtypes, even though these types are
 * identical in C.  The functions that apply only to a specific event
 * subtype generate runtime errors if called on an event of the wrong type.
 *
 * <p>The standard paradigm for using <code>GEvent</code> is illustrated
 * by the following program, which allows the user to draw lines on the
 * graphics window:
 *
 *<pre>
 *    main() {
 *       GWindow gw = newGWindow(600, 400);
 *       while (true) {
 *          GMouseEvent e = waitForEvent(MOUSE_EVENT);
 *          if (getEventType(e) == MOUSE_PRESSED) {
 *             GLine line = newGLine(getX(e), getY(e), getX(e), getY(e));
 *             add(gw, line);
 *          } else if (getEventType(e) == MOUSE_DRAGGED) {
 *             setEndPoint(line, getX(e), getY(e));
 *          }
 *       }
 *    }
 *</pre>
 */

typedef struct GEventCDT *GEvent;

/*
 * Function: freeEvent
 * Usage: freeEvent(e);
 * --------------------
 * Releases the storage associated with the event.
 */

void freeEvent(GEvent e);

/*
 * Function: getEventClass
 * Usage: eventClass = getEventClass(e);
 * -------------------------------------
 * Returns the enumerated type constant indicating the class of the event.
 */

EventClassType getEventClass(GEvent e);

/*
 * Function: getEventType
 * Usage: eventType = getEventType(e);
 * -----------------------------------
 * Returns the enumerated constant indicating the specific class of the event.
 */

EventType getEventType(GEvent e);

/*
 * Function: getGWindow
 * Usage: gw = getGWindow(e);
 * --------------------------
 * Returns the graphics window in which this event occurred.  This function
 * applies to the subtypes <code>GMouseEvent</code>, <code>GKeyEvent</code>,
 * and <code>GWindowEvent</code>.
 */

GWindow getGWindow(GEvent e);

/*
 * Function: getEventTime
 * Usage: time = getEventTime(e);
 * ------------------------------
 * Returns the system time in milliseconds at which the event occurred.
 * To ensure portability among systems that represent time in different
 * ways, the <code>cslib</code> package uses type <code>double</code> to
 * represent time, which is always encoded as the number of milliseconds
 * that have elapsed since 00:00:00 UTC on January 1, 1970, which is
 * the conventional zero point for computer-based time systems.
 */

double getEventTime(GEvent e);

/*
 * Function: setEventTime
 * Usage: setEventTime(e, time);
 * -----------------------------
 * Sets the event time field for the event.
 */

void setEventTime(GEvent e, double time);

/*
 * Function: getModifiers
 * Usage: modifiers = getModifiers(e);
 * -----------------------------------
 * Returns an integer whose bits indicate what modifiers are in effect.
 * To check whether the shift key is down, for example, clients can use
 * the following code:
 *
 *<pre>
 *    if (getModifiers(e) & SHIFT_DOWN) . . .
 *</pre>
 */

int getModifiers(GEvent e);

/*
 * Function: setModifiers
 * Usage: setModifiers(e, modifiers);
 * ----------------------------------
 * Sets the modifiers field for the event.
 */

void setModifiers(GEvent e, int modifiers);

/*
 * Function: waitForClick
 * Usage: waitForClick();
 * ----------------------
 * Waits for a mouse click to occur in any window, discarding any other
 * events.
 */

void waitForClick();

/*
 * Function: waitForEvent
 * Usage: e = waitForEvent(mask);
 * ------------------------------
 * Dismisses the process until an event occurs whose type is covered by
 * the event mask.  The mask parameter is a combination of the events of
 * interest.  For example, to wait for a mouse event or an action event,
 * clients can use the following call:
 *
 *<pre>
 *    e = waitForEvent(MOUSE_EVENT + ACTION_EVENT);
 *</pre>
 *
 * As a more sophisticated example, the following code is the canonical
 * event loop for an animated application that needs to respond to mouse,
 * key, and timer events:
 *
 *<pre>
 *    GTimer timer;
 *    GEvent e;
 *
 *    timer = newGTimer(ANIMATION_DELAY_IN_MILLISECONDS);
 *    start(timer);
 *    while (true) {
 *       e = waitForEvent(TIMER_EVENT + MOUSE_EVENT + KEY_EVENT);
 *       switch (getEventClass(e)) {
 *        case TIMER_EVENT:
 *          takeAnimationStep();
 *          break;
 *        case MOUSE_EVENT:
 *          handleMouseEvent(e);
 *          break;
 *        case KEY_EVENT:
 *          handleKeyEvent(e);
 *          break;
 *       }
 *       freeEvent(e);
 *    }
 *</pre>
 */

GEvent waitForEvent(int mask);

/*
 * Function: getNextEvent
 * Usage: e = getNextEvent(mask);
 * ------------------------------
 * Checks to see if there are any events of the desired type waiting on the
 * event queue.  If so, this function returns the event in exactly the same
 * fashion as <code>waitNextEvent</code>; if not, <code>getNextEvent</code>
 * returns <code>NULL</code>.
 */

GEvent getNextEvent(int mask);

/*
 * Type: GWindowEvent
 * ------------------
 * This event subtype represents a change in a window.
 */

typedef GEvent GWindowEvent;

/*
 * Function: newGWindowEvent
 * Usage: e = newGWindowEvent(type, gw);
 * -------------------------------------
 * Creates a new <code>GWindowEvent</code>.  The parameters are the
 * specific type of window event and the <code>GWindow</code> in which
 * the event occurred.
 */

GWindowEvent newGWindowEvent(EventType type, GWindow gw);

/*
 * Type: GMouseEvent
 * -----------------
 * This event subtype represents a mouse action in a window.
 */

typedef GEvent GMouseEvent;

/*
 * Function: newGMouseEvent
 * Usage: e = newGMouseEvent(type, gw, x, y);
 * ------------------------------------------
 * Creates a new <code>GMouseEvent</code>.  The parameters are the
 * specific event type, the <code>GWindow</code> in which the event
 * occurred, and the coordinates of the mouse.
 */

GMouseEvent newGMouseEvent(EventType type, GWindow gw, double x, double y);

/*
 * Function: getX
 * Usage: x = getX(e);
 * -------------------
 * Returns the <i>x</i> coordinate at which the event occurred.
 */

double getXGEvent(GMouseEvent e);

/*
 * Function: getY
 * Usage: y = getY(e);
 * -------------------
 * Returns the <i>y</i> coordinate at which the event occurred.
 */

double getYGEvent(GMouseEvent e);

/*
 * Type: GKeyEvent
 * ---------------
 * This event subtype represents a key action in a window.
 */

typedef GEvent GKeyEvent;

/*
 * Function: newGKeyEvent
 * Usage: e = newGKeyEvent(type, gw, ch, code);
 * --------------------------------------------
 * Creates a new <code>GKeyEvent</code>.  The parameters are the specific
 * event type, the <code>GWindow</code> in which the event occurred, the
 * character after taking into account modifier keys, and the code for the
 * specific key.
 */

GKeyEvent newGKeyEvent(EventType type, GWindow gw, int keyChar, int keyCode);

/*
 * Function: getKeyChar
 * Usage: ch = getKeyChar(e);
 * --------------------------
 * Returns the character represented by the keystroke, taking the modifier
 * keys into account.  For example, if the user types the <code>'a'</code>
 * key with the shift key down, <code>getKeyChar</code> will return
 * <code>'A'</code>.  If the key code in the event does not correspond
 * to a character, <code>getKeyChar</code> returns the null character.
 */

char getKeyChar(GKeyEvent e);

/*
 * Function: getKeyCode
 * Usage: key = getKeyCode(e);
 * ---------------------------
 * Returns the integer code associated with the key in the event.
 */

int getKeyCode(GKeyEvent e);

#endif
