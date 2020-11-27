//
//  mona_sdl.c
//  mona
//
//  Created by TobyMars on 2020/11/26.
//

#include "mona_sdl.h"

#include "SDL.h"


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

/*
    draws a line from (startx, starty) to (startx + dx, starty + dy)
    this is accomplished by drawing several blots spaced PIXELS_PER_ITERATION apart
*/
void
drawLine(SDL_Renderer *renderer, float startx, float starty, float dx, float dy)
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

/*
    loads the brush texture
*/
static void
static load_brush_texture(SDL_Renderer *renderer)
{
    SDL_Surface *bmp_surface;
    bmp_surface = SDL_LoadBMP("stroke.bmp");
    if (bmp_surface == NULL) {
        LOG_ERR("could not load stroke.bmp");
    }
    brush =
        SDL_CreateTextureFromSurface(renderer, bmp_surface);
    SDL_FreeSurface(bmp_surface);
    if (brush == 0) {
        LOG_ERR("could not create brush texture");
    }
    /* additive blending -- laying strokes on top of eachother makes them brighter */
    SDL_SetTextureBlendMode(brush, SDL_BLENDMODE_ADD);
    /* set brush color (red) */
    SDL_SetTextureColorMod(brush, 255, 100, 100);
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
        gWindow = SDL_CreateWindow(NULL, 0, 0, 320, 480, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI);
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
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP(fname);
    if( gHelloWorld == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", fname, SDL_GetError() );
        success = false;
    }

    return success;
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
mona_sdl_update_screen(void)
{
    LOG_BEGIN("");
    
//    //Apply the image
//    SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
//
//    //Update the surface
//    SDL_UpdateWindowSurface(gWindow);
    
    int x, y, dx, dy;           /* mouse location          */
    Uint8 state;                /* mouse (touch) state */
    SDL_Event event;
    int done;                   /* does user want to quit? */
    int w, h;
    
//    done = 0;
//    while (!done && SDL_WaitEvent(&event)) {
//        switch (event.type) {
//        case SDL_QUIT:
//            done = 1;
//            break;
//        case SDL_MOUSEMOTION:
//            state = SDL_GetMouseState(&x, &y);  /* get its location */
//            LOG_DEBUG("x:%d, y:%d \n", x, y);
//            SDL_GetRelativeMouseState(&dx, &dy);        /* find how much the mouse moved */
//            if (state & SDL_BUTTON_LMASK) {     /* is the mouse (touch) down? */
//                drawLine(renderer, x - dx, y - dy, dx, dy);       /* draw line segment */
//                SDL_RenderPresent(renderer);
//            }
//            break;
//        }
//    }
    
    drawLine(renderer, 10, 10, 100, 100);       /* draw line segment */
    SDL_RenderPresent(renderer);
}

