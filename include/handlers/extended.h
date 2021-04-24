#ifndef __EXTENDED_HANDLERS_H
#define __EXTENDED_HANDLERS_H

#include "common.h"

/**
 * @file handlers/extended.h
 * @brief Handlers functions for extended instructions (opcodes from 0xc4 to 0xc9).
 */

/**
 * @fn void wide(const u1* instruction)
 * @brief Handles instruction modifier wide.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction:
 *   * Format 1: [wide, <opcode>, indexbyte1, indexbyte2], (for opcodes iload, fload, aload, lload,
 * dload, istore, fstore, astore, lstore, dstore, or ret)
 *   * Format 2: [wide, iinc, indexbyte1, indexbyte2, constbyte1, constbyte2]
 *
 * - Stack state: same as modified instruction
 *
 * - Description: modifies the behavior of instructions handled by functions tload,
 * tstore, ret and iinc.
 * The modified instructions does the same as the original instructions, but using
 * a 16 bit index formed by ((indexbyte1 << 8) | indexbyte2) and a 16 bit constant
 * formed by ((constbyte1 << 8) | constbyte2).
 */
void wide(const u1* instruction);

/**
 * @fn void multianewarray(const u1* instruction)
 * @brief Handles instruction multianewarray.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [multianewarray, indexbyte1, indexbyte2, dimensions]
 *
 * - Stack state: (..., count1, [count2, ...]) -> (..., arrayref)
 *
 * - Description: pops a number o counts from operand stack equals to dimensions. Each
 * count indicates the number o elements in a given dimension of the new multiarray to
 * be allocated (e.g. count1 is the number of elements in the first dimension of the array).
 * This instructions allocates space in the memory for the new multiarray and pushes its
 * JavaType arrayref into the operand stack.
 */
void multianewarray(const u1* instruction);

/**
 * @fn void ifnull(const u1* instruction)
 * @brief Handles instruction ifnull.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [ifnull, branchbyte1, branchbyte2]
 *
 * - Stack state: (..., value) -> (...)
 *
 * - Description: pops reference JavaType value from the stack. If the reference is null
 * branches by an offset of ((branchbyte1 << 8) | branchbyte2).
 */
void ifnull(const u1* instruction);

/**
 * @fn void ifnonnull(const u1* instruction)
 * @brief Handles instruction ifnonnull.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [ifnonnull, branchbyte1, branchbyte2]
 *
 * - Stack state: (..., value) -> (...)
 *
 * - Description: pops reference JavaType value from the stack. If the reference is not null
 * branches by an offset of ((branchbyte1 << 8) | branchbyte2).
 */
void ifnonnull(const u1* instruction);

/**
 * @fn void goto_w(const u1* instruction)
 * @brief Handles instruction goto_w.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [goto_w, branchbyte1, branchbyte2, branchbyte3, branchbyte4]
 *
 * - Stack state: no change
 *
 * - Description: branches by and offset of
 * ((branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4).
 */
void goto_w(const u1* instruction);

/**
 * @fn void jsr_w(const u1* instruction)
 * @brief Handles instruction jsr_w.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [jsr_w, branchbyte1, branchbyte2, branchbyte3, branchbyte4]
 *
 * - Stack state: (...) -> (..., address)
 *
 * - Description: pushes a return address JavaType value into the operand stack. The return
 * address value is the address of the next opcode following this instruction.
 * Branches by an offset of
 * ((branchbyte1 << 24) | (branchbyte2 << 16) | (branchbyte3 << 8) | branchbyte4).
 */
void jsr_w(const u1* instruction);

#endif  //__EXTENDED_HANDLERS_H