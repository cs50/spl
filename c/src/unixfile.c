/*
 * File: unixfile.c
 * ----------------
 * Implements the filelib.h interface for unix or unix-like systems
 * (including Mac OS X running standalone applications).  The entire
 * file compiles only on such systems and is empty on other platforms.
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

#if defined(__unix__) || defined(__STDC_HOSTED__)

#ifdef __macosx__
#include <CoreServices/CoreServices.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "cslib.h"
#include "filelib.h"
#include "strlib.h"
#include "vector.h"

static string SKIP_FILES[] = {
   ".",
   "..",
   ".DS_Store",
   NULL
};

static int alphaCompare(const void *p1, const void *p2) {
   return strcmp(*(string *) p1, *(string *) p2);
}

string getDirectoryPathSeparator(void) {
   return "/";
}

string getSearchPathSeparator(void) {
   return ":";
}

bool fileExists(string path) {
   struct stat sblk;
   return stat(path, &sblk) == 0;
}

bool isFile(string path) {
   struct stat sblk;
   if (lstat(path, &sblk) != 0) return false;
   return (sblk.st_mode & S_IFMT) == S_IFREG;
}

bool isSymbolicLink(string path) {
   struct stat sblk;
   if (lstat(path, &sblk) != 0) return false;
   return (sblk.st_mode & S_IFMT) == S_IFLNK;
}

bool isDirectory(string path) {
   struct stat sblk;
   if (lstat(path, &sblk) != 0) return false;
   return (sblk.st_mode & S_IFMT) == S_IFDIR;
}

void createDirectory(string path) {
   if (endsWith(path, "/")) {
      path = substring(path, 0, stringLength(path) - 2);
   }
   if (mkdir(path, 0777) != 0) {
      if (errno == EEXIST && isDirectory(path)) return;
      error("createDirectory: %s", strerror(errno));
   }
}

void deleteFile(string filename) {
   if (unlink(filename) != 0) {
      if (errno == ENOENT) return;
      error("deleteFile: %s", strerror(errno));
   }
}

void renameFile(string oldname, string newname) {
   if (rename(oldname, newname) != 0) {
      error("renameFile: %s", strerror(errno));
   }
}

string *listDirectory(string path) {
   string *result, name;
   struct dirent *dp;
   DIR *dir;
   Vector list;
   int i, n;

   if (path == NULL) path = ".";
   path = expandPathname(path);
   dir = opendir(path);
   if (dir == NULL) error("listDirectory: Can't open directory %s", path);
   list = newVector();
   while (true) {
      dp = readdir(dir);
      if (dp == NULL) break;
      name = dp->d_name;
      if (searchStringArray(name, SKIP_FILES) == -1) {
         add(list, copyString(name));
      }
   }
   closedir(dir);
   n = size(list);
   result = newArray(n + 1, string);
   for (i = 0; i < n; i++) {
      result[i] = get(list, i);
   }
   result[n] = NULL;
   freeVector(list);
   qsort(result, n, sizeof(string), alphaCompare);
   return result;
}

void setCurrentDirectory(string path) {
   chdir(path);
}

string getCurrentDirectory(void) {
   string cwd, result;

   cwd = getcwd(NULL, 0);
   result = copyString(cwd);
   free(cwd);
   return result;
}

string expandPathname(string filename) {
   string homedir;
   char *spos;
   struct passwd *pw;

   if (*filename == '~') {
      spos = filename;
      while ((*spos != '/') && (*spos != '\\') && (*spos != '\0')) {
         spos++;
      }
      if (spos - filename == 1) {
         homedir = getenv("HOME");
         if (homedir == NULL) homedir = getpwuid(getuid())->pw_dir;
      } else {
         homedir = substring(filename, 1, spos - filename - 1);
         pw = getpwnam(homedir);
         if (pw == NULL) error("expandPathname: No user %s", homedir);
         homedir = pw->pw_dir;
      }
      filename = concat(homedir, spos);
   } else {
      filename = copyString(filename);
   }
   for (spos = filename; *spos != '\0'; spos++) {
      if (*spos == '\\') *spos = '/';
   }
   return filename;
}

#ifdef __macosx__

string convertOSTypeToString(OSType type) {
   string str;
   int i;

   str = newArray(5, char);
   for (i = 3; i >= 0; i--) {
      str[i] = type & 0xFF;
      type >>= 8;
   }
   str[4] = '\0';
   return str;
}

OSType stringToOSType(string str) {
   int i, result;

   result = 0;
   str = concat(str, "   ");
   for (i = 0; i < 4; i++) {
      result = (result << 8) | str[i];
   }
   return (OSType) result;
}

#endif

string getFileType(string filename) {

#ifdef __macosx__

   FSCatalogInfo ci;
   FileInfo *info;
   FSRef fsr;
   FSRef *ref;
   int err;

   ref = &fsr;
   err = FSPathMakeRef((UInt8 *) filename, ref, NULL);
   if (err != 0) error("Internal error: Can't find file %s", filename);
   err = FSGetCatalogInfo(ref, kFSCatInfoFinderInfo, &ci, NULL, NULL, NULL);
   info = (FileInfo *) &ci.finderInfo;
   if (err != 0) error("Internal error: Can't get finder info for %s", filename);
   return convertOSTypeToString(info->fileType);

#else

   return "????";

#endif

}

string getFileCreator(string filename) {

#ifdef __macosx__

   FSCatalogInfo ci;
   FileInfo *info;
   FSRef fsr;
   FSRef *ref;
   int err;

   ref = &fsr;
   err = FSPathMakeRef((UInt8 *) filename, ref, NULL);
   if (err != 0) error("Internal error: Can't find file %s", filename);
   err = FSGetCatalogInfo(ref, kFSCatInfoFinderInfo, &ci, NULL, NULL, NULL);
   info = (FileInfo *) &ci.finderInfo;
   if (err != 0) error("Internal error: Can't get finder info for %s", filename);
   return convertOSTypeToString(info->fileCreator);

#else

   return "????";

#endif

}

void setFileTypeAndCreator(string path, string type, string creator) {

#ifdef __macosx__

   FSCatalogInfo ci;
   FileInfo *info;
   FSRef fsr;
   FSRef *ref;
   int err;

   ref = &fsr;
   err = FSPathMakeRef((UInt8 *) path, ref, NULL);
   if (err != 0) error("Internal error: Can't find file %s", path);
   err = FSGetCatalogInfo(ref, kFSCatInfoFinderInfo, &ci, NULL, NULL, NULL);
   info = (FileInfo *) &ci.finderInfo;
   if (err != 0) error("Internal error: Can't get finder info for %s", path);
   info->fileType = stringToOSType(type);
   info->fileCreator = stringToOSType(creator);
   FSSetCatalogInfo(ref, kFSCatInfoFinderInfo, &ci);

#endif

}

void copyFileTypeAndCreator(string src, string dst) {

#ifdef __macosx__

   FSCatalogInfo ci;
   FileInfo *info;
   FSRef fsr;
   FSRef *ref;
   OSType type, creator;
   int err;

   ref = &fsr;
   err = FSPathMakeRef((UInt8 *) src, ref, NULL);
   if (err != 0) error("Internal error: Can't find file %s", src);
   err = FSGetCatalogInfo(ref, kFSCatInfoFinderInfo, &ci, NULL, NULL, NULL);
   info = (FileInfo *) &ci.finderInfo;
   if (err != 0) error("Internal error: Can't get finder info for %s", src);
   type = info->fileType;
   creator = info->fileCreator;
   err = FSPathMakeRef((UInt8 *) dst, ref, NULL);
   if (err != 0) error("Internal error: Can't find file %s", dst);
   err = FSGetCatalogInfo(ref, kFSCatInfoFinderInfo, &ci, NULL, NULL, NULL);
   info = (FileInfo *) &ci.finderInfo;
   if (err != 0) error("Internal error: Can't get finder info for %s", dst);
   info->fileType = type;
   info->fileCreator = creator;
   FSSetCatalogInfo(ref, kFSCatInfoFinderInfo, &ci);

#endif

}

#endif
