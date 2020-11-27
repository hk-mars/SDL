//
//  mona_gal.h
//  Rectangles
//
//  Created by TobyMars on 2020/11/24.
//

#ifndef mona_gal_h
#define mona_gal_h

#include <stdio.h>
#include <stdint.h>

#include "mona_error.h"
#include "mona_sdl.h"

typedef struct
{
    char *fname;
    uint8_t *buf;
    
    int x;
    int y;
    int w;
    int h;
    
    /* format */
    
} gal_bmp_t;

mona_ret_t mona_gal_init(void);

mona_ret_t mona_gal_draw_bmp(gal_bmp_t *bmp);

#endif /* mona_gal_h */
