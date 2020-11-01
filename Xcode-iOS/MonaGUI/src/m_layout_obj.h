//
//  m_layout_obj.h
//  Rectangles
//
//  Created by TobyMars on 2020/10/25.
//

#ifndef m_layout_obj_h
#define m_layout_obj_h

#include <stdio.h>

#include "m_widget.h"

typedef struct
{
    widget_t w;
    widget_t *next;
} widget_list_t;

typedef struct
{
    widget_list_t *widget_lst;
    int widget_cnt;
    
    int layer;
} layout_obj_t;

typedef struct layout_obj_list
{
    layout_obj_t obj;
    struct layout_obj_list *next;
} layout_obj_list_t;

#endif /* m_layout_obj_h */
