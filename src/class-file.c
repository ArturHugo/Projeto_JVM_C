#include "class-file.h"
#include <stdio.h>
#include <string.h>

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
