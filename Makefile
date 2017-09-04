.SECONDARY:

NAME = spl
CC = gcc

EMSCRIPTEN_ROOT ?= /usr/lib/emscripten
EMCC = $(EMSCRIPTEN_ROOT)/emcc
EMCONF = $(EMSCRIPTEN_ROOT)/emconfigure

SDLINC = /usr/include/SDL2
CFLAGS = -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter -pipe -D_XOPEN_SOURCE=500 -std=c11 -fPIC -I$(INCDIR) -I$(SDLINC)  -ggdb3 -O0
TARGET = lib$(NAME).so
WEBTARGET = lib$(NAME).bc

SRCDIR  = src
OBJDIR  = obj
INCDIR  = include

SRCS = $(SRCDIR)/typemap.c $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

GFX_DIR = SDL2_gfx-1.0.3
GFX_TAR = $(addsuffix .tar, $(GFX_DIR))
GFX_LIB_DIR = $(GFX_DIR)/.libs
GFX = $(GFX_LIB_DIR)/libSDL2_gfx.a

EMCFLAGS = -O3 -I $(INCDIR) -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s USE_SDL=2 -s USE_SDL_TTF=2


LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_gfx

$(shell `mkdir -p $(OBJDIR)`)

.PHONY: all
all: $(TARGET)

native: $(TARGET) breakout.c
	$(CC) -L. -DNAPTIME=8 $(CFLAGS) -o breakout $^ $(LDFLAGS) -l$(NAME) -lSDL2main

web: $(WEBTARGET) breakout.c
	$(EMCC) \
	    $(EMCFLAGS) \
	    -DNAPTIME=1 \
	    -s EMTERPRETIFY=1 \
	    -s EMTERPRETIFY_WHITELIST='["_getNextEvent", "_pause_", "_waitForClick", "_main"]' \
	    -s EMTERPRETIFY_ASYNC=1 \
	    -s EMTERPRETIFY_FILE=\'breakout.bin\' \
	    -s TOTAL_MEMORY=67108864 \
	    -s WASM=1 \
	    --preload-file assets \
	    -o breakout.js \
	    $^

browser: web
	FLASK_APP=application.py flask run 

$(TARGET): $(OBJS)
	$(CC) -shared $(CFLAGS) -o $@ $^ $(LDFLAGS)


$(WEBTARGET): $(SRCS) $(GFX) $(INCS) Makefile
	$(EMCC) $(EMCFLAGS) -I $(GFX_DIR) $(SRCS) $(GFX) -o libspl.bc


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) Makefile
	$(CC) $(CFLAGS) -MMD -c -o $@ $< $(LDFLAGS)

$(SRCDIR)/typemap.c: $(SRCDIR)/typemap.gperf
	gperf --ignore-case -N"in_type_set" -F",UNKNOWN" -Ct  $^  --output-file $@

$(GFX_DIR)/configure: $(GFX_TAR)
	tar xvf $(GFX_TAR)

$(GFX): $(GFX_DIR)/configure
	cd $(GFX_DIR); EMCONFIGURE_JS=1 $(EMCONF) ./configure --disable-mmx
	$(MAKE) -C $(GFX_DIR) all
    

-include $(wildcard $(OBJDIR)/*.d)

.PHONY: clean
clean:
	rm -f core $(TARGET) $(WEBTARGET) src/color.c src/typemap.c breakout vgcore.*
	rm -f -r $(OBJDIR) $(GFX_DIR)
	rm -f breakout.{js,wasm,data,bin,mem}
