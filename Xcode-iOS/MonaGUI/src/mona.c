/*
  Copyright (c) 2020-2030 Toby M.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
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
#include "mona_error.h"
#include "mona_layout_json.h"
#include "mona_view.h"

#define X "mona"
#define LOG_X(FORMAT, ARGS...)  \
{   \
printf("[%s] ", X); printf(FORMAT, ##ARGS); \
}


char *create_monitor(void);
int supports_full_hd(const char * const monitor);


static const char *json_x = "{\n\
\t\"view\": \"view_logo\",\n\
\t\"layer\": [\n\
\t    {\n\
\t    \t\"widget\": \"img_logo\",\n\
\t    \t\"type\": \"image\",\n\
\t    \t\"image\": \"logo\",\n\
\t    \t\"x\": 2,\n\
\t    \t\"y\": 2,\n\
\t    \t\"align\": \"center\",\n\
\t    \t\"bg\": \"gray\",\n\
\t    \t\"motion_effect\": \"slide\"\n\
\t    }\n\
\t]\n\
}";


char*
mona_version(void)
{
    static char version[15];
    snprintf(version, 15, "%i.%i.%i", MONA_VER_MAJOR, MONA_VER_MINOR, MONA_VER_PATCH);

    return version;
}

mona_ret_t
mona_init(void)
{
    LOG_X("mona gui framework %s \n", mona_version());
    
    LOG_X("cJSON %s\n", cJSON_Version());
    
    mona_ret_t rt = mona_view_init();
    if (rt != VIEW_OK)
    {
        return rt;
    }
    
    view_t *view = mona_view_create("my_view");
    if (!view)
    {
        return rt;
    }
    
    mona_view_layout_set_json(view, (char*)json_x);
    
    rt = mona_view_load(view);
    if (rt != VIEW_OK)
    {
        return rt;
    }

    
    return MONA_OK;
}
