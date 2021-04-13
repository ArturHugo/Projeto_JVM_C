#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/math.h"

void iadd() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.int_value);
    popValue(&current_frame->operand_stack, value1.int_value);
    result.int_value = (int32_t)value1.int_value + (int32_t)value2.int_value;
    pushValue(&current_frame->operand_stack, result);
}

void ladd() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.long_value);
    popValue(&current_frame->operand_stack, value1.long_value);
    result.long_value = (int64_t)value1.long_value + (int64_t)value2.long_value;
    pushValue(&current_frame->operand_stack, result);
}

void fadd() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.float_value);
    popValue(&current_frame->operand_stack, &value1.float_value);
    result.float_value = (float)value1.float_value + (float)value2.float_value;
    pushValue(&current_frame->operand_stack, result);
}

void daad() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.double_value);
    popValue(&current_frame->operand_stack, &value1.double_value);
    result.double_value = (double)value1.double_value + (double)value2.double_value;
    pushValue(&current_frame->operand_stack, result);
}

void isub() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.int_value);
    popValue(&current_frame->operand_stack, value1.int_value);
    result.int_value = (int32_t)value1.int_value - (int32_t)value2.int_value;
    pushValue(&current_frame->operand_stack, result);
}

void lsub() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.long_value);
    popValue(&current_frame->operand_stack, value1.long_value);
    result.long_value = (int64_t)value1.long_value - (int64_t)value2.long_value;
    pushValue(&current_frame->operand_stack, result);
}

void fsub() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.float_value);
    popValue(&current_frame->operand_stack, &value1.float_value);
    result.float_value = (float)value1.float_value - (float)value2.float_value;
    pushValue(&current_frame->operand_stack, result);
}

void dsub() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.double_value);
    popValue(&current_frame->operand_stack, &value1.double_value);
    result.double_value = (double)value1.double_value - (double)value2.double_value;
    pushValue(&current_frame->operand_stack, result);
}

void imul() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.int_value);
    popValue(&current_frame->operand_stack, value1.int_value);
    result.int_value = (int32_t)value1.int_value * (int32_t)value2.int_value;
    pushValue(&current_frame->operand_stack, result);
}

void lmul() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.long_value);
    popValue(&current_frame->operand_stack, value1.long_value);
    result.long_value = (int64_t)value1.long_value * (int64_t)value2.long_value;
    pushValue(&current_frame->operand_stack, result);
}

void fmul() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.float_value);
    popValue(&current_frame->operand_stack, &value1.float_value);
    result.float_value = (float)value1.float_value * (float)value2.float_value;
    pushValue(&current_frame->operand_stack, result);
}

void dmul() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.double_value);
    popValue(&current_frame->operand_stack, &value1.double_value);
    result.double_value = (double)value1.double_value * (double)value2.double_value;
    pushValue(&current_frame->operand_stack, result);
}

void idiv() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.int_value);
    popValue(&current_frame->operand_stack, value1.int_value);
    result.int_value = (int32_t)value1.int_value / (int32_t)value2.int_value;
    pushValue(&current_frame->operand_stack, result);
}

void ldiv() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, value2.long_value);
    popValue(&current_frame->operand_stack, value1.long_value);
    result.long_value = (int64_t)value1.long_value / (int64_t)value2.long_value;
    pushValue(&current_frame->operand_stack, result);
}

void fdiv() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.float_value);
    popValue(&current_frame->operand_stack, &value1.float_value);
    result.float_value = (float)value1.float_value + (float)value2.float_value;
    pushValue(&current_frame->operand_stack, result);
}

void ddiv() {
    JavaType value1, value2, result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame->operand_stack, &value2.double_value);
    popValue(&current_frame->operand_stack, &value1.double_value);
    result.double_value = (double)value1.double_value + (double)value2.double_value;
    pushValue(&current_frame->operand_stack, result);
}

void irem() {}

void lrem() {}

void frem() {}

void drem() {}

void ineg() {}

void lneg() {}

void fneg() {}

void dneg() {}

void ishl() {}

void lshl() {}

void ishr() {}

void lshl() {}

void iushr() {}

void lushr() {}

void iand() {}

void land() {}

void ior() {}

void lor() {}

void ixor() {}

void lxor() {}

void iinc() {}