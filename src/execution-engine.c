#include "execution-engine.h"

void run(char* start_class_name) {
  // execution engine
  u2    pc = 0;
  Stack frame_stack;

  ClassFile* current_class = mapGet(method_area.loaded_classes, start_class_name);
  int        main_index    = 1;  // TODO encontrar metodo main da primeira classe

  Instruction* current_instructions =
      current_class->methods[main_index].attributes[0].code_info._instructions;

  // TODO fazer função de executar frame

  while(1) {
    Instruction current_instruction  = current_instructions[pc];
    void (*instruction)(u1*, Frame*) = instructions_ptrs[current_instructions[pc].bytecode];
    // instruction(current_instruction.opperand_bytes, )
  }
}