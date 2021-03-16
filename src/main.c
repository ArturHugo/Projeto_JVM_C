#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "class-file.h"
#include "common.h"
#include "instructions.h"

int main() {

  FILE* file = fopen("TableSwitch.class", "rb");

  File* fd = malloc(sizeof(File));
  fseek(file, 0, SEEK_END);
  fd->size = ftell(file);
  fseek(file, 0, SEEK_SET);
  fd->buffer = malloc(fd->size * sizeof(u1));

  for(int i = 0; i < fd->size; i++)
    fd->buffer[i] = getc(file);

  fclose(file);

  fd->seek = 8;

  u2                constant_pool_count = u2Read(fd);
  ConstantPoolInfo* constant_pool       = readConstantPool(constant_pool_count, fd);

  fd->seek     = 0x185;
  u1* code     = malloc(58 * sizeof(u1));
  u1* code_ptr = code;
  for(; code_ptr < code + 58; code_ptr++)
    *code_ptr = u1Read(fd);

  Instruction** output = malloc(sizeof(Instruction*));
  readInstructions(code, 58, output);
  // u2             attributes_count = u2Read(fd);
  // AttributeInfo* attributes       = readAttributes(attributes_count, fd, constant_pool);

  printConstantPool(constant_pool, constant_pool_count);
  printInstructions(*output, 15, constant_pool);

  free(fd->buffer);
  free(fd);

  return (0);
}
