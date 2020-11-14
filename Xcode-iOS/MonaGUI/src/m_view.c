//
//  m_view.c
//  Rectangles
//
//  Created by TobyMars on 2020/11/14.
//

#include "m_view.h"


view_ret_t
m_view_init(void)
{
    m_debug("[view] %s \n", __FUNCTION__);
    
    return VIEW_OK;
}

view_t*
m_view_create(char *name)
{
    view_t *v = mona_malloc(sizeof(view_t));
    if (!v)
    {
        mlog_err("failed to malloc mem for view \n");
        return NULL;
    }
    
    v->layout = m_layout_json_create();
    if (!v->layout)
    {
        mlog_err("failed to malloc mem for layout \n");
        mona_free(v);
        return NULL;
    }
    
    if (!name || strlen(name) == 0)
    {
        name = "i_view";
    }
  
    m_debug("name max len: %lu \n", sizeof(v->name));
    snprintf(v->name, sizeof(v->name), "%s", name);
    
    v->enable = true;
    v->visible = true;
    v->state = VIEW_STATE_INIT;
    
    return v;
}
