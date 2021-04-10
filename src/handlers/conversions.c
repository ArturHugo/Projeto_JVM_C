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
void to_float() {
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
void to_double() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->double_value = value->long_value;

  current_frame->local_pc++;
}

/*
 * Convert float to int
 *
 * opcode:	0x8b
 * format: 	[i2d]
 * stack: 	(..., value: float) -> (..., value: int)
 * description:	convert to IEEE 754 using round to nearest
 */
void to_int() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  /* ieee embassando o role 🙄🙄 */
  if ((value->int_value & 0x0F800000) == 0x0F800000) {
    if(value->int_value & 0x007FFFFF) {
      value->int_value = 0;
    } else if(value->long_value == 0x7F800000) /* inf */
      value->int_value = INT32_MAX;
    else if(value->long_value == 0xFF800000) /* -inf */
      value->int_value = INT32_MIN;
    }
  else {
    value->int_value = value->float_value;
  }

  current_frame->local_pc++;
}
