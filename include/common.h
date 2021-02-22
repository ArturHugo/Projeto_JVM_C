#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Size specific data types
typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;

// Functions to read .class file
u1 u1Read(FILE* fd);
u2 u2Read(FILE* fd);
u4 u4Read(FILE* fd);

#endif  // __COMMON_H