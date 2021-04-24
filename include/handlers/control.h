
#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"
/**
 * @file handlers/control.h
 * @brief Handlers functions for control instructions (opcodes from 0xa7 to 0xb1).
 */

/**
 * @fn void go_to()
 * @brief: Branch always
 * format:  [goto, branchbyte1, branchbyte2 ]
 * stack:   (...) -> (...)
 * description: takes pc value from current frame
 * and update using int16_t branch offset.
 */
void go_to();

/**
 * @fn void jsr()
 * @brief: Jump subroutine 
 * format:  [jsr, branchbyte1, branchbyte2 ]
 * stack:   (...) -> (..., address)
 * description: takes pc value from current frame
 * and pushes into the operand stack. 
 */
void jsr();

/**
 * @fn void ret()
 * @brief: Return from subroutine
 * format:  [ret, index]
 * stack:   (...) -> (...)
 * description:	takes pc value from current frame
 * and pushes into the operand stack.
 */
void ret();

/**
 * @fn void ireturn()
 * @brief: Return void from method
 * format:  [return]
 * stack:   (...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack.
 */
void ireturn();

/**
 * @fn void lreturn()
 * @brief: Return void from method
 * format:  [return]
 * stack:   (...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack.
 */
void lreturn();

/**
 * @fn void freturn()
 * @brief: Return void from method
 * format:  [return]
 * stack:   (...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack.
 */
void freturn();

/**
 * @fn void dreturn()
 * @brief: Return void from method
 * format:  [return]
 * stack:   (...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack.
 */
void dreturn();

/**
 * @fn void areturn()
 * @brief: Return void from method
 * format:  [return]
 * stack:   (...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack.
 */
void areturn();

/**
 * @fn void return()
 * @brief: Return void from method
 * format:  [return]
 * stack:   (...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack.
 */
void return_op();

/**
 * @fn void lookupswitch()
 * @brief: Access jump table by key match and jump
 * format:  [lookupswitch, bytepad, defaultbyte1, defaultbyte2,
			defaultbyte3, defaultbyte4, npairs1, npairs2, npairs3, npairs4,
			match-offset pairs]
 * stack:   (..., key) -> (...)
 * description:	takes pc value from current frame
 * and update using default or offset value.
 */
void lookupswitch();

/**
 * @fn void tableswitch()
 * @brief: Access jump table by index and jump
 * format:  [tableswitch, bytepad, defaultbyte1, defaultbyte2,
			defaultbyte3, defaultbyte4, lowbyte1, lowbyte2, lowbyte3,
			lowbyte4, highbyte1, highbyte2, highbyte3, highbyte4, jump offsets]
 * stack:   (..., key) -> (...)
 * description:	takes pc value from current frame
 * and update using default or offset value.
 */
void tableswitch();

#endif  // __CONTROL_H
