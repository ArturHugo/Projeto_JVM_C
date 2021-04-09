#include "execution-engine.h"
#include "frame.h"
#include "handlers/constants.h"

void func() { printf("aaaaaaaaaaaaaaaaaaaaaaaaaa\n"); }

void (*instructions_handlers[256])(u1*) = {func};

void run(char* starting_class_name) {
  frame_stack = NULL;

  // execution engine
  ClassFile* starting_class = mapGet(method_area.loaded_classes, starting_class_name);
  int        main_index     = 1;  // TODO encontrar metodo main da primeira classe

  // criando frame
  Frame* starting_frame;
  starting_frame = newFrame(starting_class, main_index);

  // empilhando primeiro frame
  pushNode(&frame_stack, starting_frame);

  /*
  1) iniciar stack de frames com um frame contendo o método main da classe inicial

  2) handler das instruções invoke empilham um frame

  3) no while, o frame "no controle" eh o do topo da pilha

  */

  while(peekNode(frame_stack)) {
    Frame* current_frame        = (Frame*) peekNode(frame_stack);
    u1*    current_instructions = current_frame->current_method->attributes[0].code_info.code;
    u1*    current_instruction  = current_instructions + current_frame->local_pc;
    // void (*instruction)(u1*)        = instructions_handlers[*current_instruction];
    void (*instruction)(u1*) = instructions_handlers[0];
    instruction(current_instruction);
  }
}
