//
//  mona_sdl.c
//  mona
//
//  Created by TobyMars on 2020/11/26.
//

#include "mona_sdl.h"

#include "SDL.h"
#include "SDL_render.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Renderer *renderer;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480


#define BRUSH_SIZE 32           /* width and height of the brush */
#define PIXELS_PER_ITERATION 5  /* number of pixels between brush blots when forming a line */

static SDL_Texture *brush = 0;       /* texture for the brush */

static SDL_Texture *m_img_texture = NULL;

typedef struct
{
    int w;
    int h;
    
    SDL_Texture *texture;
} mona_texture_info_t;

/*
    draws a line from (startx, starty) to (startx + dx, starty + dy)
    this is accomplished by drawing several blots spaced PIXELS_PER_ITERATION apart
*/
void
draw_brush_line(SDL_Renderer *renderer, float startx, float starty, float dx, float dy)
{

    float distance = sqrt(dx * dx + dy * dy);   /* length of line segment (pythagoras) */
    int iterations = distance / PIXELS_PER_ITERATION + 1;       /* number of brush sprites to draw for the line */
    float dx_prime = dx / iterations;   /* x-shift per iteration */
    float dy_prime = dy / iterations;   /* y-shift per iteration */
    SDL_Rect dstRect;           /* rect to draw brush sprite into */
    float x;
    float y;
    int i;

    dstRect.w = BRUSH_SIZE;
    dstRect.h = BRUSH_SIZE;

    /* setup x and y for the location of the first sprite */
    x = startx - BRUSH_SIZE / 2.0f;
    y = starty - BRUSH_SIZE / 2.0f;

    /* draw a series of blots to form the line */
    for (i = 0; i < iterations; i++) {
        dstRect.x = x;
        dstRect.y = y;
        /* shift x and y for next sprite location */
        x += dx_prime;
        y += dy_prime;
        /* draw brush blot */
        SDL_RenderCopy(renderer, brush, NULL, &dstRect);
    }
}

static mona_texture_info_t m_texture_info;
static SDL_Texture*
load_texture_as_image(SDL_Renderer *renderer, const char *image_fpath)
{
    SDL_Surface *bmp_surface;
    bmp_surface = SDL_LoadBMP(image_fpath);
    if (bmp_surface == NULL) {
        LOG_ERR("could not load %s \n", image_fpath);
        return false;
    }
    
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, bmp_surface);
    if (t == 0) {
        LOG_ERR("could not create brush texture");
        SDL_FreeSurface(bmp_surface);
        return false;
    }
    
    /* additive blending -- laying strokes on top of eachother makes them brighter */
    SDL_SetTextureBlendMode(brush, SDL_BLENDMODE_ADD);
    /* set brush color (red) */
    SDL_SetTextureColorMod(brush, 0, 100, 0);
    
    m_texture_info.w = bmp_surface->w;
    m_texture_info.h = bmp_surface->h;
    
    SDL_FreeSurface(bmp_surface);
    
    return t;
}

/*
    loads the brush texture
*/
static bool
load_brush_texture(SDL_Renderer *renderer)
{
    SDL_Surface *bmp_surface;
    bmp_surface = SDL_LoadBMP("stroke.bmp");
    if (bmp_surface == NULL) {
        LOG_ERR("could not load stroke.bmp");
        return false;
    }
    
    brush =
        SDL_CreateTextureFromSurface(renderer, bmp_surface);
    SDL_FreeSurface(bmp_surface);
    if (brush == 0) {
        LOG_ERR("could not create brush texture");
        return false;
    }
    /* additive blending -- laying strokes on top of eachother makes them brighter */
    SDL_SetTextureBlendMode(brush, SDL_BLENDMODE_ADD);
    /* set brush color (red) */
    SDL_SetTextureColorMod(brush, 0, 100, 0);
    
    return true;
}

bool
mona_sdl_init(void)
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
//        //Create window
//        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
//        if( gWindow == NULL )
//        {
//            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
//            success = false;
//        }
//        else
//        {
//            //Get window surface
//            gScreenSurface = SDL_GetWindowSurface( gWindow );
//        }
        
        /* create main window and renderer */
        gWindow = SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(gWindow, 0, 0);

        int w, h;
        SDL_GetWindowSize(gWindow, &w, &h);
        SDL_RenderSetLogicalSize(renderer, w, h);

        /* load brush texture */
        load_brush_texture(renderer);

        /* fill canvass initially with all black */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    return success;
}


bool
mona_sdl_load_bmp(const char *fname)
{
    SDL_Texture *t = load_texture_as_image(renderer, fname);
    if(!t)
    {
        LOG_DEBUG("Unable to load image %s! SDL Error: %s \n", fname, SDL_GetError() );
        return false;
    }
    
    m_img_texture = t;
    return true;
}

void
mona_sdl_close(void)
{
    //Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void
mona_sdl_clear_screen(void)
{
    SDL_RenderClear(renderer);
}

void
mona_sdl_update_screen(void)
{
    LOG_BEGIN("");
    
#if MONA_SDL_CLEAR_SCREEN_BEFORE_UPDATE
    mona_sdl_clear_screen();
#endif
    
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = m_texture_info.w;
    dest.h = m_texture_info.h;
    LOG_DEBUG("w:%d, h:%d  \n", m_texture_info.w, m_texture_info.h);
    SDL_RenderCopy(renderer, m_img_texture, NULL, &dest);
    SDL_RenderPresent(renderer);
}

void
mona_sdl_brush(int x, int y)
{
    if (!brush)
    {
        if (!load_brush_texture(renderer))
        {
            return;
        }
    }
    
    draw_brush_line(renderer, x, y, BRUSH_SIZE, BRUSH_SIZE);
}


