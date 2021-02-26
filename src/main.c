#include <stdio.h>
#include <stdlib.h>

#include "class-file.h"

int main() {

  FILE* fd = fopen("HelloWorld.class", "rb");
  for(int i = 0; i < 10; i++) {
    getc(fd);
  }
  ConstantPoolInfo* constant_pool = readConstantPool(37, fd);

  printConstantPool(constant_pool, 37);

  fclose(fd);

  return (0);
}