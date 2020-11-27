//
//  mona_canvas.h
//  Rectangles
//
//  Created by TobyMars on 2020/11/23.
//

#ifndef mona_canvas_h
#define mona_canvas_h

#include <stdio.h>

#include "common.h"
#include "mona_error.h"

typedef enum
{
    CANVAS_OK = MONA_BASE_CANVAS,
    CANVAS_ERR,
    CANVAS_NO_MEM,
} canvas_ret_t;

typedef enum
{
    CANVAS_OBJ_BUFF = 0,
    CANVAS_OBJ_IMAGE = 1,
    CANVAS_OBJ_FONT = 2,
    CANVAS_OBJ_TEXTURE_SHAPE = 3,
    CANVAS_OBJ_TEXTURE_ALPHA = 4,
    CANVAS_OBJ_TEXTURE_COLOR = 5,
    CANVAS_OBJ_MOVE_LINEAR = 6,
} canvas_obj_type_t;

typedef enum
{
    CANVAS_ALIGN_UNKNOWN = 0,
    CANVAS_ALIGN_LEFT_TOP = 1,
    CANVAS_ALIGN_LEFT_MIDDLE = 2,
    CANVAS_ALIGN_LEFT_BOTTOM = 3,
    CANVAS_ALIGN_RIGHT_TOP = 4,
    CANVAS_ALIGN_RIGHT_MIDDLE = 5,
    CANVAS_ALIGN_RIGHT_BOTTOM = 6,
    CANVAS_ALIGN_CENTER = 7,
    CANVAS_ALIGN_MAX_TYPE,
} canvas_align_t;

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    canvas_align_t align;
} layout_t;

typedef canvas_ret_t (*canvas_draw_t) (void*, void*);

typedef struct
{
    canvas_obj_type_t type;
    layout_t layout;
    unsigned char *buf;
    
    canvas_draw_t draw;
} canvas_obj_t;

typedef struct
{
    layout_t panel_layout;
    unsigned char *panel_buf;
    
    canvas_obj_t obj;
} canvas_t;


/*
pencil sketch
watercolor
oil painting
brush
crayon
Mona Lisa
The Last Supper
The Creation of Adam
Starry Sky
Screaming
The Persistence of Memory
Girl With a Pearl Earring
The Night Watch
A Picture Without a Beard
Guernica
pop 波普
dada 达达主义
conceptual 概念
minimalism 极简
cubism 立体主义
futurism 未来主义
pointillism 点彩画派
impressionism 印象派
expressionism 表现主义
constructionism 构成主义
abstract expression 抽象表现主义
 */

canvas_t* canvas_create(void);

canvas_ret_t canvas_set_obj(canvas_t *c, canvas_obj_t obj);

canvas_ret_t canvas_sketch(canvas_t *c);

#endif /* mona_canvas_h */
