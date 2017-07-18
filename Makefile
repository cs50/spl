.SECONDARY:

NAME = spl
CC = gcc
EMCC = /usr/lib/emscripten/emcc
EMCONF = /usr/lib/emscripten/emconfigure
SDLINC = /usr/include/SDL2
CFLAGS = -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter -pipe -D_XOPEN_SOURCE=500 -std=c11 -fPIC -I$(INCDIR) -I$(SDLINC)  -ggdb3 -O0
TARGET = lib$(NAME).so

SRCDIR  = src
OBJDIR  = obj
INCDIR  = include
BCDIR   = bc

SRCS = $(SRCDIR)/typemap.c $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

GFX_DIR = SDL2_gfx-1.0.3
GFX_LIB_DIR = $(GFX_DIR)/.libs
GFX = $(GFX_LIB_DIR)/libSDL2_gfx.a

EMCFLAGS = -s TOTAL_MEMORY=67108864 -O3 -I $(GFX_DIR) -I $(INCDIR) -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1 -s USE_SDL=2 -s USE_SDL_TTF=2 --preload-file assets -s WASM=1


LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_gfx

$(shell `mkdir -p $(OBJDIR) $(BCDIR)`)

.PHONY: all
all: $(TARGET)

native: $(TARGET) breakout.c
	$(CC) -L. -DNAPTIME=8 $(CFLAGS) -o breakout $^ $(LDFLAGS) -l$(NAME) -lSDL2main


$(TARGET): $(OBJS)
	$(CC) -shared $(CFLAGS) -o $@ $^ $(LDFLAGS)

web: $(SRCS) $(GFX) breakout.c $(INCS) Makefile
	$(EMCC) -MMD $(EMCFLAGS) $(GFX) -o $(BCDIR)/libSDL2_gfx.bc
	$(EMCC) -MMD $(EMCFLAGS) $(SRCS) -o $(BCDIR)/libspl.bc
	$(EMCC) -DNAPTIME=0 -s EMTERPRETIFY_FILE=\'breakout.bin\' $(EMCFLAGS) -o breakout.js breakout.c $(BCDIR)/libspl.bc $(BCDIR)/libSDL2_gfx.bc

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) Makefile
	$(CC) $(CFLAGS) -MMD -c -o $@ $< $(LDFLAGS)


$(SRCDIR)/typemap.c: $(SRCDIR)/typemap.gperf
	gperf --ignore-case -N"in_type_set" -F",UNKNOWN" -Ct  $^  --output-file $@

$(GFX): 
	cd $(GFX_DIR); EMCONFIGURE_JS=1 $(EMCONF) ./configure --disable-mmx
	$(MAKE) -C $(GFX_DIR) all
    

-include $(wildcard $(OBJDIR)/*.d)
-include $(wildcard $(BCDIR)/*.d)

.PHONY: clean
clean:
	rm -f core $(TARGET) src/color.c src/typemap.c breakout vgcore.*
	rm -f -r $(OBJDIR) $(BCDIR)
	rm -f breakout.{js,wasm,data,bin,mem}
