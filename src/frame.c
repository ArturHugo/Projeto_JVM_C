#include "frame.h"

#include "class-file.h"
#include "common.h"
#include "map.h"
#include "method-area.h"

Frame* newFrame(ClassFile* current_class, char* method_name) {
  MethodInfo* method = mapGet(current_class->_method_map, method_name);

  if(method == NULL) {
    panic("Method not found while trying to create frame: %s", method_name);
  }

  Frame* new_frame         = malloc(sizeof(*new_frame));
  new_frame->constant_pool = current_class->constant_pool;

  new_frame->current_method = method;
  new_frame->operand_stack  = NULL;
  new_frame->local_pc       = 0;

  // TODO pode não ser attribute[0] que contém code info
  // TODO malloc de variáveis locais sendo feita em u4, mas mudamos as variaveis locais para
  // javatype
  new_frame->local_variables =
      malloc((new_frame->current_method->attributes->code_info.max_locals) * sizeof(u4));

  return new_frame;
}
