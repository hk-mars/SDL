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
printf("[err] "); printf(FORMAT, ##ARGS)

#define bool unsigned char

void* mona_malloc(size_t size);
extern int randomInt(int min, int max);
extern float randomFloat(float min, float max);
extern void fatalError(const char *string);
extern double updateDeltaTime(void);

#endif /* COMMON_H */

