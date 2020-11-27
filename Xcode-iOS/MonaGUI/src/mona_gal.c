//
//  mona_gal.c
//  Rectangles
//
//  Created by TobyMars on 2020/11/24.
//

#include "mona_gal.h"

#include "SDL.h"
#include "mona_error.h"
#include "common.h"


#if 0
void
drawGlyph(int glyph, int positionIndex)
{
    int x, y;
    getPositionForCharNumber(positionIndex, &x, &y);
    SDL_Rect srcRect = { GLYPH_SIZE_IMAGE * glyph, 0, GLYPH_SIZE_IMAGE, GLYPH_SIZE_IMAGE };
    SDL_Rect dstRect = { x, y, GLYPH_SIZE_SCREEN, GLYPH_SIZE_SCREEN };
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

/* this function loads our font into an SDL_Texture and returns the SDL_Texture  */
SDL_Texture*
loadFont(void)
{
    SDL_Surface *surface = SDL_LoadBMP("kromasky_16x16.bmp");

    if (!surface) {
        printf("Error loading bitmap: %s\n", SDL_GetError());
        return 0;
    } else {
        /* set the transparent color for the bitmap font (hot pink) */
        SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, 238, 0, 252));
        /* now we convert the surface to our desired pixel format */
        int format = SDL_PIXELFORMAT_ABGR8888;  /* desired texture format */
        Uint32 Rmask, Gmask, Bmask, Amask;      /* masks for desired format */
        int bpp;                /* bits per pixel for desired format */
        SDL_PixelFormatEnumToMasks(format, &bpp, &Rmask, &Gmask, &Bmask,
                                   &Amask);
        SDL_Surface *converted =
            SDL_CreateRGBSurface(0, surface->w, surface->h, bpp, Rmask, Gmask,
                                 Bmask, Amask);
        SDL_BlitSurface(surface, NULL, converted, NULL);
        /* create our texture */
        texture = SDL_CreateTextureFromSurface(renderer, converted);
        if (texture == 0) {
            printf("texture creation failed: %s\n", SDL_GetError());
        } else {
            /* set blend mode for our texture */
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        }
        SDL_FreeSurface(surface);
        SDL_FreeSurface(converted);
        return texture;
    }
}

void
draw()
{
    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(renderer);

    for (int i = 0; i < numChars; i++) {
        drawGlyph(glyphs[i], i);
    }

    drawGlyph(29, numChars); /* cursor is at index 29 in the bitmap font */

    SDL_RenderPresent(renderer);
}
#endif


#define TEST_INPUT_RECT

#define GLYPH_SIZE_IMAGE 16     /* size of glyphs (characters) in the bitmap font file */
#define GLYPH_SIZE_SCREEN 32    /* size of glyphs (characters) as shown on the screen */

#define MAX_CHARS 1024

static SDL_Texture *texture; /* texture where we'll hold our font */

static SDL_Renderer *renderer;
static int numChars = 0;        /* number of characters we've typed so far */
static SDL_Color bg_color = { 50, 50, 100, 255 };       /* color of background */

static int glyphs[MAX_CHARS];

/*
    This function returns and x,y position for a given character number.
    It is used for positioning each character of text
*/
static void
getPositionForCharNumber(int n, int *x, int *y)
{
    int renderW, renderH;
    SDL_RenderGetLogicalSize(renderer, &renderW, &renderH);

    int x_padding = 16;         /* padding space on left and right side of screen */
    int y_padding = 32;         /* padding space at top of screen */
    /* figure out the number of characters that can fit horizontally across the screen */
    int max_x_chars = (renderW - 2 * x_padding) / GLYPH_SIZE_SCREEN;
    int line_separation = 5;    /* pixels between each line */
    *x = (n % max_x_chars) * GLYPH_SIZE_SCREEN + x_padding;
#ifdef TEST_INPUT_RECT
    *y = renderH - GLYPH_SIZE_SCREEN;
#else
    *y = (n / max_x_chars) * (GLYPH_SIZE_SCREEN + line_separation) + y_padding;
#endif
}

static void
drawGlyph(int glyph, int positionIndex)
{
    int x, y;
    getPositionForCharNumber(positionIndex, &x, &y);
    SDL_Rect srcRect = { GLYPH_SIZE_IMAGE * glyph, 0, GLYPH_SIZE_IMAGE, GLYPH_SIZE_IMAGE };
    SDL_Rect dstRect = { x, y, GLYPH_SIZE_SCREEN, GLYPH_SIZE_SCREEN };
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

// The window we'll be rendering to
static SDL_Window* gWindow = NULL;
    
// The surface contained by the window
static SDL_Surface* gScreenSurface = NULL;

static SDL_Surface *m_surface = NULL;

mona_ret_t
mona_gal_init(void)
{
    LOG_BEGIN("");
    
    mona_sdl_init();
    
    LOG_END("");
    
    return MONA_OK;
}

mona_ret_t
mona_gal_draw_bmp(gal_bmp_t *bmp)
{
    if (!bmp) return MONA_NULL;
    
    LOG_BEGIN("");
    
    bool ok = mona_sdl_load_bmp(bmp->fname);
    if (!ok) return MONA_ERR;
    
    mona_sdl_update_screen();
    
//    m_surface = SDL_LoadBMP("kromasky_16x16.bmp");
//    if (!m_surface) {
//        printf("Error loading bitmap: %s\n", SDL_GetError());
//        return MONA_ERR;
//    }
    
//    /* set the transparent color for the bitmap font (hot pink) */
//    SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, 238, 0, 252));
//    /* now we convert the surface to our desired pixel format */
//    int format = SDL_PIXELFORMAT_ABGR8888;  /* desired texture format */
//    Uint32 Rmask, Gmask, Bmask, Amask;      /* masks for desired format */
//    int bpp;                /* bits per pixel for desired format */
//    SDL_PixelFormatEnumToMasks(format, &bpp, &Rmask, &Gmask, &Bmask,
//                               &Amask);
//    SDL_Surface *converted =
//        SDL_CreateRGBSurface(0, surface->w, surface->h, bpp, Rmask, Gmask,
//                             Bmask, Amask);
//    SDL_BlitSurface(surface, NULL, converted, NULL);
//    /* create our texture */
//    texture = SDL_CreateTextureFromSurface(renderer, converted);
//    if (texture == 0) {
//        printf("texture creation failed: %s\n", SDL_GetError());
//    } else {
//        /* set blend mode for our texture */
//        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//    }
//    SDL_FreeSurface(surface);
//    SDL_FreeSurface(converted);
////    return texture;
//
//    SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
//    SDL_RenderClear(renderer);
//
//    for (int i = 0; i < numChars; i++) {
//        drawGlyph(glyphs[i], i);
//    }
//
//    drawGlyph(29, numChars); /* cursor is at index 29 in the bitmap font */
//
//    SDL_RenderPresent(renderer);
    
    LOG_END("");
    
    return MONA_OK;
}
