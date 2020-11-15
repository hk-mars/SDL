//
//  m_view.c
//  Rectangles
//
//  Created by TobyMars on 2020/11/14.
//

#include "m_view.h"

#define X "view"
#define LOG_X(FORMAT, ARGS...)  \
{   \
printf("[%s] ", X); printf(FORMAT, ##ARGS); \
}


view_ret_t
m_view_init(void)
{
    LOG_X("%s \n", __FUNCTION__);
    
    return VIEW_OK;
}

view_t*
m_view_create(char *name)
{
    view_t *v = mona_malloc(sizeof(view_t));
    if (!v)
    {
        LOG_ERR("failed to malloc mem for view \n");
        return NULL;
    }
    
    v->layout = m_layout_json_create();
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
    
    m_view_show(v);
    
    return v;
}

void
m_view_show(view_t *view)
{
    if (!view) return;
    
    LOG_BEGIN("");
    
    LOG_X("name: %s \n", view->name);
    LOG_X("enable: %d \n", view->enable);
    LOG_X("visible: %d \n", view->visible);
    
    LOG_END("");
}
