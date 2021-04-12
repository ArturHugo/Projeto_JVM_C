#include <bits/stdint-intn.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/conversions.h"

/*
 * Convert int or long to float
 *
 * opcode:	0x86, 0x
 * format: 	[i2f/l2f]
 * stack: 	(..., value: integer) -> (..., value: float)
 * description:	convert to IEEE 754 using round to nearest
 */
void l2f() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->float_value = value->long_value;

  current_frame->local_pc++;
}

/*
 * Convert int or long to double
 *
 * opcode:	0x87, 0x
 * format: 	[i2d/l2d]
 * stack: 	(..., value: integer) -> (..., value: double)
 * description:	convert to IEEE 754 using round to nearest
 */
void l2d() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->double_value = value->long_value;

  current_frame->local_pc++;
}

/*
 * Convert float to int
 *
 * opcode:	0x8b, 0x8c
 * format: 	[f2i/f2l]
 * stack: 	(..., value: float) -> (..., value: int)
 * description:	convert to IEEE 754 using round to nearest
 */
void f2l(const u1* instruction) {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  int is_long = *instruction - 0x8b;

  /* ieee embassando o role 🙄🙄 */
  if((value->int_value & IEEE_MASK_F) == IEEE_MASK_F) {
    if(value->int_value & NAN_MASK_F) {
      value->int_value = 0;
    } else if(value->long_value == INF_F) /* inf */
      value->long_value = is_long ? INT64_MAX : INT32_MAX;
    else if(value->long_value == NEG_INF_F) /* -inf */
      value->long_value = is_long ? INT64_MIN : INT32_MIN;
  } else {
    value->long_value = value->float_value;
  }

  current_frame->local_pc++;
}

/*
 * Convert float to double
 *
 * opcode:	0x8d
 * format: 	[f2s]
 * stack: 	(..., value: float) -> (..., value: double)
 * description:	convert to double precision
 */
void f2d() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->double_value = value->float_value;

  current_frame->local_pc++;
}

/*
 * Convert double to float
 *
 * opcode:	0x90
 * format: 	[d2f]
 * stack: 	(..., value: double) -> (..., value: float)
 * description:	convert to double precision
 */
void d2f() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->float_value = value->double_value;

  current_frame->local_pc++;
}

/*
 * Convert double to int
 *
 * opcode:	0x8e, 0x8f
 * format: 	[f2i/f2l]
 * stack: 	(..., value: double) -> (..., value: int)
 * description:	convert to IEEE 754 using round to nearest
 */
void d2l(const u1* instruction) {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  int is_long = *instruction - 0x8e;

  /* ieee embassando o role 🙄🙄 */
  if((value->long_value & IEEE_MASK_D) == IEEE_MASK_D) {
    if(value->long_value & NAN_MASK_D) {
      value->long_value = 0;
    } else if(value->long_value == INF_D) /* inf */
      value->long_value = is_long ? INT64_MAX : INT32_MAX;
    else if((uint64_t) value->long_value == NEG_INF_D) /* -inf */
      value->long_value = is_long ? INT64_MIN : INT32_MIN;
  } else {
    value->long_value = value->double_value;
  }

  current_frame->local_pc++;
}

/*
 * Convert int to byte
 *
 * opcode:	0x91
 * format: 	[i2b]
 * stack: 	(..., value: int) -> (..., value: int)
 * description:	truncate int to a byte, then sign-extend
 */
void i2b() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->int_value = value->byte_value;

  current_frame->local_pc++;
}

/*
 * Convert int to char (uint16_t)
 *
 * opcode:	0x92
 * format: 	[i2c]
 * stack: 	(..., value: int) -> (..., value: int)
 * description:	truncate int to a byte, then 0-extend
 */
void i2c() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->int_value = value->char_value;

  current_frame->local_pc++;
}

/*
 * Convert int to byte
 *
 * opcode:	0x93
 * format: 	[i2s]
 * stack: 	(..., value: int) -> (..., value: int)
 * description:	truncate int to a short, then sign-extend
 */
void i2s() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->int_value = value->short_value;

  current_frame->local_pc++;
}
