//
//  m_widget.h
//  Rectangles
//
//  Created by TobyMars on 2020/11/1.
//

#ifndef m_widget_h
#define m_widget_h

#include <stdio.h>
#include "common.h"

typedef enum
{
    WIDGET_OK = 0,
    WIDGET_ERR = 1,
    WIDGET_NULL = 2,
    WIDGET_NO_MEM = 3,
} widget_ret_t;

typedef enum
{
    WIDGET_UNKNOWN = 0,
    WIDGET_OBJECT = 1,
    WIDGET_IMAGE = 2,
    
    WIDGET_MAX_TYPE,
} widget_type_t;

typedef struct
{
    int x;
    int y;
} widget_position_t;

typedef enum
{
    ALIGN_UNKNOWN = 0,
    ALIGN_LEFT_TOP = 1,
    ALIGN_LEFT_MIDDLE = 2,
    ALIGN_LEFT_BOTTOM = 3,
    ALIGN_RIGHT_TOP = 4,
    ALIGN_RIGHT_MIDDLE = 5,
    ALIGN_RIGHT_BOTTOM = 6,
    ALIGN_CENTER = 7,
    
    ALIGN_MAX_TYPE,
} widget_align_t;

typedef struct
{
    unsigned char *buf;
    int max_size;
} widget_texture_buf_t;

typedef struct
{
    uint32_t color;
    char *image;
    widget_position_t pos;
    int w;
    int h;
} widget_background_t;

typedef widget_ret_t (*widget_func_t) (void*);
typedef widget_ret_t (*widget_move_t) (void*, int);
typedef widget_ret_t (*widget_move_xy_t) (void*, int, int);

typedef struct
{
    char *name;
    widget_type_t type;
    
    widget_position_t pos;
    widget_align_t align;
    int w;
    int h;
    
    widget_background_t bg;
    widget_texture_buf_t *texture_buf;
    
    bool is_enable;
    bool is_visible;
    widget_func_t enable;
    widget_func_t disable;
    widget_func_t show;
    widget_func_t hide;
    
    widget_position_t offset_pos;
    widget_move_t move_x;
    widget_move_t move_y;
    widget_move_xy_t move_xy;
} widget_t;

#endif /* m_widget_h */
