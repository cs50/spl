# ****************************************************************
# Makefile for SPL

BUILD = \
    build \
    build/classes \
    build/lib \
    build/obj \
    build/tests

OBJECTS = \
    build/obj/bst.o \
    build/obj/charset.o \
    build/obj/cmpfn.o \
    build/obj/cslib.o \
    build/obj/exception.o \
    build/obj/filelib.o \
    build/obj/foreach.o \
    build/obj/generic.o \
    build/obj/gevents.o \
    build/obj/gobjects.o \
    build/obj/gmath.o \
    build/obj/graph.o \
    build/obj/gtimer.o \
    build/obj/gtypes.o \
    build/obj/gwindow.o \
    build/obj/hashmap.o \
    build/obj/iterator.o \
    build/obj/loadobj.o \
    build/obj/map.o \
    build/obj/options.o \
    build/obj/platform.o \
    build/obj/pqueue.o \
    build/obj/queue.o \
    build/obj/random.o \
    build/obj/ref.o \
    build/obj/set.o \
    build/obj/simpio.o \
    build/obj/sound.o \
    build/obj/stack.o \
    build/obj/strbuf.o \
    build/obj/strlib.o \
    build/obj/tokenscanner.o \
    build/obj/unittest.o \
    build/obj/unixfile.o \
    build/obj/vector.o

LIBRARIES = build/lib/libcs.a

TESTS = \
    TestStanfordCSLib

TESTOBJECTS = \
    build/obj/TestStanfordCSLib.o

JAR = spl.jar


# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(BUILD) $(OBJECTS) $(LIBRARIES) $(TESTS) $(JAR)


# ***************************************************************
# directories

$(BUILD):
	mkdir -p $(BUILD)


# ***************************************************************
# Library compilations

build/obj/bst.o: c/src/bst.c c/include/bst.h c/include/cmpfn.h c/include/cslib.h \
           c/include/exception.h c/include/foreach.h c/include/generic.h \
           c/include/iterator.h c/include/itertype.h c/include/strlib.h \
           c/include/unittest.h
	gcc -c -o build/obj/bst.o -Ic/include c/src/bst.c

build/obj/charset.o: c/src/charset.c c/include/charset.h c/include/cmpfn.h \
               c/include/cslib.h c/include/exception.h c/include/foreach.h \
               c/include/generic.h c/include/iterator.h c/include/itertype.h \
               c/include/strlib.h c/include/unittest.h
	gcc -c -o build/obj/charset.o -Ic/include c/src/charset.c

build/obj/cmdscan.o: c/src/cmdscan.c c/include/cmdscan.h c/include/cmpfn.h \
               c/include/cslib.h c/include/exception.h c/include/generic.h \
               c/include/hashmap.h c/include/iterator.h c/include/itertype.h \
               c/include/private/tokenpatch.h c/include/simpio.h \
               c/include/strlib.h c/include/tokenscanner.h
	gcc -c -o build/obj/cmdscan.o -Ic/include c/src/cmdscan.c

build/obj/cmpfn.o: c/src/cmpfn.c c/include/cmpfn.h c/include/cslib.h c/include/generic.h \
             c/include/strlib.h
	gcc -c -o build/obj/cmpfn.o -Ic/include c/src/cmpfn.c

build/obj/cslib.o: c/src/cslib.c c/include/cslib.h c/include/exception.h
	gcc -c -o build/obj/cslib.o -Ic/include c/src/cslib.c

build/obj/exception.o: c/src/exception.c c/include/cmpfn.h c/include/cslib.h \
                 c/include/exception.h c/include/generic.h c/include/strlib.h \
                 c/include/unittest.h
	gcc -c -o build/obj/exception.o -Ic/include c/src/exception.c

build/obj/filelib.o: c/src/filelib.c c/include/cmpfn.h c/include/cslib.h \
               c/include/exception.h c/include/filelib.h c/include/generic.h \
               c/include/iterator.h c/include/itertype.h c/include/strlib.h \
               c/include/unittest.h
	gcc -c -o build/obj/filelib.o -Ic/include c/src/filelib.c

build/obj/foreach.o: c/src/foreach.c c/include/cslib.h c/include/foreach.h \
               c/include/iterator.h
	gcc -c -o build/obj/foreach.o -Ic/include c/src/foreach.c

build/obj/generic.o: c/src/generic.c c/include/charset.h c/include/cmpfn.h \
               c/include/cslib.h c/include/exception.h c/include/generic.h \
               c/include/gevents.h c/include/gobjects.h c/include/gtimer.h \
               c/include/gtypes.h c/include/gwindow.h c/include/hashmap.h \
               c/include/iterator.h c/include/map.h c/include/pqueue.h \
               c/include/queue.h c/include/ref.h c/include/set.h c/include/stack.h \
               c/include/strbuf.h c/include/strlib.h c/include/vector.h
	gcc -c -o build/obj/generic.o -Ic/include c/src/generic.c

build/obj/gevents.o: c/src/gevents.c c/include/cmpfn.h c/include/cslib.h \
               c/include/exception.h c/include/generic.h c/include/gevents.h \
               c/include/ginteractors.h c/include/gobjects.h c/include/gtimer.h \
               c/include/gtypes.h c/include/gwindow.h c/include/hashmap.h \
               c/include/iterator.h c/include/platform.h c/include/sound.h \
               c/include/strlib.h c/include/unittest.h c/include/vector.h
	gcc -c -o build/obj/gevents.o -Ic/include c/src/gevents.c

build/obj/gmath.o: c/src/gmath.c c/include/gmath.h
	gcc -c -o build/obj/gmath.o -Ic/include c/src/gmath.c

build/obj/gobjects.o: c/src/gobjects.c c/include/cmpfn.h c/include/cslib.h \
                c/include/generic.h c/include/gevents.h c/include/ginteractors.h \
                c/include/gmath.h c/include/gobjects.h c/include/gtimer.h \
                c/include/gtypes.h c/include/gwindow.h c/include/platform.h \
                c/include/sound.h c/include/vector.h
	gcc -c -o build/obj/gobjects.o -Ic/include c/src/gobjects.c

build/obj/graph.o: c/src/graph.c c/include/cmpfn.h c/include/cslib.h \
             c/include/exception.h c/include/foreach.h c/include/generic.h \
             c/include/graph.h c/include/hashmap.h c/include/iterator.h \
             c/include/itertype.h c/include/set.h c/include/strlib.h \
             c/include/unittest.h
	gcc -c -o build/obj/graph.o -Ic/include c/src/graph.c

build/obj/gtimer.o: c/src/gtimer.c c/include/cmpfn.h c/include/cslib.h \
              c/include/generic.h c/include/gevents.h c/include/ginteractors.h \
              c/include/gobjects.h c/include/gtimer.h c/include/gtypes.h \
              c/include/gwindow.h c/include/platform.h c/include/sound.h \
              c/include/vector.h
	gcc -c -o build/obj/gtimer.o -Ic/include c/src/gtimer.c

build/obj/gtypes.o: c/src/gtypes.c c/include/cmpfn.h c/include/cslib.h \
              c/include/exception.h c/include/generic.h c/include/gtypes.h \
              c/include/unittest.h
	gcc -c -o build/obj/gtypes.o -Ic/include c/src/gtypes.c

build/obj/gwindow.o: c/src/gwindow.c c/include/cmpfn.h c/include/cslib.h \
               c/include/generic.h c/include/gevents.h c/include/ginteractors.h \
               c/include/gmath.h c/include/gobjects.h c/include/gtimer.h \
               c/include/gtypes.h c/include/gwindow.h c/include/platform.h \
               c/include/sound.h c/include/vector.h
	gcc -c -o build/obj/gwindow.o -Ic/include c/src/gwindow.c

build/obj/hashmap.o: c/src/hashmap.c c/include/cmpfn.h c/include/cslib.h \
               c/include/exception.h c/include/foreach.h c/include/generic.h \
               c/include/hashmap.h c/include/iterator.h c/include/itertype.h \
               c/include/strlib.h c/include/unittest.h
	gcc -c -o build/obj/hashmap.o -Ic/include c/src/hashmap.c

build/obj/iterator.o: c/src/iterator.c c/include/cmpfn.h c/include/cslib.h \
                c/include/iterator.h c/include/itertype.h
	gcc -c -o build/obj/iterator.o -Ic/include c/src/iterator.c

build/obj/loadobj.o: c/src/loadobj.c c/include/cmpfn.h c/include/cslib.h \
               c/include/filelib.h c/include/generic.h c/include/iterator.h \
               c/include/loadobj.h c/include/strlib.h
	gcc -c -o build/obj/loadobj.o -Ic/include c/src/loadobj.c

build/obj/map.o: c/src/map.c c/include/bst.h c/include/cmpfn.h c/include/cslib.h \
           c/include/exception.h c/include/foreach.h c/include/generic.h \
           c/include/iterator.h c/include/itertype.h c/include/map.h \
           c/include/strlib.h c/include/unittest.h
	gcc -c -o build/obj/map.o -Ic/include c/src/map.c

build/obj/options.o: c/src/options.c c/include/cmpfn.h c/include/cslib.h \
               c/include/exception.h c/include/generic.h c/include/hashmap.h \
               c/include/iterator.h c/include/options.h c/include/strlib.h \
               c/include/unittest.h c/include/vector.h
	gcc -c -o build/obj/options.o -Ic/include c/src/options.c

build/obj/platform.o: c/src/platform.c c/include/cmpfn.h c/include/cslib.h \
                c/include/filelib.h c/include/generic.h c/include/gevents.h \
                c/include/ginteractors.h c/include/gobjects.h c/include/gtimer.h \
                c/include/gtypes.h c/include/gwindow.h c/include/hashmap.h \
                c/include/iterator.h c/include/platform.h \
                c/include/private/tokenpatch.h c/include/queue.h \
                c/include/simpio.h c/include/sound.h c/include/strbuf.h \
                c/include/strlib.h c/include/tokenscanner.h c/include/vector.h
	gcc -c -o build/obj/platform.o -Ic/include c/src/platform.c

build/obj/pqueue.o: c/src/pqueue.c c/include/cmpfn.h c/include/cslib.h \
              c/include/exception.h c/include/generic.h c/include/pqueue.h \
              c/include/unittest.h c/include/vector.h
	gcc -c -o build/obj/pqueue.o -Ic/include c/src/pqueue.c

build/obj/queue.o: c/src/queue.c c/include/cmpfn.h c/include/cslib.h \
             c/include/exception.h c/include/generic.h c/include/queue.h \
             c/include/unittest.h
	gcc -c -o build/obj/queue.o -Ic/include c/src/queue.c

build/obj/random.o: c/src/random.c c/include/cslib.h c/include/exception.h \
              c/include/private/randompatch.h c/include/random.h \
              c/include/unittest.h
	gcc -c -o build/obj/random.o -Ic/include c/src/random.c

build/obj/ref.o: c/src/ref.c c/include/cslib.h c/include/ref.h
	gcc -c -o build/obj/ref.o -Ic/include c/src/ref.c

build/obj/set.o: c/src/set.c c/include/bst.h c/include/cmpfn.h c/include/cslib.h \
           c/include/exception.h c/include/foreach.h c/include/generic.h \
           c/include/iterator.h c/include/itertype.h c/include/map.h \
           c/include/set.h c/include/strlib.h c/include/unittest.h
	gcc -c -o build/obj/set.o -Ic/include c/src/set.c

build/obj/simpio.o: c/src/simpio.c c/include/cmpfn.h c/include/cslib.h \
              c/include/generic.h c/include/simpio.h c/include/strlib.h
	gcc -c -o build/obj/simpio.o -Ic/include c/src/simpio.c

build/obj/sound.o: c/src/sound.c c/include/cmpfn.h c/include/cslib.h c/include/generic.h \
             c/include/gevents.h c/include/ginteractors.h c/include/gobjects.h \
             c/include/gtimer.h c/include/gtypes.h c/include/gwindow.h \
             c/include/platform.h c/include/sound.h c/include/vector.h
	gcc -c -o build/obj/sound.o -Ic/include c/src/sound.c

build/obj/stack.o: c/src/stack.c c/include/cmpfn.h c/include/cslib.h \
             c/include/exception.h c/include/generic.h c/include/stack.h \
             c/include/unittest.h
	gcc -c -o build/obj/stack.o -Ic/include c/src/stack.c

build/obj/strbuf.o: c/src/strbuf.c c/include/cmpfn.h c/include/cslib.h \
              c/include/exception.h c/include/generic.h c/include/strbuf.h \
              c/include/strlib.h c/include/unittest.h
	gcc -c -o build/obj/strbuf.o -Ic/include c/src/strbuf.c

build/obj/strlib.o: c/src/strlib.c c/include/cmpfn.h c/include/cslib.h \
              c/include/exception.h c/include/generic.h c/include/strlib.h \
              c/include/unittest.h
	gcc -c -o build/obj/strlib.o -Ic/include c/src/strlib.c

build/obj/tokenscanner.o: c/src/tokenscanner.c c/include/cmpfn.h c/include/cslib.h \
                    c/include/exception.h c/include/generic.h \
                    c/include/private/tokenpatch.h c/include/strbuf.h \
                    c/include/strlib.h c/include/tokenscanner.h \
                    c/include/unittest.h
	gcc -c -o build/obj/tokenscanner.o -Ic/include c/src/tokenscanner.c

build/obj/unittest.o: c/src/unittest.c c/include/cmpfn.h c/include/cslib.h \
                c/include/exception.h c/include/generic.h c/include/strlib.h \
                c/include/unittest.h
	gcc -c -o build/obj/unittest.o -Ic/include c/src/unittest.c

build/obj/unixfile.o: c/src/unixfile.c c/include/cmpfn.h c/include/cslib.h \
                c/include/filelib.h c/include/generic.h c/include/iterator.h \
                c/include/strlib.h c/include/vector.h
	gcc -c -o build/obj/unixfile.o -Ic/include c/src/unixfile.c

build/obj/vector.o: c/src/vector.c c/include/cmpfn.h c/include/cslib.h \
              c/include/exception.h c/include/generic.h c/include/iterator.h \
              c/include/itertype.h c/include/strlib.h c/include/unittest.h \
              c/include/vector.h
	gcc -c -o build/obj/vector.o -Ic/include c/src/vector.c


# ***************************************************************
# Entry to reconstruct the library archive

build/lib/libcs.a: $(OBJECTS)
	-rm -f build/lib/libcs.a
	ar cr build/lib/libcs.a $(OBJECTS)
	ranlib build/lib/libcs.a
	cp -r c/include build/


# ***************************************************************
# Test program

build/obj/TestStanfordCSLib.o: c/tests/TestStanfordCSLib.c c/include/cslib.h \
	c/include/strlib.h c/include/unittest.h
	gcc -c -o build/obj/TestStanfordCSLib.o -Ic/include \
            c/tests/TestStanfordCSLib.c

TestStanfordCSLib: $(TESTOBJECTS) build/lib/libcs.a
	gcc -o build/tests/TestStanfordCSLib $(TESTOBJECTS) -Lbuild/lib -lcs -lm


# ***************************************************************
# Java Back End

$(JAR): stanford/spl/JavaBackEnd.class
	@cp java/lib/acm.jar build/lib/spl.jar
	@(cd build/classes; jar ufm ../lib/spl.jar ../../java/include/JBEManifest.txt \
		`find stanford -name '*.class'`)
	@echo jar cf build/lib/spl.jar . . .

stanford/spl/JavaBackEnd.class: java/src/stanford/spl/*.java
	javac -d build/classes -classpath java/lib/acm.jar -sourcepath java/src \
		java/src/stanford/spl/JavaBackEnd.java


# ***************************************************************
# install

install: build/lib/libcs.a $(JAR)
	rm -rf /usr/local/include/spl
	cp -r build/include /usr/local/include/spl
	chmod -R a+rX /usr/local/include/spl
	cp build/lib/{libcs.a,spl.jar} /usr/local/lib/
	chmod -R a+r /usr/local/lib/{libcs.a,spl.jar}


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	@rm -f `find . -name ',*' -o -name '.,*' -o -name '*~'`
	@rm -f `find . -name '*.tmp' -o -name '*.err'`
	@rm -f `find . -name core -o -name a.out`
	@rm -rf build/classes
	@rm -rf build/obj

scratch clean: tidy
	@rm -f -r $(BUILD) $(OBJECTS) $(LIBRARIES) $(TESTS) $(TESTOBJECTS)
