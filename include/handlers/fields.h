#ifndef __FIELD_INSTRUCTIONS_H
#define __FIELD_INSTRUCTIONS_H

#include "common.h"

/**
 * @file handlers/stores.h
 * @brief Handlers functions for field related instructions (opcodes from 0xb2 to 0xb5).
 */

/**
 * @brief handler for getstatic instruction
 *
 * @param instruction - bytecode stream, offset to current instruction
 *
 * - opcode:	0xb2
 * - format: 	[getstatic, indexbyte1, indexbyte2]
 * - stack: 	(...) -> (..., value)
 * - description:	get the value from a static field on a class, may initialize
 *   class if not already
 * - constraints:
 *    * [x] class must be loaded (load if not)
 *    * [ ] field must be static (IncompattibleClassChangeError)
 */
void getstatic(const u1* instruction);

/**
 * @brief handler for setstatic instruction
 *
 * @param instruction - bytecode stream, offset to current instruction
 *
 * - opcode:	0xb3
 * - format: 	[putstatic, indexbyte1, indexbyte2]
 * - stack: 	(..., value) -> (...)
 * - description: set the value to a static field on a class, may initialize
 * -   class if not already
 * - constaints:
 *    * [x] class must be loaded (load if not)
 *    * [ ] field must be static (IncompattibleClassChangeError)
 *    * [ ] value must be type compatible with field descriptor (???)
 *    * [ ] field must not be final if current method is not <clinit> (IllegalAccessError)
 */
void putstatic(const u1* instruction);

/**
 * @brief handler for setstatic instruction
 *
 * @param instruction - bytecode stream, offset to current instruction
 *
 * - opcode:	0xb4
 * - format: 	[getfield, indexbyte1, indexbyte2]
 * - stack: 	(..., objectref) -> (..., value)
 * - description: get instance field from objectref and push into the operand_stack
 * - constaints:
 *    * [x] object must not be null
 *    * [ ] field must not be static (IncompattibleClassChangeError)
 */
void getfield(const u1* instruction);

/**
 * @brief handler for setstatic instruction
 *
 * @param instruction - bytecode stream, offset to current instruction
 *
 * opcode:	0xb4
 * format: 	[putfield, indexbyte1, indexbyte2]
 * stack: 	(..., objectref, value) -> (...)
 * description: set field from object to value
 * constaints:
 *  [x] object must not be null (NullPointerException)
 *  [ ] value must be type compatible with field descriptor (???)
 *  [ ] field must not be static (IncompattibleClassChangeError)
 *  [ ] field must not be final outside <init> (IllegalAccessError)
 */
void putfield(const u1* instruction);

#endif  // __FIELD_INSTRUCTIONS_H
