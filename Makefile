.SECONDARY:

NAME = spl
CC = gcc
EMCC = /usr/lib/emscripten/emcc
EMCONF = /usr/lib/emscripten/emconfigure
SDLINC = /usr/include/SDL2
CFLAGS = -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter -pipe -D_XOPEN_SOURCE=500 -std=c11 -fPIC -I$(INCDIR) -I$(SDLINC)  -ggdb3 -O2
TARGET = lib$(NAME).so

SRCDIR  = src
OBJDIR  = obj
INCDIR  = include
BCDIR   = bc

SRCS = $(wildcard $(SRCDIR)/*.c)
INCS = $(wildcard $(INCDIR)/*.h)
OBJS = $(OBJDIR)/color.o $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
BCS  = $(BCDIR)/breakout_em.bc $(OBJS:$(OBJDIR)/%.o=$(BCDIR)/%.bc)

GFX_DIR = SDL2_gfx-1.0.3
GFX_LIB_DIR = $(GFX_DIR)/.libs
GFX = $(GFX_LIB_DIR)/libSDL2_gfx.a

EMCFLAGS = -s TOTAL_MEMORY=67108864 -O3 -I $(GFX_DIR) -I $(INCDIR) -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1 -s USE_SDL=2 -s USE_SDL_TTF=2 --preload-file assets


LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_gfx

$(shell `mkdir -p $(OBJDIR) $(BCDIR)`)

.PHONY: all
all: $(TARGET)

breakout: $(TARGET) breakout.c
	$(CC) -L. $(CFLAGS) -o $@ $^ $(LDFLAGS) -l$(NAME) -lSDL2main


$(TARGET): $(OBJS)
	$(CC) -shared $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BCDIR)/%.bc: $(SRCDIR)/%.c $(INCS) Makefile
	$(EMCC) -MMD $(EMCFLAGS) -o $@ $<

$(BCDIR)/breakout_em.bc: breakout_em.c
	$(EMCC) -MMD $(EMCFLAGS) -o $@ $<

breakout_em: $(BCS) $(GFX)
	$(EMCC) --separate-asm -s EMTERPRETIFY_FILE=\'$@.bin\' $(EMCFLAGS) -o $@.html $^ $(GFX)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) Makefile
	$(CC) $(CFLAGS) -MMD -c -o $@ $< $(LDFLAGS)


$(SRCDIR)/color.c: $(SRCDIR)/color.gperf
	gperf --ignore-case -F",0" -Ct  $^  --output-file $@

$(GFX): 
	cd $(GFX_DIR); EMCONFIGURE_JS=1 $(EMCONF) ./configure --disable-mmx
	$(MAKE) -C $(GFX_DIR) all
    

-include $(wildcard $(OBJDIR)/*.d)
-include $(wildcard $(BCDIR)/*.d)

.PHONY: clean
clean:
	rm -f core $(TARGET) src/color.c breakout
	rm -f -r $(OBJDIR) $(BCDIR)
	rm -f breakout_em.js breakout_em.mem breakout_em.html
