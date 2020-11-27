//
//  mona_view.c
//  Rectangles
//
//  Created by TobyMars on 2020/11/14.
//

#include "mona_view.h"

#define X "view"
#define LOG_X(FORMAT, ARGS...)  \
{   \
printf("[%s] ", X); printf(FORMAT, ##ARGS); \
}


view_ret_t
mona_view_init(void)
{
    LOG_X("%s \n", __FUNCTION__);
    
    return VIEW_OK;
}

view_t*
mona_view_create(char *name)
{
    view_t *v = mona_malloc(sizeof(view_t));
    if (!v)
    {
        LOG_ERR("failed to malloc mem for view \n");
        return NULL;
    }
    
    v->layout = mona_layout_json_create();
    if (!v->layout)
    {
        LOG_ERR("failed to malloc mem for layout \n");
        mona_free(v);
        return NULL;
    }
    
    if (!name || strlen(name) == 0)
    {
        name = "i_view";
    }
  
    LOG_X("name max len: %lu \n", sizeof(v->name));
    snprintf(v->name, sizeof(v->name), "%s", name);
    
    v->enable = true;
    v->visible = true;
    v->state = VIEW_STATE_INIT;
    
    v->render.canvas = canvas_create();
    
    mona_view_debug(v);
    
    return v;
}

void
mona_view_debug(view_t *view)
{
    if (!view) return;
    
    LOG_BEGIN("");
    
    LOG_X("name: %s \n", view->name);
    LOG_X("enable: %d \n", view->enable);
    LOG_X("visible: %d \n", view->visible);
    
    LOG_END("");
}

bool
mona_view_layout_set_json(view_t *view, char *json)
{
    if (!view || !json)
    {
        return false;
    }
    
    view->layout->json = json;
    
    return true;
}

view_ret_t
mona_view_load(view_t *view)
{
    json_layout_ret_t rt;
    
    if (!view || !view->layout)
    {
        return VIEW_NULL;
    }
    
    rt  = mona_json_layout_parse(view->layout->json, view->layout);
    if (rt != JL_OK)
    {
        return rt;
    }
    
    return VIEW_OK;
}

view_ret_t
mona_view_present(view_t *view)
{
    json_layout_ret_t rt;
    
    if (!view) {
        return VIEW_NULL;
    }
    
    LOG_BEGIN("");
    
    canvas_obj_t obj;
    
//    canvas_set_obj(view->render.canvas, )
    
    canvas_sketch(view->render.canvas);
    
    LOG_END("");
    
    return VIEW_OK;
}


