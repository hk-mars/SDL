//
//  mona_error.h
//  Rectangles
//
//  Created by TobyMars on 2020/11/21.
//

#ifndef mona_error_h
#define mona_error_h

#include <stdio.h>

#define MONA_OK             0x00
#define MONA_ERR            0x01
#define MONA_NULL           0x02
#define MONA_NO_MEM         0x03
#define MONA_TIMEOUT        0x04
#define MONA_DRAW_DELAY     0x05
#define MONA_BASE_VIEW      0x100
#define MONA_BASE_LAYOUT    0x200
#define MONA_BASE_WIDGET    0x300
typedef unsigned int mona_ret_t;

#endif /* mona_error_h */
