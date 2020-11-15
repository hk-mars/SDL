//
//  m_view.h
//  Rectangles
//
//  Created by TobyMars on 2020/11/14.
//

#ifndef m_view_h
#define m_view_h

#include <stdio.h>

#include "common.h"
#include "m_layout_json.h"

#define VIEW_NAME_LEN_MAX  20

typedef enum
{
    VIEW_OK,
    VIEW_ERR,
    VIEW_NULL,
    VIEW_NO_MEM,
} view_ret_t;

typedef enum
{
    VIEW_EVENT_OPEN = 0,
    VIEW_EVENT_CLOSING = 1,
    VIEW_EVENT_CLOSED = 2,
    VIEW_EVENT_UPDATE_DATA = 3,
    VIEW_EVENT_HIDE = 4,
    VIEW_EVENT_ENABLE = 5,
    VIEW_EVENT_DISABLE = 6,
    
    VIEW_EVENT_UNKNOWN,
} view_event_t;

typedef enum
{
    VIEW_STATE_INIT = 0,
    VIEW_STATE_OPEN = 1,
    VIEW_STATE_CLOSE = 2,
    VIEW_STATE_WORKING = 3,
    VIEW_STATE_SUSPEND = 4,
} view_state_t;

typedef struct
{
    char name[VIEW_NAME_LEN_MAX + 1];
    layout_json_t *layout;
    
    view_state_t state;
    
    bool enable;
    bool visible;
    
    
} view_t;

view_ret_t m_view_init(void);

view_t* m_view_create(char *name);

void m_view_show(view_t *view);

#endif /* m_view_h */
