#include "file.h"

u1 u1Read(File* fd) { return fd->buffer[fd->seek++]; }

u2 u2Read(File* fd) {
  u2 toReturn = u1Read(fd);
  toReturn    = (toReturn << 8) | (u1Read(fd));
  return toReturn;
}

u4 u4Read(File* fd) {
  u4 toReturn = u2Read(fd);
  toReturn    = (toReturn << 16) | (u2Read(fd));
  return toReturn;
}

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