#ifndef __EXECUTION_ENGINE_H
#define __EXECUTION_ENGINE_H

extern void (*const instructions_handlers[256])(const u1*);
void run(char* start_class_name);

#endif  // __EXECUTION_ENGINE_H
