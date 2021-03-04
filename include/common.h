#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define println(format, ...) printf(format "\n", ##__VA_ARGS__)

// Size specific data types
typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;

typedef struct {
  u1* buffer;
  int size;
  int seek;
} File;

#endif  // __COMMON_H