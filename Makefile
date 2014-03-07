# Makefile for cslib directory
# Last modified on Thu Aug  8 18:00:01 2013 by eroberts
#****************************************************************

OBJECTS = \
    obj/bst.o \
    obj/charset.o \
    obj/cmpfn.o \
    obj/cslib.o \
    obj/exception.o \
    obj/filelib.o \
    obj/foreach.o \
    obj/generic.o \
    obj/gevents.o \
    obj/gobjects.o \
    obj/gmath.o \
    obj/graph.o \
    obj/gtimer.o \
    obj/gtypes.o \
    obj/gwindow.o \
    obj/hashmap.o \
    obj/iterator.o \
    obj/loadobj.o \
    obj/map.o \
    obj/options.o \
    obj/platform.o \
    obj/pqueue.o \
    obj/queue.o \
    obj/random.o \
    obj/ref.o \
    obj/set.o \
    obj/simpio.o \
    obj/sound.o \
    obj/stack.o \
    obj/strbuf.o \
    obj/strlib.o \
    obj/tokenscanner.o \
    obj/unittest.o \
    obj/unixfile.o \
    obj/vector.o

LIBRARIES = lib/libcs.a

TESTS = \
    TestStanfordCSLib

TESTOBJECTS = \
    obj/TestStanfordCSLib.o


# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(OBJECTS) $(LIBRARIES) $(TESTS)


# ***************************************************************
# Library compilations

obj/bst.o: src/bst.c include/bst.h include/cmpfn.h include/cslib.h \
           include/exception.h include/foreach.h include/generic.h \
           include/iterator.h include/itertype.h include/strlib.h \
           include/unittest.h
	gcc -c -o obj/bst.o -Iinclude src/bst.c

obj/charset.o: src/charset.c include/charset.h include/cmpfn.h \
               include/cslib.h include/exception.h include/foreach.h \
               include/generic.h include/iterator.h include/itertype.h \
               include/strlib.h include/unittest.h
	gcc -c -o obj/charset.o -Iinclude src/charset.c

obj/cmdscan.o: src/cmdscan.c include/cmdscan.h include/cmpfn.h \
               include/cslib.h include/exception.h include/generic.h \
               include/hashmap.h include/iterator.h include/itertype.h \
               include/private/tokenpatch.h include/simpio.h \
               include/strlib.h include/tokenscanner.h
	gcc -c -o obj/cmdscan.o -Iinclude src/cmdscan.c

obj/cmpfn.o: src/cmpfn.c include/cmpfn.h include/cslib.h include/generic.h \
             include/strlib.h
	gcc -c -o obj/cmpfn.o -Iinclude src/cmpfn.c

obj/cslib.o: src/cslib.c include/cslib.h include/exception.h
	gcc -c -o obj/cslib.o -Iinclude src/cslib.c

obj/exception.o: src/exception.c include/cmpfn.h include/cslib.h \
                 include/exception.h include/generic.h include/strlib.h \
                 include/unittest.h
	gcc -c -o obj/exception.o -Iinclude src/exception.c

obj/filelib.o: src/filelib.c include/cmpfn.h include/cslib.h \
               include/exception.h include/filelib.h include/generic.h \
               include/iterator.h include/itertype.h include/strlib.h \
               include/unittest.h
	gcc -c -o obj/filelib.o -Iinclude src/filelib.c

obj/foreach.o: src/foreach.c include/cslib.h include/foreach.h \
               include/iterator.h
	gcc -c -o obj/foreach.o -Iinclude src/foreach.c

obj/generic.o: src/generic.c include/charset.h include/cmpfn.h \
               include/cslib.h include/exception.h include/generic.h \
               include/gevents.h include/gobjects.h include/gtimer.h \
               include/gtypes.h include/gwindow.h include/hashmap.h \
               include/iterator.h include/map.h include/pqueue.h \
               include/queue.h include/ref.h include/set.h include/stack.h \
               include/strbuf.h include/strlib.h include/vector.h
	gcc -c -o obj/generic.o -Iinclude src/generic.c

obj/gevents.o: src/gevents.c include/cmpfn.h include/cslib.h \
               include/exception.h include/generic.h include/gevents.h \
               include/ginteractors.h include/gobjects.h include/gtimer.h \
               include/gtypes.h include/gwindow.h include/hashmap.h \
               include/iterator.h include/platform.h include/sound.h \
               include/strlib.h include/unittest.h include/vector.h
	gcc -c -o obj/gevents.o -Iinclude src/gevents.c

obj/gmath.o: src/gmath.c include/gmath.h
	gcc -c -o obj/gmath.o -Iinclude src/gmath.c

obj/gobjects.o: src/gobjects.c include/cmpfn.h include/cslib.h \
                include/generic.h include/gevents.h include/ginteractors.h \
                include/gmath.h include/gobjects.h include/gtimer.h \
                include/gtypes.h include/gwindow.h include/platform.h \
                include/sound.h include/vector.h
	gcc -c -o obj/gobjects.o -Iinclude src/gobjects.c

obj/graph.o: src/graph.c include/cmpfn.h include/cslib.h \
             include/exception.h include/foreach.h include/generic.h \
             include/graph.h include/hashmap.h include/iterator.h \
             include/itertype.h include/set.h include/strlib.h \
             include/unittest.h
	gcc -c -o obj/graph.o -Iinclude src/graph.c

obj/gtimer.o: src/gtimer.c include/cmpfn.h include/cslib.h \
              include/generic.h include/gevents.h include/ginteractors.h \
              include/gobjects.h include/gtimer.h include/gtypes.h \
              include/gwindow.h include/platform.h include/sound.h \
              include/vector.h
	gcc -c -o obj/gtimer.o -Iinclude src/gtimer.c

obj/gtypes.o: src/gtypes.c include/cmpfn.h include/cslib.h \
              include/exception.h include/generic.h include/gtypes.h \
              include/unittest.h
	gcc -c -o obj/gtypes.o -Iinclude src/gtypes.c

obj/gwindow.o: src/gwindow.c include/cmpfn.h include/cslib.h \
               include/generic.h include/gevents.h include/ginteractors.h \
               include/gmath.h include/gobjects.h include/gtimer.h \
               include/gtypes.h include/gwindow.h include/platform.h \
               include/sound.h include/vector.h
	gcc -c -o obj/gwindow.o -Iinclude src/gwindow.c

obj/hashmap.o: src/hashmap.c include/cmpfn.h include/cslib.h \
               include/exception.h include/foreach.h include/generic.h \
               include/hashmap.h include/iterator.h include/itertype.h \
               include/strlib.h include/unittest.h
	gcc -c -o obj/hashmap.o -Iinclude src/hashmap.c

obj/iterator.o: src/iterator.c include/cmpfn.h include/cslib.h \
                include/iterator.h include/itertype.h
	gcc -c -o obj/iterator.o -Iinclude src/iterator.c

obj/loadobj.o: src/loadobj.c include/cmpfn.h include/cslib.h \
               include/filelib.h include/generic.h include/iterator.h \
               include/loadobj.h include/strlib.h
	gcc -c -o obj/loadobj.o -Iinclude src/loadobj.c

obj/map.o: src/map.c include/bst.h include/cmpfn.h include/cslib.h \
           include/exception.h include/foreach.h include/generic.h \
           include/iterator.h include/itertype.h include/map.h \
           include/strlib.h include/unittest.h
	gcc -c -o obj/map.o -Iinclude src/map.c

obj/options.o: src/options.c include/cmpfn.h include/cslib.h \
               include/exception.h include/generic.h include/hashmap.h \
               include/iterator.h include/options.h include/strlib.h \
               include/unittest.h include/vector.h
	gcc -c -o obj/options.o -Iinclude src/options.c

obj/platform.o: src/platform.c include/cmpfn.h include/cslib.h \
                include/filelib.h include/generic.h include/gevents.h \
                include/ginteractors.h include/gobjects.h include/gtimer.h \
                include/gtypes.h include/gwindow.h include/hashmap.h \
                include/iterator.h include/platform.h \
                include/private/tokenpatch.h include/queue.h \
                include/simpio.h include/sound.h include/strbuf.h \
                include/strlib.h include/tokenscanner.h include/vector.h
	gcc -c -o obj/platform.o -Iinclude src/platform.c

obj/pqueue.o: src/pqueue.c include/cmpfn.h include/cslib.h \
              include/exception.h include/generic.h include/pqueue.h \
              include/unittest.h include/vector.h
	gcc -c -o obj/pqueue.o -Iinclude src/pqueue.c

obj/queue.o: src/queue.c include/cmpfn.h include/cslib.h \
             include/exception.h include/generic.h include/queue.h \
             include/unittest.h
	gcc -c -o obj/queue.o -Iinclude src/queue.c

obj/random.o: src/random.c include/cslib.h include/exception.h \
              include/private/randompatch.h include/random.h \
              include/unittest.h
	gcc -c -o obj/random.o -Iinclude src/random.c

obj/ref.o: src/ref.c include/cslib.h include/ref.h
	gcc -c -o obj/ref.o -Iinclude src/ref.c

obj/set.o: src/set.c include/bst.h include/cmpfn.h include/cslib.h \
           include/exception.h include/foreach.h include/generic.h \
           include/iterator.h include/itertype.h include/map.h \
           include/set.h include/strlib.h include/unittest.h
	gcc -c -o obj/set.o -Iinclude src/set.c

obj/simpio.o: src/simpio.c include/cmpfn.h include/cslib.h \
              include/generic.h include/simpio.h include/strlib.h
	gcc -c -o obj/simpio.o -Iinclude src/simpio.c

obj/sound.o: src/sound.c include/cmpfn.h include/cslib.h include/generic.h \
             include/gevents.h include/ginteractors.h include/gobjects.h \
             include/gtimer.h include/gtypes.h include/gwindow.h \
             include/platform.h include/sound.h include/vector.h
	gcc -c -o obj/sound.o -Iinclude src/sound.c

obj/stack.o: src/stack.c include/cmpfn.h include/cslib.h \
             include/exception.h include/generic.h include/stack.h \
             include/unittest.h
	gcc -c -o obj/stack.o -Iinclude src/stack.c

obj/strbuf.o: src/strbuf.c include/cmpfn.h include/cslib.h \
              include/exception.h include/generic.h include/strbuf.h \
              include/strlib.h include/unittest.h
	gcc -c -o obj/strbuf.o -Iinclude src/strbuf.c

obj/strlib.o: src/strlib.c include/cmpfn.h include/cslib.h \
              include/exception.h include/generic.h include/strlib.h \
              include/unittest.h
	gcc -c -o obj/strlib.o -Iinclude src/strlib.c

obj/tokenscanner.o: src/tokenscanner.c include/cmpfn.h include/cslib.h \
                    include/exception.h include/generic.h \
                    include/private/tokenpatch.h include/strbuf.h \
                    include/strlib.h include/tokenscanner.h \
                    include/unittest.h
	gcc -c -o obj/tokenscanner.o -Iinclude src/tokenscanner.c

obj/unittest.o: src/unittest.c include/cmpfn.h include/cslib.h \
                include/exception.h include/generic.h include/strlib.h \
                include/unittest.h
	gcc -c -o obj/unittest.o -Iinclude src/unittest.c

obj/unixfile.o: src/unixfile.c include/cmpfn.h include/cslib.h \
                include/filelib.h include/generic.h include/iterator.h \
                include/strlib.h include/vector.h
	gcc -c -o obj/unixfile.o -Iinclude src/unixfile.c

obj/vector.o: src/vector.c include/cmpfn.h include/cslib.h \
              include/exception.h include/generic.h include/iterator.h \
              include/itertype.h include/strlib.h include/unittest.h \
              include/vector.h
	gcc -c -o obj/vector.o -Iinclude src/vector.c


# ***************************************************************
# Entry to reconstruct the library archive

lib/libcs.a: $(OBJECTS)
	-rm -f lib/libcs.a
	ar cr lib/libcs.a $(OBJECTS)
	ranlib lib/libcs.a


# ***************************************************************
# Test program

obj/TestStanfordCSLib.o: src/tests/TestStanfordCSLib.c include/cslib.h \
                         include/strlib.h include/unittest.h
	gcc -c -o obj/TestStanfordCSLib.o -Iinclude \
            src/tests/TestStanfordCSLib.c

TestStanfordCSLib: $(TESTOBJECTS) lib/libcs.a
	gcc -o TestStanfordCSLib $(TESTOBJECTS) -Llib -lcs -lm


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	@rm -f `find . -name ',*' -o -name '.,*' -o -name '*~'`
	@rm -f `find . -name '*.tmp' -o -name '*.err'`
	@rm -f `find . -name core -o -name a.out`

scratch clean: tidy
	@rm -f -r $(OBJECTS) $(LIBRARIES) $(TESTS) $(TESTOBJECTS)
