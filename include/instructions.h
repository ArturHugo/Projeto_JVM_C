#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include "common.h"

/**
 * @file instructions.h
 * @brief Reads bytecode from classfile and loads its instructions into an internal representation.
 */

/**
 * Struct that contains the necessary information about an instruction.
 */
typedef struct {
  u1  bytecode;
  u1  n_opperand_bytes;
  u1* opperand_bytes;
  u2  pc;
} Instruction;

u4 nInstructions(u1* code, u4 n_bytes);

/**
 * @fn Instruction* readInstructions(u1* code, u4 n_instruction)
 * @brief Reads bytecode and returns irs instructions in an array.
 * Reads a bytecode and returns initialized array of instructions, struct which contains all
 * necessary information for bytecode viewer.
 *
 * @param code Java bytecode to be analyzed.
 * @param n_instruction Number of instructions contained in the bytecode.
 * @return Populated array of instruction struct.
 */

Instruction* readInstructions(u1* code, u4 n_instruction);

/**
 * @fn void printInstructions(Instruction* instructions, u4 n_instrs, ConstantPoolInfo* cp)
 * @brief Organizes and prints relevant information contained in Instruction array.
 *
 * @param instructions Instruction (struct) type array containing instructions to be printed.
 * @param n_instrs length of instruction array.
 * @param cp Current class's constant pool.
 */

void printInstructions(Instruction* instructions, u4 n_instrs, ConstantPoolInfo* cp);

/* --------------------- Helper functions -----------------------------*/
// funcões abaixo retornam o número de bytes de argumento para as instruções de tamanho
// variável. code deve ser o código da instrução inteira (incluindo bytecode). Offset
// deve ser o valor do pc local (número do byte atual no código).

/**
 * @fn u4 calcTableswitchOps(u1* code, u4 offset)
 * @brief Calculates the number of operand bytes that accompany a tableswitch instruction.
 *
 * @param code Code with the tableswitch bytecode on index 0 and arguments on the folowing indexes.
 * @param offset PC value at the instruction bytecode byte.
 * @return Number of operand bytes that accompany the given tableswitch.
 */

u4 calcTableswitchOps(u1* code, u4 offset);

/**
 * @fn u4 calcLookupswitchOps(u1* code, u4 offset)
 * @brief Calculates the number of operand bytes that accompany a lookupswitch instruction.
 *
 * @param code Code with the lookupswitch bytecode on index 0 and arguments on the folowing indexes.
 * @param offset PC value at the instruction bytecode byte.
 * @return Number of operand bytes that accompany the given lookupswitch.
 */

u4 calcLookupswitchOps(u1* code, u4 offset);

/**
 * @fn u4 calcWideOps(u1* code, u4 offset)
 * @brief Calculates the number of operand bytes that accompany a wide instruction.
 *
 * @param code Code with the wide bytecode on index 0 and arguments on the folowing indexes.
 * @param offset PC value at the instruction bytecode byte.
 * @return Number of operand bytes that accompany the given wide.
 */

u1 calcWideOps(u1* code);

#endif