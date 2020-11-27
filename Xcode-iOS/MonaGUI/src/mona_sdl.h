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

bool mona_sdl_init(void);

bool mona_sdl_load_bmp(const char *fname);

void mona_sdl_close(void);

void mona_sdl_update_screen(void);

#endif /* mona_sdl_h */
