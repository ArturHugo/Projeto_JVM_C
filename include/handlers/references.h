#ifndef __REFERENCES_H
#define __REFERENCES_H

#include "common.h"

/**
 * @file handlers/references.h
 * @brief Handlers functions for reference instructions (opcodes from 0x57 to 0x5f).
 */

/**
 * @fn void invokestatic(const u1* instruction)
 * @brief Invoke a class (static) method
 * format:  [invokestatic, indexbyte1, indexbyte2]
 * stack:   (..., [arg1, [arg2...]]) -> (...)
 * description:  Invoke a class (static) method. args are the method arguments, indexbyte1 and 2 are
 * joined and used as a constant pool index to the static method.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void invokestatic(const u1* instruction);

/**
 * @brief Invoke instance method; special handling for superclass, private, and
 * instance initialization method invocations
 *
 * - opcode:	0xb7
 * - format: 	[invokespecial, indexbyte1, indexbyte2]
 * - stack: 	(..., objectref, [arg1, [arg2 ...]]) -> (...)
 * - description: get a methodref info using indexbyte1 and indexbyte2 to
 *   construct a index in the current frame constant pool. Load the class
 *   referenced by the method, then create a new frame using the retrieved
 *   methodref. Pop nargs + 1 using the method's descriptor and put them in the
 *   new frame local variable array. Push the new frame.
 * - reference: [invokespecial](https://docs.oracle.com/javase/specs/jvms/se8/jvms8.pdf#%5B%7B%22num%22%3A2285%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C72%2C468%2Cnull%5D)
 */
void invokespecial(const u1* instruction);

/**
 * @brief Invoke interface method
 *
 * - opcode:	0xb9
 * - format: 	[invokeinterface, indexbyte1, indexbyte2, count, 0]
 * - stack: 	(..., objectref, [arg1, [arg2 ...]]) -> (...)
 * - description: get a interfaceref info using indexbyte1 and indexbyte2 to
 *   construct a index in the current frame constant pool. Pop nargs + 1 using
 *   then interface descriptor, then use the popped objectref to construct a
 *   new frame. Put the popped values on the new frame local variable array
 *   then push the new frame.
 * - reference: [invokeinterface](https://docs.oracle.com/javase/specs/jvms/se8/jvms8.pdf#%5B%7B%22num%22%3A3184%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C72%2C590%2Cnull%5D)
 */
void invokeinterface(const u1* instruction);

/**
 * @fn void new(const u1* instruction)
 * @brief Create new object
 * format:  [new, indexbyte1, indexbyte2]
 * stack:   (...) -> (..., objectref)
 * description:  Create new object.  indexbyte1 and 2 are joined and used as a constant pool index
 * to the object's class or interface.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void new(const u1* instruction);

/**
 * @fn void newarray(const u1* instruction)
 * @brief Create new array
 * format:  [newarray, atype]
 * stack:   (..., count) -> (..., arrayref)
 * description:  The count must be of type int. It is popped off the operand stack.
 * The count represents the number of elements in the array to be
 * created.
 * The atype is a code that indicates the type of array to create. It must
 * take one of the following values:
 *
 * T_BOOLEAN 4
 * T_CHAR 5
 * T_FLOAT 6
 * T_DOUBLE 7
 * T_BYTE 8
 * T_SHORT 9
 * T_INT 10
 * T_LONG 11
 *
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void newarray(const u1* instruction);

/**
 * @fn void anewarray()
 * @brief Create new array of references
 * format:  [new, indexbyte1, indexbyte2]
 * stack:   (...) -> (..., objectref)
 * description:  Create new array of reference. indexbyte1 and 2 are joined and used as a constant
 * pool index to the simbolic reference of a class, array or interface type. Count is of type int
 * and represents the number of components of the array to be created.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */

void anewarray();

/**
 * @fn void arraylength()
 * @brief pushes array length onto stack
 * format:  [arraylength]
 * stack:   (..., arrayref) -> (..., length)
 * description:  The arrayref must be of type reference and must refer to an array.
 * It is popped from the operand stack. The length of the array it
 * references is determined. That length is pushed onto the operand
 * stack as an int.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void arraylength();
void athrow();

#endif  // __REFERENCES_H
