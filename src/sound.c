/*
 * File: sound.c
 * -------------
 * This file implements the sound.h interface.
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
#include "cslib.h"
#include "platform.h"
#include "sound.h"

/*
 * Type SoundCDT
 * -------------
 * This type is the concrete type for sounds.
 */

struct SoundCDT {
   string filename;
};

Sound newSound(string filename) {
   Sound sound;

   sound = newBlock(Sound);
   sound->filename = filename;
   createSoundOp(sound, filename);
   return sound;
}

void freeSound(Sound sound) {
   deleteSoundOp(sound);
}

void playSound(Sound sound) {
   playSoundOp(sound);
}
