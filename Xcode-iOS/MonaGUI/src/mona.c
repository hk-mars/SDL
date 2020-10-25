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
#include "m_layout_json.h"

char *create_monitor(void);
int supports_full_hd(const char * const monitor);

int
mona_init(void)
{
    printf("[mona] %s \n", __FUNCTION__);
    
    printf("Version: %s\n", cJSON_Version());
    
    m_json_layout_test();
    
    return 0;
}
