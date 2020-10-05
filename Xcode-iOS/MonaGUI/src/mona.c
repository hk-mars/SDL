/*
 *  mona.c
 *  written by Toby M.
 *  it's free to use.
 */

#include "mona.h"
#include "SDL.h"
#include "SDL_opengles.h"
#include "common.h"
#include <math.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

char *create_monitor(void);
int supports_full_hd(const char * const monitor);

int
mona_init(void)
{
    printf("[mona] %s \n", __FUNCTION__);
    
    printf("Version: %s\n", cJSON_Version());
    
    return 0;
}
