#ifndef __STORES_H
#define __STORES_H

#include "common.h"

/**
 * @file handlers/stores.h
 * @brief Handlers functions for store instructions (opcodes from 0x36 to 0x56).
 */

/**
 * @brief Handles instructions istore, lstore, fstore, dstore and astore.
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 *
 * - - opcodes:	0x36, 0x37, 0x38, 0x39, 0x3a
 * - - format: 	[store, index]
 * - - stack: 	(..., value) -> (...)
 * - - description:	put value into operand_stack at index
 */
void tstore(const u1* instruction);

/**
 * @name xstore_n handlers
 * @brief Handles instructions with format xstore_n
 *
 * @param instruction - pointer to the instruction's opcode in the CodeInfo attribute
 *
 * - - opcodes:	0x3b, 0x4e
 * - - format: 	[xstore_n]
 * - - stack: 	(..., value) -> (...)
 * - - description:	put value into operand_stack at n
 */
///@{
void istore_n(const u1* instruction);
void lstore_n(const u1* instruction);
void fstore_n(const u1* instruction);
void dstore_n(const u1* instruction);
void astore_n(const u1* instruction);
///@}

/**
 * @brief Handles instructions iastore, lastore, fastore, dastore and aastore.
 *
 * - format: [tastore]
 * - Stack state: (..., arrayref, index, value) -> (...)
 * - Description: takes reference (arrayref) to an array of type t,
 * index and value from the top of the current Frame's operand stack.
 * Inserts value at array[index]
 */
void tastore();

#endif  // __STORES_H
