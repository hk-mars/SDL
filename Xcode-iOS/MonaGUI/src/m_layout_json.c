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

#include "common.h"

#if JSON_LAYOUT_DEBUG
#define JL_DEBUG(FORMAT, ARGS...) \
printf("[layout] "); printf(FORMAT, ##ARGS)
#else
#define JL_DEBUG(...)
#endif

static void
show_obj(cJSON *o, const char *name)
{
    if (!o || !name) return;
    
    if (cJSON_IsString(o) && (o->valuestring != NULL))
    {
        JL_DEBUG("%s \"%s\"\n", name, o->valuestring);
    }
    else if (cJSON_IsNumber(o))
    {
        JL_DEBUG("%s \"%d\"\n", name, o->valueint);
    }
    else
    {
        JL_DEBUG("%s undefined type \n", name);
    }
}

static cJSON*
parse_obj(cJSON *o, const char *name)
{
    o = cJSON_GetObjectItemCaseSensitive(o, name);
    show_obj(o, name);
    
    return o;
}

static json_layout_ret_t
parse_layer_obj(cJSON *obj, layout_obj_t *layout_obj)
{
    cJSON *o;
    const char *s = NULL;
    
    JL_DEBUG("%s start \n", __FUNCTION__);
    
    layout_obj->layer = 0;
    
    widget_list_t *lst = &layout_obj->widget_lst;
    
    /* create a new widget
     */
    widget_list_t *node = lst->next;
    while (node) {
        lst = node;
        node = node->next;
    }
    node = lst->next = mona_malloc(sizeof(widget_list_t));
    if (!node) {
        return JL_NO_MEM;
    }
    JL_DEBUG("a widget created \n");
    widget_t *w = &node->w;

    o = parse_obj(obj, "widget");
    if (o) w->name = o->valuestring;
    
    o = parse_obj(obj, "image");
    if (o) w->val_str = o->valuestring;
    
    o = parse_obj(obj, "x");
    if (o) w->pos.x = o->valueint;
    
    o = parse_obj(obj, "y");
    if (o) w->pos.y = o->valueint;
    
    o = parse_obj(obj, "align");
    if (o)
    {
        w->align_str = o->valuestring;
        w->align = layout_util_get_widget_align(w->align_str);
    }
    
    JL_DEBUG("%s done \n", __FUNCTION__);
    return JL_OK;
}

static json_layout_ret_t
parse_layer(cJSON *array, layout_json_t *layout)
{
    cJSON *item;
    layout_obj_list_t *lst = &layout->lst;
    
    /* create a new node
     */
    layout_obj_list_t *node = lst->next;
    if (node) {
        while (lst->next) {
            node = lst;
            lst = lst->next;
        }
    }
    node = mona_malloc(sizeof(layout_obj_list_t));
    if (!node) {
        return JL_NO_MEM;
    }
    JL_DEBUG("a layout object created \n");
    
    layout_obj_t *layout_obj = &node->obj;
    
    int size = cJSON_GetArraySize(array);;
    for (int i = 0; i < size; i++)
    {
        item =cJSON_GetArrayItem(array, i);
        if (!item) break;
        
        json_layout_ret_t rt = parse_layer_obj(item, layout_obj);
        if (rt != JL_OK) return rt;
    }
    
    return ;
}

json_layout_ret_t
m_json_layout_parse(const char *json, layout_json_t *layout)
{
    json_layout_ret_t rt = JL_OK;
    cJSON *o;
    
    if (!json || !layout) return JL_NULL;
    
    JL_DEBUG("%s:\n%s\n", __FUNCTION__, json);
    
    cJSON *obj = cJSON_Parse(json);
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
    if (o)
    {
        layout->view_name = o->string;
    }
    
    o = parse_obj(obj, "layer");
    if (o)
    {
        JL_DEBUG("[layout] layer \n");
        parse_layer(o, layout);
    }

    JL_DEBUG("%s, done \n", __FUNCTION__);
end:
    return rt;
}

layout_json_t*
m_layout_json_create(void)
{
    layout_json_t *layout = mona_malloc(sizeof(layout_json_t));
    if (!layout)
    {
        return NULL;
    }
    
    return layout;
}

#if JSON_LAYOUT_DEBUG

static const char *json_test = "{\n\
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

int
m_json_layout_test(void)
{
    layout_json_t *layout = m_layout_json_create();
    
    json_layout_ret_t rt = m_json_layout_parse(json_test, layout);
    
    return rt;
}

#endif /* JSON_LAYOUT_DEBUG */

