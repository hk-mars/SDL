//
//  mona_canvas.c
//  Rectangles
//
//  Created by TobyMars on 2020/11/23.
//

#include "mona_canvas.h"
#include "mona_gal.h"

canvas_t*
canvas_create(void)
{
    canvas_t *c = mona_malloc(sizeof(canvas_t));
    if (!c) return NULL;
    
    c->panel_layout.align = CANVAS_ALIGN_LEFT_TOP;
    
    return c;
}


canvas_ret_t
canvas_set_obj(canvas_t *c, canvas_obj_t obj)
{
    if (!c) return CANVAS_ERR;
    
    return CANVAS_OK;
}

canvas_ret_t
canvas_sketch(canvas_t *c)
{
    if (!c) return CANVAS_ERR;
    
    /* test */
    gal_bmp_t bmp;
    bmp.fname = "kromasky_16x16.bmp";
    mona_gal_draw_bmp(&bmp);
    
//    if (!c->obj.draw) {
//        LOG_ERR("draw function not defined \n");
//        return CANVAS_ERR;
//    }
//
//    c->obj.draw(c, &c->obj);
    
    return CANVAS_OK;
}
