#include "exceptions.h"
#include "attributes.h"
#include "frame.h"
#include "global.h"

#include <string.h>

void throwException(const char* exception_name) {
  Frame* current_frame = (Frame*) peekNode(frame_stack);

  if(current_frame == NULL) {
    panic("Exception %s", exception_name);
  }

  ExceptionTable* exception = findException(exception_name);

  // Exception match was found
  if (exception != NULL) {
    current_frame->local_pc = exception->handler_pc;
  } else {
    // if no exception was found, pop current_frame
    // and let previous frame take care
    Frame* old_frame = popNode(&frame_stack);
    free(old_frame);
    throwException(exception_name);
  }
}

ExceptionTable* findException(const char* exception_name) {
  Frame* current_frame = (Frame*) peekNode(frame_stack);

  u2 exception_table_length =
      current_frame->current_method->attributes[0].code_info.exception_table_length;
  ExceptionTable* exception_table =
      current_frame->current_method->attributes[0].code_info.exception_table;

  for(int index = 0; index < exception_table_length; index++) {
    ExceptionTable* current_entry = exception_table + index;

    // if it's within the current entry bounds
    if(current_frame->local_pc >= current_entry->start_pc &&
       current_frame->local_pc <= current_entry->end_pc) {

      // an index in the constant_pool
      u2 catch_type = current_entry->catch_type;

      // all exception match when catch_type is 0;
      if(catch_type == 0) {
        return current_entry;
      }

      ClassInfo exception_class_info = current_frame->constant_pool[catch_type].class_info;

      // see if name matches
      // on correct implementations, should check if it's a subclass of
      if(!strcmp((char*) exception_class_info._name, exception_name)) {
        return current_entry;
      }
    }
  }

  return NULL;
}
