#ifndef __LOAD_HANDLERS_H
#define __LOAD_HANDLERS_H

#include "common.h"

/**
 * @file handlers/loads.h
 * @brief Handlers functions for load instructions (opcodes from 0x15 to 0x35).
 */

/**
 * @fn void tload(const u1* instruction)
 * @brief Handles instructions iload, lload, fload, tload, dload and aload.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - - Format of instruction: [tload, index]
 *
 * - - Stack state: (...) -> (..., value)
 *
 * - - Description: takes JavaType value of type t from current Frame's local_variables[index]
 * and pushes it into the operand stack. Increments Frame's local PC by 2.
 */
void tload(const u1* instruction);

/**
 * @fn void iload_n(const u1* instruction)
 * @brief Handles instructions iload_0, iload_1, iload_2, iload_3.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [iload_n]
 *
 * - Stack state: (...) -> (..., value)
 *
 * - Description: takes int JavaType value from current Frame's local_variables[n]
 * and pushes into the operand stack. Increments Frame's local PC by 1.
 */
void iload_n(const u1* instruction);

/**
 * @fn void lload_n(const u1* instruction)
 * @brief Handles instructions lload_0, lload_1, lload_2, lload_3.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [lload_n]
 *
 * - Stack state: (...) -> (..., value)
 *
 * - Description: takes long JavaType value from current Frame's local_variables[n]
 * and pushes into the operand stack. Increments Frame's local PC by 1.
 */
void lload_n(const u1* instruction);

/**
 * @fn void fload_n(const u1* instruction)
 * @brief Handles instructions fload_0, fload_1, fload_2, fload_3.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [fload_n]
 *
 * - Stack state: (...) -> (..., value)
 *
 * - Description: takes float JavaType value from current Frame's local_variables[n]
 * and pushes into the operand stack. Increments Frame's local PC by 1.
 */
void fload_n(const u1* instruction);

/**
 * @fn void dload_n(const u1* instruction)
 * @brief Handles instructions dload_0, dload_1, dload_2, dload_3.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [dload_n]
 *
 * - Stack state: (...) -> (..., value)
 *
 * - Description: takes double JavaType value from current Frame's local_variables[n]
 * and pushes into the operand stack. Increments Frame's local PC by 1.
 */
void dload_n(const u1* instruction);

/**
 * @fn void aload_n(const u1* instruction)
 * @brief Handles instructions aload_0, aload_1, aload_2, aload_3.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 * code bytes.
 *
 * - Format of instruction: [aload_n]
 *
 * - Stack state: (...) -> (..., value)
 *
 * - Description: takes reference JavaType value from current Frame's local_variables[n]
 * and pushes into the operand stack. Increments Frame's local PC by 1.
 */
void aload_n(const u1* instruction);

/**
 * @fn void taload()
 * @brief Handles instructions iaload, laload, faload, daload and aaload.
 *
 * - Format of instruction: [taload]
 *
 * - Stack state: (..., arrayref, index) -> (..., value)
 *
 * - Description: takes reference (arrayref) to an array of type t
 * and index from the top of the current Frame's operand stack.
 * Pushes the JavaType value of array[index] into the operand stack.
 */
void taload();

#endif  // __LOAD_HANDLERS_H