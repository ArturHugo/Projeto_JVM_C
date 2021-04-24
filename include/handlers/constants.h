#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include "common.h"
#include "frame.h"
#include "global.h"

/**
 * @file handlers/constants.h
 * @brief Handlers functions for constant instructions (opcodes from 0x00 to 0x14).
 */

/**
 * @fn void nop()
 * @brief Do nothing
 * - format:  [nop]
 * - stack:   (...) -> (...)
 * - description: Do nothing.
 */
void nop();

/**
 * @fn void aconst_null()
 * @brief Push the null object reference onto the operand stack.
 * - format:  [aconst_null]
 * - stack:   (...) -> (..., null)
 * - description: Push the null object reference onto the operand stack.
 */
void aconst_null();

/**
 * @fn void iconst_n(const u1* instruction)
 * @brief: Push the int constant <i> onto stack
 * - format:  [iconst_<i>]
 * - stack:   (...) -> (..., <i>)
 * - description: Push the int constant <i> (-1, 0, 1, 2, 3, 4 or 5) onto the operand
 * stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void iconst_n(const u1* instruction);

/**
 * @fn lconst_n(const u1* instruction)
 * @brief Push the long constant <l> onto stack
 * - format:  [lconst_<l>]
 * - stack:   (...) -> (..., <l>)
 * - description: Push the long constant <l> (0 or 1) onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void lconst_n(const u1* instruction);

/**
 * @fn fconst_n(const u1* instruction)
 * @brief Push the float constant <f> onto stack
 * - format:  [fconst_<f>]
 * - stack:   (...) -> (..., <f>)
 * - description: Push the float constant <f> (0.0, 1.0, or 2.0) onto the operand
 * stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void fconst_n(const u1* instruction);

/**
 * @fn dconst_n(const u1* instruction)
 * @brief Push the double constant <d> onto stack
 * - format:  [dconst_<d>]
 * - stack:   (...) -> (..., <d>)
 * - description: Push the double constant <d> (0.0 or 1.0) onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void dconst_n(const u1* instruction);

/**
 * @fn bipush(const u1* instruction)
 * @brief Pushes int value onto stack
 * - format:  [bipush, byte]
 * - stack:   (...) -> (..., value)
 * - description:  The immediate byte is sign-extended to an int value. That value
 * is pushed onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void bipush(const u1* instruction);

/**
 * @fn sipush(const u1* instruction)
 * @brief Pushes int value onto stack
 * - format:  [sipush, byte1, byte2]
 * - stack:   (...) -> (..., value)
 * - description:  The immediate unsigned byte1 and byte2 values are assembled into
 * an intermediate short, where the value of the short is (byte1 <<
 * 8) | byte2. The intermediate value is then sign-extended to an int
 * value. That value is pushed onto the operand stack.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void sipush(const u1* instruction);

/**
 * @fn ldc(const u1* instruction)
 * @brief Push item from run-time constant pool
 * format:  [ldc, index]
 * stack:   (...) -> (..., value)
 * description:  Push item from run-time constant pool.
 *
 * - format:  [ldc_w, indexbyte1, indexbyte2]
 * - stack:   (...) -> (..., value)
 * - description:  Push item from run-time constant pool (wide index).
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void ldc(const u1* instruction);

/**
 * @fn ldc2_w(const u1* instruction)
 * @brief Push long or double from run-time constant pool
 * - format:  [ldc2_w, indexbyte1, indexbyte2]
 * - stack:   (...) -> (..., value)
 * - description:  Push long or double from run-time constant pool (wide index).
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void ldc2_w(const u1* instruction);

#endif  // __CONSTANTS_H
