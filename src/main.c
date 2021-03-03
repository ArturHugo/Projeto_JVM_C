#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "class-file.h"

int main() {

  FILE* file = fopen("HelloWorld.class", "rb");

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

  fd->seek                        = 0x1a0;
  u2             attributes_count = u2Read(fd);
  AttributeInfo* attributes       = readAttributes(attributes_count, fd, constant_pool);

  printConstantPool(constant_pool, constant_pool_count);
  printAttributes(attributes_count, attributes, constant_pool);

  free(fd->buffer);
  free(fd);

  return (0);
}
