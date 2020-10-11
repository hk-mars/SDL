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

#include "m_json_layout.h"
#include "cJSON.h"

#if JSON_LAYOUT_DEBUG
#define JL_DEBUG printf
#else
#define JL_DEBUG(...)
#endif

static int
parse_layer_obj(cJSON *obj)
{
    cJSON *item;
    
    JL_DEBUG("[layout] %s start \n", __FUNCTION__);

    item = cJSON_GetObjectItemCaseSensitive(obj, "widget");
    if (cJSON_IsString(item) && (item->valuestring != NULL))
    {
        JL_DEBUG("[layout] widget \"%s\"\n", item->valuestring);
    }
    
    item = cJSON_GetObjectItemCaseSensitive(obj, "type");
    if (cJSON_IsString(item) && (item->valuestring != NULL))
    {
        JL_DEBUG("[layout] type \"%s\"\n", item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(obj, "x");
    if (cJSON_IsNumber(item))
    {
        JL_DEBUG("[layout] x \"%d\"\n", item->valueint);
    }
    
    item = cJSON_GetObjectItemCaseSensitive(obj, "y");
    if (cJSON_IsNumber(item))
    {
        JL_DEBUG("[layout] y \"%d\"\n", item->valueint);
    }
    
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

int
m_json_layout_parse(char *layout)
{
    int status;
    cJSON *item;
    
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
      status = 0;
      goto end;
    }

    item = cJSON_GetObjectItemCaseSensitive(obj, "view");
    if (cJSON_IsString(item) && (item->valuestring != NULL))
    {
        JL_DEBUG("[layout] view \"%s\"\n", item->valuestring);
    }
    
    item = cJSON_GetObjectItemCaseSensitive(obj, "type");
    if (cJSON_IsString(item) && (item->valuestring != NULL))
    {
        JL_DEBUG("[layout] type \"%s\"\n", item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(obj, "layer");
    if (cJSON_IsArray(item))
    {
        JL_DEBUG("[layout] layer \n");
        
        parse_layer(item);
    }
    JL_DEBUG("[layout] %s, done \n", __FUNCTION__);
end:
    return status;
}


#if JSON_LAYOUT_DEBUG

static const char *layout_a = "{\n\
\t\"view\": \"view_logo\",\n\
\t\"type\": \"single\",\n\
\t\"layer\": [\n\
\t    {\n\
\t    \t\"widget\": \"img_logo\",\n\
\t    \t\"type\": \"image\",\n\
\t    \t\"x\": 0,\n\
\t    \t\"y\": 0,\n\
\t    \t\"algin\": \"center\"\n\
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

