//
//  mona_sdl.h
//  mona
//
//  Created by TobyMars on 2020/11/26.
//

#ifndef mona_sdl_h
#define mona_sdl_h

#include <stdio.h>

#include "common.h"

#define MONA_SDL_CLEAR_SCREEN_BEFORE_UPDATE  1

bool mona_sdl_init(void);

bool mona_sdl_load_bmp(const char *fname);

void mona_sdl_close(void);

void mona_sdl_clear_screen(void);
void mona_sdl_update_screen(void);

void mona_sdl_brush(int x, int y);

#endif /* mona_sdl_h */
