/*
 *  common.h
 *  written by Holmes Futrell
 *  use however you want
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define m_debug printf

#define bool unsigned char

extern int randomInt(int min, int max);
extern float randomFloat(float min, float max);
extern void fatalError(const char *string);
extern double updateDeltaTime(void);
