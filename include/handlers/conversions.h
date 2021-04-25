#ifndef __CONVERSIONS_H
#define __CONVERSIONS_H

#include "common.h"

/**
 * @brief handler for i2l instruction
 *
 * - - opcode:	0x85
 * - - format: 	[i2l]
 * - - stack: 	(..., value: integer) -> (..., value: long)
 * - - description:	convert to int to long
 */
void i2l();

/**
 * @brief handler for i2f instruction
 *
 * - - opcode:	0x86
 * - - format: 	[i2f]
 * - - stack: 	(..., value: integer) -> (..., value: float)
 * - - description:	convert to int to float
 */
void i2f();

/**
 * @brief handler for i2d instruction
 *
 * - opcode:	0x87
 * - format: 	[i2d]
 * - stack: 	(..., value: integer) -> (..., value: double)
 * - description:	convert to int to double
 */
void i2d();

/**
 * @brief handler for l2i instruction
 *
 * - opcode:	0x88
 * - format: 	[l2i]
 * - stack: 	(..., value: long) -> (..., value: int)
 * - description:	convert to long to int
 */
void l2i();

/**
 * @brief handler for l2f instruction
 *
 * - opcode:	0x89
 * - format: 	[l2f]
 * - stack: 	(..., value: long) -> (..., value: float)
 * - description:	convert to IEEE 754 using round to nearest
 */
void l2f();

/**
 * @brief handler for l2d instruction
 *
 * - opcode:	0x8a
 * - format: 	[l2d]
 * - stack: 	(..., value: long) -> (..., value: double)
 * - description:	convert to IEEE 754 using round to nearest
 */
void l2d();

/*
 * @brief handler for f2i and f2l instructions
 *
 * - opcode:	0x8b, 0x8c
 * - format: 	[f2i/f2l]
 * - stack: 	(..., value: float) -> (..., value: int)
 * - description:	convert to IEEE 754 using round to nearest
 */
void f2l(const u1* instruction);

/*
 * @brief handler for f2d instruction
 *
 * - opcode:	0x8d
 * - format: 	[f2d]
 * - stack: 	(..., value: float) -> (..., value: double)
 * - description:	convert to double precision
 */
void f2d();

/*
 * @brief handler for d2i and d2l instructions
 *
 * - opcode:	0x8e, 0x8f
 * - format: 	[d2i/d2l]
 * - stack: 	(..., value: double) -> (..., value: int)
 * - description:	convert to IEEE 754 using round to nearest
 */
void d2l(const u1* instruction);

/*
 * @brief handler for d2f instruction
 *
 * - opcode:	0x90
 * - format: 	[d2f]
 * - stack: 	(..., value: double) -> (..., value: float)
 * - description:	convert to double precision
 */
void d2f();

/*
 * @brief handler for i2b instruction
 *
 * - opcode:	0x91
 * - format: 	[i2b]
 * - stack: 	(..., value: int) -> (..., value: int)
 * - description:	truncate int to a byte, then sign-extend
 */
void i2b();

/*
 * @brief handler for i2c instruction
 *
 * - opcode:	0x92
 * - format: 	[i2c]
 * - stack: 	(..., value: int) -> (..., value: int)
 * - description:	truncate int to a char (uint16_t), then 0-extend
 */
void i2c();

/*
 * @brief handler for i2s instruction
 *
 * - opcode:	0x93
 * - format: 	[i2s]
 * - stack: 	(..., value: int) -> (..., value: int)
 * - description:	truncate int to a short, then sign-extend
 */
void i2s();

#endif  // __CONVERSIONS_H
