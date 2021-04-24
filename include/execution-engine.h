#ifndef __EXECUTION_ENGINE_H
#define __EXECUTION_ENGINE_H

#include "class-file.h"
#include "common.h"
#include "frame.h"
#include "global.h"

#include "handlers/conversions.h"
#include "handlers/loads.h"
#include "handlers/references.h"
#include "handlers/stack.h"
#include "handlers/stores.h"



extern void (*const instructions_handlers[256])(const u1*);
void run(char* start_class_name);

#endif  // __EXECUTION_ENGINE_H
