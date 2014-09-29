# Makefile for spl
#****************************************************************

PROGRAMS = \
    Breakout \
    DrawLines \
    DrawRectangles \
    GHelloWorld \
    PacMan \
    StopSign \
    TestGraphics \
    TestInteractors \
    USFlag

FLAGS = -L../lib -lcs -lm


# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAMS)

Breakout: Breakout.o
	gcc -o Breakout Breakout.o $(FLAGS)

Breakout.o: Breakout.c
	gcc -c -I../include Breakout.c

DrawLines: DrawLines.o
	gcc -o DrawLines DrawLines.o $(FLAGS)

DrawLines.o: DrawLines.c
	gcc -c -I../include DrawLines.c

DrawRectangles: DrawRectangles.o
	gcc -o DrawRectangles DrawRectangles.o $(FLAGS)

DrawRectangles.o: DrawRectangles.c
	gcc -c -I../include DrawRectangles.c

GHelloWorld: GHelloWorld.o
	gcc -o GHelloWorld GHelloWorld.o $(FLAGS)

GHelloWorld.o: GHelloWorld.c
	gcc -c -I../include GHelloWorld.c

PacMan: PacMan.o
	gcc -o PacMan PacMan.o $(FLAGS)

PacMan.o: PacMan.c
	gcc -c -I../include PacMan.c

StopSign: StopSign.o
	gcc -o StopSign StopSign.o $(FLAGS)

StopSign.o: StopSign.c
	gcc -c -I../include StopSign.c

TestGraphics: TestGraphics.o
	gcc -o TestGraphics TestGraphics.o $(FLAGS)

TestGraphics.o: TestGraphics.c
	gcc -c -I../include TestGraphics.c

TestInteractors: TestInteractors.o
	gcc -o TestInteractors TestInteractors.o $(FLAGS)

TestInteractors.o: TestInteractors.c
	gcc -c -I../include TestInteractors.c

USFlag: USFlag.o
	gcc -o USFlag USFlag.o $(FLAGS)

USFlag.o: USFlag.c
	gcc -c -I../include USFlag.c


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	@rm -f `find . -name ',*' -o -name '.,*' -o -name '*~'`
	@rm -f `find . -name '*.tmp' -o -name '*.err'`
	@rm -f `find . -name core -o -name a.out`

clean scratch: tidy
	@rm -f *.o *.a $(PROGRAMS)
