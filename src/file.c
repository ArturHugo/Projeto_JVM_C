#include "file.h"

File* convertFile(FILE* file) {
  File* fd = malloc(sizeof(File));
  fseek(file, 0, SEEK_END);
  fd->size = ftell(file);
  fseek(file, 0, SEEK_SET);
  fd->buffer = malloc(fd->size * sizeof(u1));

  for(int i = 0; i < fd->size; i++)
    fd->buffer[i] = getc(file);

  return fd;
}