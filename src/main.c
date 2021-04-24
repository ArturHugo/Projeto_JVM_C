#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "attributes.h"
#include "class-file.h"
#include "common.h"
#include "execution-engine.h"
#include "frame.h"
#include "global.h"
#include "instructions.h"
#include "map.h"
#include "method-area.h"
#include "stack.h"

MethodArea method_area;
Stack      frame_stack;

int main(int numargs, char* arg[]) {

  if(numargs != 3) {
    printf("Número errado de argumentos. Faça ./output/main.exe -<flag> <nome do arquivo.class>\n");
    printf("Flag -l para leitor-exibidor\n");
    printf("Flag -i para interpretador\n");
    return 1;
  }

  if(!strcmp(arg[1], "-l")) {
    FILE* file = fopen(arg[2], "rb");

    File* fd = convertFile(file);

    fclose(file);

    ClassFile* class_file = readClassFile(fd);

    char* source_file_name = strtok(getSourceFile(class_file), ".");
    char* class_file_name  = strtok(arg[2], ".");

    if(strcmp(source_file_name, class_file_name)) {
      printf("Erro: nome do source file e do class file sao diferentes!\n");
      return 0;
    }

    printClassFile(class_file);

    free(fd->buffer);
    free(fd);
  } else if(!strcmp(arg[1], "-i")) {
    method_area.loaded_classes = newMap();
    loadObjectClass();

    char* class_name = trimSuffix(arg[2], ".class");

    if(class_name == NULL) {
      panic("Erro ao ler o argumento");
    }

    run(class_name);
    free(class_name);
  }
  return (0);
}
