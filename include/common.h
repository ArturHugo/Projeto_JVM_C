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

#define EMPTY_TYPE          255
#define BYTE_TYPE           0
#define SHORT_TYPE          1
#define INT_TYPE            2
#define LONG_TYPE           3
#define CHAR_TYPE           4
#define FLOAT_TYPE          5
#define DOUBLE_TYPE         6
#define REFERENCE_TYPE      7
#define RETURN_ADDRESS_TYPE 8

#define IEEE_MASK_F 0x7F800000
#define IEEE_MASK_D 0x7FF0000000000000
#define INF_F       0x7F800000
#define INF_D       0x7FF0000000000000
#define NEG_INF_F   0xFF800000
#define NEG_INF_D   0xFFF0000000000000
#define NAN_MASK_F  0x007FFFFF
#define NAN_MASK_D  0x000FFFFFFFFFFFFF

#define CAT1 1
#define CAT2 2

typedef struct JavaType {
  u1 cat_tag;
  union {
    int8_t   byte_value;
    int16_t  short_value;
    int32_t  int_value;
    int64_t  long_value;
    uint16_t char_value;
    float    float_value;
    double   double_value;
    void*    reference_value;
    uint32_t return_address_value;
  };
} JavaType;

#endif  // __COMMON_H
