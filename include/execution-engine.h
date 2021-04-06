#ifndef __EXECUTION_ENGINE_H
#define __EXECUTION_ENGINE_H

#include "class-file.h"
#include "common.h"
#include "frame.h"
#include "global.h"
#include "instructions.h"
#include "method-area.h"
#include "stack.h"

void func();

static void (*instructions_handlers[256])(u1*) = {func};

void run(char* start_class_name);

#endif  // __EXECUTION_ENGINE_H