#ifndef __FILE_H
#define __FILE_H

#include "common.h"

#include <stdio.h>

typedef struct {
  u1* buffer;
  int size;
  int seek;
} File;

u1 u1Read(File* fd);
u2 u2Read(File* fd);
u4 u4Read(File* fd);

File* convertFile(FILE* file);

#endif