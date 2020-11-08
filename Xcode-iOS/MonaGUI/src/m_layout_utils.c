//
//  m_layout_utils.c
//  Rectangles
//
//  Created by TobyMars on 2020/11/8.
//

#include "m_layout_utils.h"


typedef struct
{
    char *name;
    widget_align_t type;
} align_info_t;

widget_align_t
layout_util_get_widget_align(char *name)
{
    widget_align_t type;
    align_info_t align_lst[] =
    {
        { "left top", ALIGN_LEFT_TOP },
        { "left middle", ALIGN_LEFT_MIDDLE },
        { "left bottom", ALIGN_LEFT_BOTTOM },
        { "right top", ALIGN_RIGHT_TOP },
        { "right middle", ALIGN_RIGHT_MIDDLE },
        { "right bottom", ALIGN_RIGHT_BOTTOM },
        { "center", ALIGN_CENTER },
        
        /* optional
         */
        { "left_top", ALIGN_LEFT_TOP },
        { "left_middle", ALIGN_LEFT_MIDDLE },
        { "left_bottom", ALIGN_LEFT_BOTTOM },
        { "right_top", ALIGN_RIGHT_TOP },
        { "right_middle", ALIGN_RIGHT_MIDDLE },
        { "right_bottom", ALIGN_RIGHT_BOTTOM },
    };
    
    int len = sizeof(align_lst) / sizeof(align_lst[0]);
    for (int i = 0; i < len; i++)
    {
        if (!strcasecmp(align_lst[i].name, name))
        {
            return align_lst[i].type;
        }
    }
    
    return ALIGN_UNKNOWN;
}
