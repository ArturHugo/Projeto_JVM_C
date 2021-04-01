#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "attributes.h"
#include "class-file.h"
#include "common.h"
#include "instructions.h"
#include "method-area.h"

int main(int numargs, char* arg[]) {

  if(numargs != 3) {
    printf(
        "Número errado de argumentos. Faça ./output/main.exe -<flag> <nome do arquivo .class>\n");
    printf("Flag -l para leitor-exibidor\n");
    printf("Flag -i para interpretador\n");
    return 1;
  }

  FILE* file = fopen(arg[2], "rb");

  File* fd = convertFile(file);

  fclose(file);

  ClassFile* class_file       = readClassFile(fd);
  char*      source_file_name = strtok(getSourceFile(class_file), ".");
  char*      class_file_name  = strtok(arg[2], ".");

  if(strcmp(source_file_name, class_file_name)) {
    printf("Erro: nome do source file e do class file sao diferentes!\n");
    return 1;
  }

  if(!strcmp(arg[1], "-l")) {
    printClassFile(class_file);
  } else if(!strcmp(arg[1], "-i")) {
    extern MethodArea method_area;
    method_area.loaded_classes = newMap();
    mapAdd(method_area.loaded_classes, class_file_name, class_file);
    printClassFile(mapGet(method_area.loaded_classes, class_file_name));
  }

  free(fd->buffer);
  free(fd);

  return (0);
}