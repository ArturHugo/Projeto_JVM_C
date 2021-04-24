#include "handlers/constants.h"
#include "frame.h"
#include "global.h"
#include "stack.h"

/**
 * format:  [nop]
 * stack:   (...) -> (...)
 * description: Do nothing.
 */
void nop() {
  Frame* current_frame = peekNode(frame_stack);
  current_frame->local_pc++;
}

/**
 * format:  [aconst_null]
 * stack:   (...) -> (..., null)
 * description: Push the null object reference onto the operand stack.
 */
void aconst_null() {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.reference_value = NULL;
  value.cat_tag         = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

/**
 * format:  [iconst_<i>]
 * stack:   (...) -> (..., <i>)
 * description: Push the int constant <i> (-1, 0, 1, 2, 3, 4 or 5) onto the operand
 * stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void iconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (*instruction) - 3;
  value.cat_tag   = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

/**
 * format:  [lconst_<l>]
 * stack:   (...) -> (..., <l>)
 * Push the long constant <l> (0 or 1) onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void lconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.long_value = (*instruction) - 9;
  value.cat_tag    = CAT2;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

/**
 * format:  [fconst_<f>]
 * stack:   (...) -> (..., <f>)
 * description: Push the float constant <f> (0.0, 1.0, or 2.0) onto the operand
 * stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void fconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.float_value = (*instruction) - 11.0;
  value.cat_tag     = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

/**
 * format:  [dconst_<d>]
 * stack:   (...) -> (..., <d>)
 * description: Push the double constant <d> (0.0 or 1.0) onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void dconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.double_value = (*instruction) - 14.0;
  value.cat_tag      = CAT2;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

/**
 * format:  [bipush, byte]
 * stack:   (...) -> (..., value)
 * description:  The immediate byte is sign-extended to an int value. That value
 * is pushed onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void bipush(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (instruction[1]) | ((instruction[1] & 0x80) ? 0xFFFFFF00 : 0);
  value.cat_tag   = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 2;
}

/**
 * format:  [sipush, byte1, byte2]
 * stack:   (...) -> (..., value)
 * description:  The immediate unsigned byte1 and byte2 values are assembled into
 * an intermediate short, where the value of the short is (byte1 <<
 * 8) | byte2. The intermediate value is then sign-extended to an int
 * value. That value is pushed onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void sipush(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value =
      (instruction[1] << 8) | (instruction[2]) | ((instruction[1] & 0x80) ? 0xFFFF0000 : 0);
  value.cat_tag = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 3;
}

/**
 * format:  [ldc, index]
 * stack:   (...) -> (..., value)
 * description:  Push item from run-time constant pool.
 *
 * format:  [ldc_w, indexbyte1, indexbyte2]
 * stack:   (...) -> (..., value)
 * description:  Push item from run-time constant pool (wide index).
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void ldc(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  u2       index       = instruction[1];
  u1       pc_increase = 2;
  u1       is_ldc_w    = 0;

  // if instruction is ldc_w
  if(instruction[0] == 0x13) {
    index = (instruction[1] << 8) | instruction[2];
    pc_increase++;
    is_ldc_w = 1;
  }

  ConstantPoolInfo* current_info = &(current_frame->constant_pool[index]);

  value.cat_tag         = CAT1;
  value.reference_value = NULL;

  switch(current_info->tag) {
    case CONSTANT_INTEGER:
      value.int_value = (int32_t)(current_info->integer_info.bytes);
      break;
    case CONSTANT_FLOAT:
      value.float_value = current_info->float_info._value;
      break;
    case CONSTANT_STRING:
      value.reference_value = current_info->string_info._value;
      break;
    case CONSTANT_CLASS:
      value.reference_value =
          mapGet(method_area.loaded_classes, (char*) (current_info->class_info._name));
      break;
    case CONSTANT_METHOD_TYPE:
      // TODO, ldc Method type not yet implemented
      printf("\npc = %d: ldc%s Method type not implemented",
             current_frame->local_pc,
             is_ldc_w ? "_w" : "");
      break;
    case CONSTANT_METHOD_HANDLE:
      // TODO, ldc Method handle not yet implemented
      printf("\npc = %d: ldc%s Method handle not implemented",
             current_frame->local_pc,
             is_ldc_w ? "_w" : "");
      break;
    default:
      printf("\npc = %d: ldc%s resolved to unsupported constant pool item\n",
             current_frame->local_pc,
             is_ldc_w ? "_w" : "");
      exit(1);
  }
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += pc_increase;
}

/**
 * format:  [ldc2_w, indexbyte1, indexbyte2]
 * stack:   (...) -> (..., value)
 * description:  Push long or double from run-time constant pool (wide index).
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void ldc2_w(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;

  ConstantPoolInfo* current_info =
      &(current_frame->constant_pool[(instruction[1] << 8) | instruction[2]]);

  value.cat_tag         = CAT2;
  value.reference_value = NULL;

  switch(current_info->tag) {
    case CONSTANT_LONG:
      value.long_value = current_info->long_info._value;
      break;

    case CONSTANT_DOUBLE:
      value.double_value = current_info->double_info._value;
      break;

    default:
      printf("\npc = %d: ldc_2_w resolved to unsupported constant pool item\n",
             current_frame->local_pc);
      exit(1);
  }
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 3;
}