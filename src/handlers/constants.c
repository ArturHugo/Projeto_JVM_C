#include "handlers/constants.h"
#include "frame.h"
#include "global.h"
#include "stack.h"

void nop() {
  Frame* current_frame = peekNode(frame_stack);
  current_frame->local_pc++;
}

void aconst_null() {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.reference_value = NULL;
  value.cat_tag         = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void iconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (*instruction) - 3;
  value.cat_tag   = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void lconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.long_value = (*instruction) - 9;
  value.cat_tag    = CAT2;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void fconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.float_value = (*instruction) - 11.0;
  value.cat_tag     = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void dconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.double_value = (*instruction) - 14.0;
  value.cat_tag      = CAT2;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void bipush(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (instruction[1]) | ((instruction[1] & 0x80) ? 0xFFFFFF00 : 0);
  value.cat_tag   = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 2;
}

void sipush(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value =
      (instruction[1] << 8) | (instruction[2]) | ((instruction[1] & 0x80) ? 0xFFFF0000 : 0);
  value.cat_tag = CAT1;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 3;
}

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
  // TODO checar se o indice é valido

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

void ldc_2_w(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;

  ConstantPoolInfo* current_info =
      &(current_frame->constant_pool[(instruction[1] << 8) | instruction[2]]);

  value.cat_tag         = CAT2;
  value.reference_value = NULL;
  // TODO checar se o indice é valido

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