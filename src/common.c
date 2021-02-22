#include "common.h"

u1 u1Read(FILE* fd) { return getc(fd); }

u2 u2Read(FILE* fd) {
  u2 toReturn = u1Read(fd);
  toReturn    = (toReturn << 8) | (u1Read(fd));
  return toReturn;
}

u4 u4Read(FILE* fd) {
  u4 toReturn = u2Read(fd);
  toReturn    = (toReturn << 16) | (u2Read(fd));
  return toReturn;
}