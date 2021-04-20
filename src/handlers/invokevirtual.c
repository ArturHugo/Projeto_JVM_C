#include "handlers/invokevirtual.h"
#include "class-file.h"
#include "frame.h"
#include "global.h"

#include <string.h>

void invokevirtual(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u1*    operands      = instruction + 1;

  u2 index = (operands[0] << 8) | operands[1];

  ConstantPoolInfo* current_cp_info = &(current_frame->constant_pool[index]);

  char* class_name;
  char* method_name;
  char* method_descriptor;

  if(current_cp_info->tag == CONSTANT_METHODREF) {
    class_name        = (char*) (current_cp_info->methodref_info._class);
    method_name       = (char*) (current_cp_info->methodref_info._name);
    method_descriptor = (char*) (current_cp_info->methodref_info._descriptor);
  } else {
    class_name        = (char*) (current_cp_info->interface_methodref_info._interface);
    method_name       = (char*) (current_cp_info->interface_methodref_info._name);
    method_descriptor = (char*) (current_cp_info->interface_methodref_info._descriptor);
  }

  if(!strcmp(class_name, "java/io/PrintStream;")) {
    if(!strcmp(method_name, "print") || !strcmp(method_name, "println")) {
      // TODO checa descritor e imprime
      JavaType value_to_print;
      popValue(&current_frame->operand_stack, &value_to_print);
      switch(method_descriptor[1]) {
        case 'C':
          printf("%c", value_to_print.char_value);
          break;

        case 'I':
          printf("%d", value_to_print.int_value);
          break;

        case 'J':
          printf("%ld", value_to_print.long_value);
          break;

        case 'F':
          printf("%f", value_to_print.float_value);
          break;

        case 'D':
          printf("%f", value_to_print.double_value);
          break;

        case 'Z':
          value_to_print.boolean_value ? printf("true") : printf("false");
          break;

        case 'L':
          if(!strcmp(method_descriptor, "(Ljava/lang/String;)V")) {
            printf("%s", (char*) value_to_print.reference_value);
          } else {
            print("Argumento de metodo print ou println nao reconhecido\n");
          }
          break;

        case ')':
          break;

        default:
          print("Argumento de metodo print ou println nao reconhecido\n");
          break;
      }
      if(!strcmp(method_name, "println")) {
        print("\n");
      }
    } else {
      print("Metodo da classe PrintStream nao simulado\n");
    }
  } else if(!strcmp(class_name, "java/lang/StringBuilder")) {
    // TODO talvez fazer depois
    exit(10);
  } else {
    // TODO does this even work?
    ClassFile* new_class = loadClass(class_name);

    if(new_class == NULL) {
      printf("\npc = %d: invokestatic failed\n", current_frame->local_pc);
      exit(1);
    }

    if(new_class->_status != initialized) {
      resolveReferences(new_class);
    }

    initializeClass(new_class);

    Frame* new_frame = newFrame(new_class, method_name);

    // loading opperands from current stack to new local variables
    u2       n_args               = getArgumentCount((u1*) method_descriptor);
    u2       local_variable_index = 1;
    JavaType temp_value;
    for(u2 i = 0; i < n_args; i++) {
      popValue(&(current_frame->operand_stack), &temp_value);
      new_frame->local_variables[local_variable_index] = temp_value;
      local_variable_index++;
      if(temp_value.cat_tag == CAT2)
        local_variable_index++;
    }
    popValue(&(current_frame->operand_stack), &temp_value);
    new_frame->local_variables[0] = temp_value;

    pushNode(&frame_stack, new_frame);
  }
  current_frame->local_pc += 3;
}