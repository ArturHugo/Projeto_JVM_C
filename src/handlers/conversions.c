#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/conversions.h"

void i2l() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->long_value = value->int_value;
  value->cat_tag    = CAT2;

  current_frame->local_pc++;
}

void i2f() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->float_value = value->int_value;

  current_frame->local_pc++;
}

void i2d() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->double_value = value->int_value;
  value->cat_tag      = CAT2;

  current_frame->local_pc++;
}

void l2i() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->long_value = value->int_value;
  value->cat_tag    = CAT2;

  current_frame->local_pc++;
}

void l2f() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->float_value = value->long_value;
  value->cat_tag     = CAT1;

  current_frame->local_pc++;
}

void l2d() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->double_value = value->long_value;

  current_frame->local_pc++;
}

void f2l(const u1* instruction) {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  int is_long = *instruction - 0x8b;

  /* Casos de borda para IEEE 754 */
  if((value->int_value & IEEE_MASK_F) == IEEE_MASK_F) {
    if(value->int_value & NAN_MASK_F) { /* NAN */
      value->int_value = 0;
    } else if(value->long_value == INF_F) /* inf */
      value->long_value = is_long ? INT64_MAX : INT32_MAX;
    else if(value->long_value == NEG_INF_F) /* -inf */
      value->long_value = is_long ? INT64_MIN : INT32_MIN;
  } else {
    value->long_value = value->float_value;
  }

  value->cat_tag = is_long ? CAT2 : CAT1;

  current_frame->local_pc++;
}

void f2d() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->double_value = value->float_value;

  current_frame->local_pc++;
}

void d2f() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->float_value = value->double_value;

  current_frame->local_pc++;
}

void d2l(const u1* instruction) {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  int is_long = *instruction - 0x8e;

  /* Casos de borda para IEEE 754 */
  if((value->long_value & IEEE_MASK_D) == IEEE_MASK_D) {
    if(value->long_value & NAN_MASK_D) { /* NaN */
      value->long_value = 0;
    } else if(value->long_value == INF_D) /* inf */
      value->long_value = is_long ? INT64_MAX : INT32_MAX;
    else if((uint64_t) value->long_value == NEG_INF_D) /* -inf */
      value->long_value = is_long ? INT64_MIN : INT32_MIN;
  } else {
    value->long_value = value->double_value;
  }

  value->cat_tag = is_long ? CAT2 : CAT1;

  current_frame->local_pc++;
}

void i2b() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->int_value = value->byte_value;

  current_frame->local_pc++;
}

void i2c() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->int_value = value->char_value;

  current_frame->local_pc++;
}

void i2s() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = peekNode(current_frame->operand_stack);

  value->int_value = value->short_value;

  current_frame->local_pc++;
}
