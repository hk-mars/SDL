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

#include "m_layout_json.h"
#include "cJSON.h"

#if JSON_LAYOUT_DEBUG
#define JL_DEBUG printf
#else
#define JL_DEBUG(...)
#endif

static void
show_obj(cJSON *o, const char *name)
{
    if (!o || !name) return;
    
    if (cJSON_IsString(o) && (o->valuestring != NULL))
    {
        JL_DEBUG("[layout] %s \"%s\"\n", name, o->valuestring);
    }
    else if (cJSON_IsNumber(o))
    {
        JL_DEBUG("[layout] %s \"%d\"\n", name, o->valueint);
    }
}

static cJSON*
parse_obj(cJSON *o, const char *name)
{
    o = cJSON_GetObjectItemCaseSensitive(o, name);
    show_obj(o, name);
    
    return o;
}

static int
parse_layer_obj(cJSON *obj)
{
    cJSON *o;
    const char *s = NULL;
    
    JL_DEBUG("[layout] %s start \n", __FUNCTION__);

    o = parse_obj(obj, "widget");
    o = parse_obj(obj, "image");
    o = parse_obj(obj, "x");
    o = parse_obj(obj, "y");
    o = parse_obj(obj, "align");
    
    JL_DEBUG("[layout] %s done \n", __FUNCTION__);
    return 1;
}

static int
parse_layer(cJSON *array)
{
    cJSON *item;
    
    int size = cJSON_GetArraySize(array);;
    for (int i = 0; i < size; i++)
    {
        item =cJSON_GetArrayItem(array, i);
        if (!item) break;
        
        parse_layer_obj(item);
    }
    
    return 1;
}

json_layout_ret_t
m_json_layout_parse(char *layout)
{
    json_layout_ret_t rt = JS_OK;
    cJSON *o;
    
    
    if (!layout) return 0;
    
    JL_DEBUG("[layout] %s:\n%s\n", __FUNCTION__, layout);
    
    cJSON *obj = cJSON_Parse(layout);
    if (!obj)
    {
      const char *error_ptr = cJSON_GetErrorPtr();
      if (error_ptr)
      {
          fprintf(stderr, "error before: %s\n", error_ptr);
      }
      rt = JL_ERR;
      goto end;
    }

    o = parse_obj(obj, "view");
    o = parse_obj(obj, "layer");
    if (o)
    {
        JL_DEBUG("[layout] layer \n");
        parse_layer(o);
    }

    JL_DEBUG("[layout] %s, done \n", __FUNCTION__);
end:
    return rt;
}


#if JSON_LAYOUT_DEBUG

static const char *layout_a = "{\n\
\t\"view\": \"view_logo\",\n\
\t\"layer\": [\n\
\t    {\n\
\t    \t\"widget\": \"img_logo\",\n\
\t    \t\"type\": \"image\",\n\
\t    \t\"image\": \"logo\",\n\
\t    \t\"x\": 2,\n\
\t    \t\"y\": 2,\n\
\t    \t\"algin\": \"center\",\n\
\t    \t\"bg\": \"gray\",\n\
\t    \t\"motion_effect\": \"slide\"\n\
\t    }\n\
\t]\n\
}";

int
m_json_layout_test(void)
{
    int pass;
    
    pass = m_json_layout_parse((char*)layout_a);
    
    return pass;
}

#endif /* JSON_LAYOUT_DEBUG */

