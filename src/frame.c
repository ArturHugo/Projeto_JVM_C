#include "frame.h"
#include "class-file.h"
#include "common.h"
#include "map.h"
#include "method-area.h"

#include <string.h>
#include <stdio.h>

Frame* newFrame(ClassFile* current_class, char* method_name, char* method_descriptor) {
  char* name_and_type = calloc(strlen(method_name) + strlen(method_descriptor) + 1, sizeof(char*));
  strcat(name_and_type, method_name);
  strcat(name_and_type, method_descriptor);

  MethodInfo* method = mapGet(current_class->_method_map, name_and_type);

  free(name_and_type);

  if(method == NULL) {
    panic("Method not found while trying to create frame: %s", method_name);
  }

  Frame* new_frame         = malloc(sizeof(*new_frame));
  new_frame->constant_pool = current_class->constant_pool;

  new_frame->current_method = method;
  new_frame->operand_stack  = NULL;
  new_frame->local_pc       = 0;

  new_frame->local_variables =
      malloc((new_frame->current_method->attributes->code_info.max_locals) * sizeof(JavaType));

  return new_frame;
}
