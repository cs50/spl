/*
 * File: sound.h
 * -------------
 * This interface defines an abstract type that represents a sound.
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

#ifndef _sound_h
#define _sound_h

/*
 * Type: Sound
 * -----------
 * This type encapsulates a sound file.  The sound file is specified in the
 * constructor and must be a file in either the current directory or a
 * subdirectory named <code>sounds</code>.
 *
 * <p>The following code, for example, plays the sound file
 * <code>ringtone.wav</code>:
 *
 *<pre>
 *    Sound ringtone = newSound("ringtone.wav");
 *    play(ringtone);
 *</pre>
 */

typedef struct SoundCDT *Sound;

/*
 * Function: newSound
 * Usage: sound = newSound(filename);
 * ----------------------------------
 * Creates a <code>Sound</code> object from the specified file.
 */

Sound newSound(string filename);

/*
 * Function: freeSound
 * Usage: freeSound(sound);
 * ------------------------
 * Frees the memory associated with the sound.
 */

void freeSound(Sound sound);

/*
 * Function: play
 * Usage: play(sound);
 * -------------------
 * Starts playing the sound.  This call returns immediately without waiting
 * for the sound to finish.
 */

void play(Sound sound);

#endif
