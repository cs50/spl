#ifndef INLINE
#   if __GNUC__ && !__GNUC_STDC_INLINE__
#       define INLINE extern inline
#   else
#       define INLINE inline
#  endif
#endif

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdint.h>
#include <stdlib.h>

INLINE void requiresFonts() {
    if (!TTF_WasInit()) {
        TTF_Init();
        atexit(TTF_Quit);
    }
}

INLINE void requiresSubsystem(int32_t systems) {
    if (!SDL_WasInit(SDL_INIT_EVERYTHING)) {
        atexit(SDL_Quit);
    }
    SDL_InitSubSystem(systems);
}
