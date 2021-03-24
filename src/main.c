#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "attributes.h"
#include "class-file.h"
#include "common.h"
#include "instructions.h"

int main(int numargs, char* arg[]) {

  if(numargs != 2) {
    printf("Número errado de argumentos. Faça ./output/main.exe <nome do arquivo .class>\n");
    return 1;
  }

  FILE* file = fopen(arg[1], "rb");

  File* fd = convertFile(file);

  fclose(file);

  ClassFile* class_file = readClassFile(fd);

  char* source_file_name = strtok(getSourceFile(class_file), ".");
  char* class_file_name  = strtok(arg[1], ".");

  if(strcmp(source_file_name, class_file_name)) {
    printf("Erro: nome do source file e do class file sao diferentes!\n");
    return 0;
  }

  printClassFile(class_file);

  free(fd->buffer);
  free(fd);

  return (0);
}