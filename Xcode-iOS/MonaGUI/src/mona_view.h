//
//  mona_view.h
//  Rectangles
//
//  Created by TobyMars on 2020/11/14.
//

#ifndef mona_view_h
#define mona_view_h

#include <stdio.h>

#include "mona_error.h"
#include "common.h"
#include "mona_layout_json.h"

#include "mona_canvas.h"


#define VIEW_NAME_LEN_MAX  20

typedef enum
{
    VIEW_OK = MONA_BASE_VIEW,
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
    canvas_t *canvas;
    
} render_t;

typedef struct
{
    char name[VIEW_NAME_LEN_MAX + 1];
    layout_json_t *layout;
    
    view_state_t state;
    
    bool enable;
    bool visible;
    
    render_t render;
    
} view_t;

view_ret_t mona_view_init(void);

view_t* mona_view_create(char *name);

void mona_view_debug(view_t *view);

bool mona_view_layout_set_json(view_t *view, char *json);

view_ret_t mona_view_load(view_t *view);

view_ret_t mona_view_present(view_t *view);

#endif /* mona_view_h */
