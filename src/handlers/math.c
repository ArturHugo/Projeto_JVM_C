#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/math.h"

void iadd() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value += value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;  // ver depois quantos bytes tem
}

void ladd() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value += value2.long_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void fadd() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.float_value += value2.float_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void dadd() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.double_value += value2.double_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void isub() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value -= value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lsub() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value -= value2.long_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void fsub() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.float_value -= value2.float_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void dsub() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.double_value -= value2.double_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void imul() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value *= value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lmul() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value *= value2.long_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void fmul() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.float_value *= value2.float_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void dmul() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.double_value *= value2.double_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void idiv() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value /= value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void ldiv_instruction() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value /= value2.long_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void fdiv() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.float_value /= value2.float_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void ddiv() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.double_value /= value2.double_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void irem() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value -= (value1.int_value / value2.int_value) * value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lrem() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value -= (value1.long_value / value2.long_value) * value2.long_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void frem() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.float_value -= (value1.float_value / value2.float_value) * value2.float_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void drem() {
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.double_value -= (value1.double_value / value2.double_value) * value2.double_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void ineg() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.int_value -= 2 * value.int_value;
  pushValue(&current_frame->operand_stack, value);
  current_frame->local_pc++;
}

void lneg() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.long_value -= 2 * value.long_value;
  pushValue(&current_frame->operand_stack, value);
  current_frame->local_pc++;
}

void fneg() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.float_value -= 2 * value.float_value;
  pushValue(&current_frame->operand_stack, value);
  current_frame->local_pc++;
}

void dneg() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.double_value -= 2 * value.double_value;
  pushValue(&current_frame->operand_stack, value);
  current_frame->local_pc++;
}

void ishl() {  // revisado
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value <<= value2.int_value & 0x1f;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lshl() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value *= 32;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void ishr() {  // revisado
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  // faz o shift de value1 em até value2 vezes, olhando ultimos 5 bits de value2
  value1.int_value >>= (value2.int_value & 0x1f);
  // compensa pelo c não fazer extensão de sinal no shift as vezes
  value1.int_value |=
      (value1.int_value & (1 << 31)) ? (0xFFFFFFFF) << (32 - (value2.int_value & 0x1f)) : 0;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lshr() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value /= 32;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void iushr() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value += value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lushr() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value += value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void iand() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value = value1.int_value && value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void land() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value = value1.long_value && value2.long_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void ior() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value = value1.int_value || value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lor() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.long_value = value1.long_value || value2.long_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void ixor() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value = value1.int_value ^ value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void lxor() {  // revisar no documento
  JavaType value1, value2;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value2);
  popValue(&current_frame->operand_stack, &value1);
  value1.int_value = value1.int_value ^ value2.int_value;
  pushValue(&current_frame->operand_stack, value1);
  current_frame->local_pc++;
}

void iinc(const u1* instruction) {  // revisado
  Frame* current_frame = peekNode(frame_stack);

  JavaType* local_variable_value = &(current_frame->local_variables[instruction[1]]);
  int32_t   value_to_increase    = (instruction[2]) | ((instruction[2] & 0x80) ? 0xFFFFFF00 : 0);

  local_variable_value->int_value += value_to_increase;

  current_frame->local_pc += 3;
}