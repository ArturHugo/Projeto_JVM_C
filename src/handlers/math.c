#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/math.h"


/*
 * Add two int values
 *
 * opcode: 0x60
 * format: [iadd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the sum
 */ 
void iadd() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value += value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Add two long values
 *
 * opcode: 0x61
 * format: [ladd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the sum
 */ 
void ladd() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value += value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Add two float values
 *
 * opcode: 0x62
 * format: [fadd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the sum
 */ 
void fadd() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.float_value += value2.float_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Add two double values
 *
 * opcode: 0x63
 * format: [dadd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the sum
 */ 
void dadd() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.double_value += value2.double_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Subtract one int value from another
 *
 * opcode: 0x64
 * format: [isub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the difference between them
 */ 
void isub() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value -= value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Subtract one long value from another
 *
 * opcode: 0x65
 * format: [lsub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the difference between them
 */ 
void lsub() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value -= value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Subtract one float value from another
 *
 * opcode: 0x66
 * format: [fsub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the difference between them
 */ 
void fsub() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.float_value -= value2.float_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Subtract one double value from another
 *
 * opcode: 0x67
 * format: [dsub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the difference between them
 */ 
void dsub() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.double_value -= value2.double_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Multiply two int values
 *
 * opcode: 0x68
 * format: [imul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the multiplication between them
 */ 
void imul() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value *= value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Multiply two long values
 *
 * opcode: 0x69
 * format: [lmul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the multiplication between them
 */  
void lmul() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value *= value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Multiply two float values
 *
 * opcode: 0x6a
 * format: [fmul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the multiplication between them
 */  
void fmul() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.float_value *= value2.float_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Multiply two double values
 *
 * opcode: 0x6b
 * format: [dmul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the multiplication between them
 */  
void dmul() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.double_value *= value2.double_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Divide one int value from another
 *
 * opcode: 0x6c
 * format: [idiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the division between them
 */ 
void idiv() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value /= value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Divide one long value from another
 *
 * opcode: 0x6d
 * format: [ldiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the division between them
 */ 
void ldiv_instruction() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value /= value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Divide one float value from another
 *
 * opcode: 0x6e
 * format: [fdiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the division between them
 */ 
void fdiv() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.float_value /= value2.float_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Divide one double value from another
 *
 * opcode: 0x6f
 * format: [ddiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the division between them
 */ 
void ddiv() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.double_value /= value2.double_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Calculate the remainder from an int division
 *
 * opcode: 0x70
 * format: [irem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the remainder from their division
 */ 
void irem() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value -= (value1.int_value / value2.int_value) * value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Calculate the remainder from a long division
 *
 * opcode: 0x71
 * format: [lrem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the remainder from their division
 */ 
void lrem() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value -= (value1.long_value / value2.long_value) * value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Calculate the remainder from a float division
 *
 * opcode: 0x72
 * format: [frem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the remainder from their division
 */ 
void frem() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.float_value -= ((int)(value1.float_value / value2.float_value)) * value2.float_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Calculate the remainder from a double division
 *
 * opcode: 0x73
 * format: [drem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the remainder from their division
 */ 
void drem() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.double_value -= ((long long)(value1.double_value / value2.double_value)) * value2.double_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Calculate the opposite from an int value
 *
 * opcode: 0x74
 * format: [ineg]
 * stack: (..., value) -> (..., result)
 * description: pop one int value from the top of the stack and push their opposite
 */ 
void ineg() {
  JavaType value;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value);
  value.int_value -= 2 * value.int_value;
  pushValue(&current_frame -> operand_stack, value);
  current_frame -> local_pc ++;
}

/*
 * Calculate the opposite from a long value
 *
 * opcode: 0x75
 * format: [lneg]
 * stack: (..., value) -> (..., result)
 * description: pop one long value from the top of the stack and push their opposite
 */ 
void lneg() {
  JavaType value;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value);
  value.long_value -= 2 * value.long_value;
  pushValue(&current_frame -> operand_stack, value);
  current_frame -> local_pc ++;
}

/*
 * Calculate the opposite from a float value
 *
 * opcode: 0x76
 * format: [fneg]
 * stack: (..., value) -> (..., result)
 * description: pop one float value from the top of the stack and push their opposite
 */ 
void fneg() {
  JavaType value;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value);
  value.float_value -= 2 * value.float_value;
  pushValue(&current_frame -> operand_stack, value);
  current_frame -> local_pc ++;
}

/*
 * Calculate the opposite from an double value
 *
 * opcode: 0x77
 * format: [dneg]
 * stack: (..., value) -> (..., result)
 * description: pop one double value from the top of the stack and push their opposite
 */ 
void dneg() {
  JavaType value;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value);
  value.double_value -= 2 * value.double_value;
  pushValue(&current_frame -> operand_stack, value);
  current_frame -> local_pc ++;
}

/*
 * Shift an int value left with the low 5 bits from another int value
 *
 * opcode: 0x78
 * format: [ishl]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push one of them left shifted with the low 5 bits from the other
 */ 
void ishl() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value <<= (value2.int_value & 0x1f);
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Shift a long value left with the low 6 bits from another long value
 *
 * opcode: 0x79
 * format: [lshl]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push one of them left shifted with the low 6 bits from the other
 */
void lshl() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value <<= (value2.long_value & 0x3f);
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Shift an int value right with the low 5 bits from another int value
 *
 * opcode: 0x7a
 * format: [ishr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void ishr() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value >>= (value2.int_value & 0x1f);
  value1.int_value |=
      (value1.int_value & (1 << 31)) ? (0xFFFFFFFF) << (32 - (value2.int_value & 0x1f)) : 0;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Shift a long value right with the low 5 bits from another long value
 *
 * opcode: 0x7b
 * format: [lshr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void lshr() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value >>= (value2.long_value & 0x3f);
  value1.long_value |=
      (value1.long_value & (1 << 63)) ? (0xFFFFFFFFFFFFFFFF) << (64 - (value2.long_value & 0x3f)) : 0;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Shift an int value right with the low 5 bits from another int value with zero extension
 *
 * opcode: 0x7c
 * format: [iushr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void iushr() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value >>= (value2.int_value & 0x1f);
  value1.int_value &= (uint32_t)(0xFFFFFFFF) >> (value2.int_value & 0x1f);
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Shift a long value right with the low 5 bits from another long value with zero extension
 *
 * opcode: 0x7d
 * format: [lushr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void lushr() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value >>= (value2.long_value & 0x3f);
  value1.long_value &= (uint64_t)(0xFFFFFFFFFFFFFFFF) >> (value2.long_value & 0x3f);
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Take the bitwise AND conjunction from two int values
 *
 * opcode: 0x7e
 * format: [iand]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the bitwise AND conjunction between them
 */ 
void iand() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value = value1.int_value & value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Take the bitwise AND conjunction from two long values
 *
 * opcode: 0x7f
 * format: [land]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the bitwise AND conjunction between them
 */ 
void land() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value = value1.long_value & value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Take the bitwise OR conjunction from two int values
 *
 * opcode: 0x80
 * format: [ior]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the bitwise OR conjunction between them
 */ 
void ior() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value = value1.int_value | value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Take the bitwise OR conjunction from two long values
 *
 * opcode: 0x81
 * format: [lor]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the bitwise OR conjunction between them
 */ 
void lor() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value = value1.long_value | value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Take the bitwise XOR conjunction from two int values
 *
 * opcode: 0x82
 * format: [ixor]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the bitwise XOR conjunction between them
 */ 
void ixor() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.int_value = value1.int_value ^ value2.int_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Take the bitwise XOR conjunction from two long values
 *
 * opcode: 0x83
 * format: [lxor]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the bitwise XOR conjunction between them
 */ 
void lxor() {
  JavaType value1, value2;
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame -> operand_stack, &value2);
  popValue(&current_frame -> operand_stack, &value1);
  value1.long_value = value1.long_value ^ value2.long_value;
  pushValue(&current_frame -> operand_stack, value1);
  current_frame -> local_pc ++;
}

/*
 * Increment local variable from constant
 *
 * opcode: 0x84
 * format: [iinc]
 * stack: (..., const, index, iinc)
 * description: increment the local variable in index with the const value
 */ 
void iinc(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  JavaType* local_variable_value = &(current_frame -> local_variables[instruction[1]]);
  // int32_t value_to_increase = (instruction[2]) | ((instruction[2] & 0x80) ? 0xFFFFFF00 : 0);
  local_variable_value -> int_value += (int8_t)(instruction[2]);
  current_frame -> local_pc += 3;
}