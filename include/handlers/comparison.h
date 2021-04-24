#ifndef __COMPARISON_H
#define __COMPARISON_H

#include "common.h"

/**
 * @file handlers/comparison.h
 * @brief Handlers functions for comparison instructions (opcodes from 0x94 to 0xa6).
 */

/**
 * @fn void lcmp()
 * @brief: Compare long
 * format:  [lcmp]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type long from operand stack
 * and pushes into the operand stack.
 */
void lcmp();

/**
 * @fn void fcmpl()
 * @brief: Compare float
 * format:  [fcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type float from operand stack
 * and pushes into the operand stack.
 */
void fcmpl();

/**
 * @fn void fcmpg()
 * @brief: Compare float
 * format:  [fcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type float from operand stack
 * and pushes into the operand stack.
 */
void fcmpg();

/**
 * @fn void dcmpl()
 * @brief: Compare double
 * format:  [dcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type double from operand stack
 * and pushes into the operand stack.
 */
void dcmpl();

/**
 * @fn void dcmpg()
 * @brief: Compare double
 * format:  [dcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type double from operand stack
 * and pushes into the operand stack.
 */
void dcmpg();

/**
 * @fn void ifeq()
 * @brief: Branch if int comparison with zero succeeds
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value.
 */
void ifeq();

/**
 * @fn void ifne()
 * @brief: Branch if int comparison with zero succeeds
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value.
 */
void ifne();

/**
 * @fn void iflt()
 * @brief: Branch if int comparison with zero succeeds
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value.
 */
void iflt();

/**
 * @fn void ifge()
 * @brief: Branch if int comparison with zero succeeds
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value.
 */
void ifge();

/**
 * @fn void ifgt()
 * @brief: Branch if int comparison with zero succeeds
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value.
 */
void ifgt();

/**
 * @fn void ifle()
 * @brief: Branch if int comparison with zero succeeds
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value.
 */
void ifle();

/**
 * @fn void if_icmpeq()
 * @brief: Branch if int comparison succeeds
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_icmpeq();

/**
 * @fn void if_icmpne()
 * @brief: Branch if int comparison succeeds
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_icmpne();

/**
 * @fn void void if_icmplt()
 * @brief: Branch if int comparison succeeds
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_icmplt();

/**
 * @fn void void if_icmpge()
 * @brief: Branch if int comparison succeeds
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_icmpge();

/**
 * @fn void void if_icmpgt()
 * @brief: Branch if int comparison succeeds
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_icmpgt();

/**
 * @fn void void if_icmple()
 * @brief: Branch if int comparison succeeds
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_icmple();

/**
 * @fn void void if_acmpeq()
 * @brief: Branch if reference comparison succeeds
 * format:  [if_acmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_acmpeq();

/**
 * @fn void void if_acmpne()
 * @brief: Branch if reference comparison succeeds
 * format:  [if_acmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value.
 */
void if_acmpne();

#endif  // __COMPARISON_H