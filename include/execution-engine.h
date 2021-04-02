#include "class-file.h"
#include "common.h"
#include "frame.h"
#include "global.h"
#include "instructions.h"
#include "method-area.h"
#include "stack.h"

void (*instructions_ptrs[256])(u1*, Frame*);

void run(char* start_class_name);