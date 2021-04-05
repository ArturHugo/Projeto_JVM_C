#include "execution-engine.h"

void run(char* starting_class_name) {
  // execution engine
  ClassFile* starting_class = mapGet(method_area.loaded_classes, starting_class_name);
  int        main_index     = 1;  // TODO encontrar metodo main da primeira classe

  /*
  1) iniciar stack de frames com um frame contendo o método main da classe inicial

  2) handler das instruções invoke empilham um frame

  3) no while, o frame "no controle" eh o do topo da pilha

  */

  while(1) {
    Frame*       current_frame = (Frame*) peekNode(frame_stack);
    Instruction* current_instructions =
        current_frame->current_method->attributes[0].code_info._instructions;
    Instruction current_instruction = current_instructions[current_frame->local_pc];
    void (*instruction)(u1*)        = instructions_handlers[current_instruction.bytecode];
    instruction(current_instruction.opperand_bytes);
  }
}