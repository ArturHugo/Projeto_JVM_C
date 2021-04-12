#include "handlers/constants.h"
#include "frame.h"
#include "global.h"
#include "stack.h"

void nop(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  current_frame->local_pc++;
}

void aconst_null(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.reference_value = NULL;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void iconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (*instruction) - 3;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void lconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.long_value = (*instruction) - 9;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void fconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.float_value = (*instruction) - 11.0;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void dconst_n(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.double_value = (*instruction) - 14.0;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void bipush(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (instruction[1]) | ((instruction[1] & 0x80) ? 0xFFFFFF00 : 0);
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 2;
}

void sipush(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value =
      (instruction[1] << 8) | (instruction[2]) | ((instruction[1] & 0x80) ? 0xFFFF0000 : 0);
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 3;
}

void ldc(const u1* instruction) {
  Frame*            current_frame = peekNode(frame_stack);
  JavaType          value;
  ConstantPoolInfo* current_info = &(current_frame->constant_pool[instruction[1]]);
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
      value.reference_value = mapGet(method_area.loaded_classes, current_info->class_info._name);
      break;
    case CONSTANT_METHOD_TYPE:
      // TODO, ldc Method type não imlpementado ainda
      printf("ldc Method type não imlpementado ainda");
      break;
    case CONSTANT_METHOD_HANDLE:
      // TODO, ldc Method handle não imlpementado ainda
      printf("ldc Method type não imlpementado ainda");
      break;
    default:
      printf("ERRO: Instrução ldc aponta para campo de tipo inválido na constant pool.");
      exit(1);
  }
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 2;
}

void ldc_w(const u1* instruction) {}
void ldc_2_w(const u1* instruction) {}