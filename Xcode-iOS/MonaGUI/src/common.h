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

#define m_debug printf

#define mlog_err(FORMAT, ARGS...) \
    printf("[err] fun:%s line:%d, ", __FUNCTION__, __LINE__); \
    printf(FORMAT, ##ARGS)

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

