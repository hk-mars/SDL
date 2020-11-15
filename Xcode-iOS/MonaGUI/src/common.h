/*
 *  common.h
 *  written by Holmes Futrell
 *  use however you want
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define LOG_DEBUG(FORMAT, ARGS...)  \
{   \
printf(FORMAT, ##ARGS); \
}

#define LOG_INFO(FORMAT, ARGS...)   \
{   \
printf("[info] [%s] [%d] ", __FUNCTION__, __LINE__);  \
printf(FORMAT, ##ARGS); \
}

#define LOG_ERR(FORMAT, ARGS...)    \
{   \
printf("[err] [%s] [%d] ", __FUNCTION__, __LINE__);  \
printf(FORMAT, ##ARGS); \
}

#define LOG_BEGIN(FORMAT, ARGS...)  \
{   \
printf("\n#### [%s] #### begin \n", __FUNCTION__);  \
printf(FORMAT, ##ARGS); \
}

#define LOG_END(FORMAT, ARGS...)  \
{   \
printf("\n#### [%s] #### end \n", __FUNCTION__);  \
printf(FORMAT, ##ARGS); \
}


#define bool unsigned char
#define true 1
#define false 0

void* mona_malloc(size_t size);
void mona_free(void *mem);

extern int randomInt(int min, int max);
extern float randomFloat(float min, float max);
extern void fatalError(const char *string);
extern double updateDeltaTime(void);

#endif /* COMMON_H */

