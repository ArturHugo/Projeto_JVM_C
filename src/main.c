#include <stdio.h>
#include <stdlib.h>

#include "class-file.h"

int main() {

  FILE* file = fopen("HelloWorld.class", "rb");

  File* fd = malloc(sizeof(File));

  fseek(file, 0, SEEK_END);

  fd->size = ftell(file);

  fseek(file, 0, SEEK_SET);

  fd->buffer = malloc(fd->size * sizeof(u1));

  fd->seek = 0;

  for(int i = 0; i < fd->size; i++) {
    fd->buffer[i] = getc(file);
  }

  for(int i = 0; i < 10; i++) {
    u1Read(fd);
  }
  ConstantPoolInfo* constant_pool = readConstantPool(37, fd);

  printConstantPool(constant_pool, 37);

  free(fd->buffer);
  free(fd);
  fclose(file);

  return (0);
}