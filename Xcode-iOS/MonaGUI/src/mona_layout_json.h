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

#ifndef mona_layout_json_h
#define mona_layout_json_h

#include <stdio.h>

#include "mona_error.h"
#include "mona_layout_obj.h"
#include "mona_layout_utils.h"

#define JSON_LAYOUT_DEBUG  1

typedef enum
{
    JL_OK = MONA_BASE_LAYOUT,
    JL_ERR,
    JL_NULL,
    JL_NO_MEM,
} json_layout_ret_t;

typedef struct
{
    char *json;
    
    char *view_name;
    
    layout_obj_list_t lst;
    
    int layer_cnt;
    int cur_layer;
} layout_json_t;

json_layout_ret_t mona_json_layout_parse(const char  *json, layout_json_t *layout);

layout_json_t* mona_layout_json_create(void);

#if JSON_LAYOUT_DEBUG
int mona_json_layout_test(void);
#endif

#endif /* mona_layout_json_h */
