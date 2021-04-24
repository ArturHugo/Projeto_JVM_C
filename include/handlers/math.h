#ifndef __MATH_H
#define __MATH_H

#include "common.h"

/**
 * @file handlers/math.h
 * @brief Handlers functions for math instructions (opcodes from 0x60 to 0x84)
 */

/**
 * @fn void iadd()
 * @brief Add two int values
 *
 * opcode: 0x60
 * format: [iadd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the sum
 */ 
void iadd();

/**
 * @fn void ladd()
 * @brief Add two long values
 *
 * opcode: 0x61
 * format: [ladd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the sum
 */
void ladd();

/**
 * @fn void fadd()
 * @brief Add two float values
 * 
 * opcode: 0x62
 * format: [fadd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the sum
 */
void fadd();

/**
 * @fn void dadd()
 * @brief Add two double values
 *
 * opcode: 0x63
 * format: [dadd]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the sum
 */
void dadd();

/**
 * @fn void isub()
 * @brief Subtract one int value from another
 *
 * opcode: 0x64
 * format: [isub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the difference between them
 */ 
void isub();

/**
 * @fn void lsub()
 * @brief Subtract one long value from another
 *
 * opcode: 0x65
 * format: [lsub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the difference between them
 */
void lsub();

/**
 * 
 * @fn void fsub()
 * @brief Subtract one float value from another
 *
 * opcode: 0x66
 * format: [fsub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the difference between them
 */ 
void fsub();

/**
 * @fn void dsub()
 * @brief Subtract one double value from another
 *
 * opcode: 0x67
 * format: [dsub]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the difference between them
 */ 
void dsub();

/**
 * @fn void imul()
 * @brief Multiply two int values
 *
 *
 * opcode: 0x68
 * format: [imul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the multiplication between them
 */ 
void imul();

/**
 * @fn void lmul()
 * @brief Multiply two long values
 *
 * opcode: 0x69
 * format: [lmul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the multiplication between them
 */  
void lmul();

/**
 * @fn void fmul()
 * @brief Multiply two float values
 *
 * opcode: 0x6a
 * format: [fmul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the multiplication between them
 */  
void fmul();

/**
 * @fn void dmul()
 * @brief Multiply two double values
 *
 * opcode: 0x6b
 * format: [dmul]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the multiplication between them
 */  
void dmul();

/**
 * @fn void idiv()
 * @brief Divide one int value from another
 *
 * opcode: 0x6c
 * format: [idiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the division between them
 */ 
void idiv();

/**
 * @fn void ldiv_instruction()
 * @brief Divide one long value from another
 *
 * opcode: 0x6d
 * format: [ldiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the division between them
 */ 
void ldiv_instruction();

/**
 * @fn void fdiv()
 * @brief Divide one float value from another
 *
 * opcode: 0x6e
 * format: [fdiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the division between them
 */ 
void fdiv();

/**
 * 
 * @fn void ddiv()
 * @brief Divide one double value from another
 *
 * opcode: 0x6f
 * format: [ddiv]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the division between them
 */ 
void ddiv();

/**
 * @fn void irem()
 * @brief Calculate the remainder from an int division
 *
 * opcode: 0x70
 * format: [irem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the remainder from their division
 */ 
void irem();

/**
 * @fn void lrem()
 * @brief Calculate the remainder from a long division
 *
 * opcode: 0x71
 * format: [lrem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the remainder from their division
 */ 
void lrem();

/**
 * @fn void frem()
 * @brief Calculate the remainder from a float division
 *
 * opcode: 0x72
 * format: [frem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two float values from the top of the stack and push the remainder from their division
 */ 
void frem();

/**
 * @fn void drem()
 * @brief Calculate the remainder from a double division
 *
 * opcode: 0x73
 * format: [drem]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two double values from the top of the stack and push the remainder from their division
 */ 
void drem();

/**
 * @fn void ineg()
 * @brief Calculate the opposite from an int value
 *
 * opcode: 0x74
 * format: [ineg]
 * stack: (..., value) -> (..., result)
 * description: pop one int value from the top of the stack and push their opposite
 */ 
void ineg();

/**
 * @fn void lneg()
 * @brief Calculate the opposite from a long value
 *
 * opcode: 0x75
 * format: [lneg]
 * stack: (..., value) -> (..., result)
 * description: pop one long value from the top of the stack and push their opposite
 */ 
void lneg();

/**
 * @fn void fneg()
 * @brief Calculate the opposite from a float value
 *
 * opcode: 0x76
 * format: [fneg]
 * stack: (..., value) -> (..., result)
 * description: pop one float value from the top of the stack and push their opposite
 */ 
void fneg();

/**
 * @fn void dneg()
 * @brief Calculate the opposite from an double value
 *
 * opcode: 0x77
 * format: [dneg]
 * stack: (..., value) -> (..., result)
 * description: pop one double value from the top of the stack and push their opposite
 */ 
void dneg();

/**
 * @fn void ishl()
 * @brief Shift an int value left with the low 5 bits from another int value
 *
 * opcode: 0x78
 * format: [ishl]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push one of them left shifted with the low 5 bits from the other
 */ 
void ishl();

/**
 * @fn void lshl()
 * @brief Shift a long value left with the low 6 bits from another long value
 *
 * opcode: 0x79
 * format: [lshl]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push one of them left shifted with the low 6 bits from the other
 */
void lshl();

/**
 * @fn void ishr()
 * @brief Shift an int value right with the low 5 bits from another int value
 *
 * opcode: 0x7a
 * format: [ishr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void ishr();

/**
 * @fn void lshr()
 * @brief Shift a long value right with the low 5 bits from another long value
 *
 * opcode: 0x7b
 * format: [lshr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void lshr();

/**
 * @fn void iushr()
 * @brief Shift an int value right with the low 5 bits from another int value with zero extension
 *
 * opcode: 0x7c
 * format: [iushr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void iushr();

/**
 * @fn void lushr()
 * @brief Shift a long value right with the low 5 bits from another long value with zero extension
 *
 * opcode: 0x7d
 * format: [lushr]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push one of them right shifted with the low 5 bits from the other
 */
void lushr();

/**
 * @fn void iand()
 * @brief Take the bitwise AND conjunction from two int values
 *
 * opcode: 0x7e
 * format: [iand]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the bitwise AND conjunction between them
 */ 
void iand();

/**
 * @fn void land()
 * @brief Take the bitwise AND conjunction from two long values
 *
 * opcode: 0x7f
 * format: [land]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the bitwise AND conjunction between them
 */ 
void land();

/**
 * @fn void ior()
 * @brief Take the bitwise OR conjunction from two int values
 *
 * opcode: 0x80
 * format: [ior]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the bitwise OR conjunction between them
 */ 
void ior();

/**
 * @fn void lor()
 * @brief Take the bitwise OR conjunction from two long values
 *
 * opcode: 0x81
 * format: [lor]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the bitwise OR conjunction between them
 */ 
void lor();

/**
 * @fn void ixor()
 * @brief Take the bitwise XOR conjunction from two int values
 *
 * opcode: 0x82
 * format: [ixor]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two int values from the top of the stack and push the bitwise XOR conjunction between them
 */ 
void ixor();

/**
 * @fn void lxor()
 * @brief Take the bitwise XOR conjunction from two long values
 *
 * opcode: 0x83
 * format: [lxor]
 * stack: (..., value1, value2) -> (..., result)
 * description: pop two long values from the top of the stack and push the bitwise XOR conjunction between them
 */ 
void lxor();

/**
 * @fn void iinc(const u1* instruction)
 * @brief Increment local variable from constant
 *
 * opcode: 0x84
 * format: [iinc]
 * stack: (..., const, index, iinc)
 * description: increment the local variable in index with the const value
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from index 1 on, if any
 */ 
void iinc(const u1* instruction);

#endif  // __MATH_H