#include <stdio.h>
#include <stdlib.h>

#include "class-file.h"

int main() {

  FILE* fd = fopen("HelloWorld.class", "rb");
  for(int i = 0; i < 10; i++) {
    getc(fd);
  }
  ConstantPoolInfo* constant_pool = readConstantPool(29, fd);

  printConstantPool(constant_pool);

  fclose(fd);

  return (0);
}