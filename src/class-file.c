#include "class-file.h"
#include <corecrt_malloc.h>
#include <stdio.h>
#include <string.h>

u1 u1Read(FILE* fd) { return getc(fd); }

u2 u2Read(FILE* fd) {
  u2 toReturn = u1Read(fd);
  toReturn    = (toReturn << 8) | (u1Read(fd));
  return toReturn;
}

u4 u4Read(FILE* fd) {
  u4 toReturn = u2Read(fd);
  toReturn    = (toReturn << 16) | (u2Read(fd));
  return toReturn;
}

Constant* readConstantPool(u2 cp_count, FILE* fd) {
  Constant* constant_pool = (Constant*) malloc((cp_count - 1) * sizeof(Constant));

  Constant* cp;
  for(cp = constant_pool; cp < constant_pool + cp_count - 1; cp++) {
    cp->tag = u1Read(fd);
    switch(cp->tag) {
      case CONSTANT_CLASS:
        cp->class_info.name_index = u2Read(fd);
        break;

      case CONSTANT_FIELDREF:
        cp->fieldref_info.class_index         = u2Read(fd);
        cp->fieldref_info.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_METHODREF:
        cp->methodref_info.class_index         = u2Read(fd);
        cp->methodref_info.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_INTERFACE_METHODREF:
        cp->interface_methodref_info.class_index         = u2Read(fd);
        cp->interface_methodref_info.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_STRING:
        cp->string_info.string_index = u2Read(fd);
        break;

      case CONSTANT_INTEGER:
        cp->integer_info.bytes = u4Read(fd);
        break;

      case CONSTANT_FLOAT:
        cp->float_info.bytes = u4Read(fd);
        break;

      case CONSTANT_LONG:
        cp->long_info.high_bytes = u4Read(fd);
        cp->long_info.low_bytes  = u4Read(fd);
        break;

      case CONSTANT_DOUBLE:
        cp->double_info.high_bytes = u4Read(fd);
        cp->double_info.low_bytes  = u4Read(fd);
        break;

      case CONSTANT_NAME_AND_TYPE:
        cp->name_and_type_info.name_index       = u2Read(fd);
        cp->name_and_type_info.descriptor_index = u2Read(fd);
        break;

      case CONSTANT_UTF8:
        cp->utf8_info.length = u2Read(fd);

        cp->utf8_info.bytes = (u1*) malloc(cp->utf8_info.length * sizeof(u1));

        // TODO: testar esse bagulho aqui
        u1* bytes_ptr = cp->utf8_info.bytes;
        u2  num_bytes = cp->utf8_info.length;
        while(num_bytes--) {
          *bytes_ptr++ = u1Read(fd);
        }
        break;

      case CONSTANT_METHOD_HANDLE:
        cp->method_handle_info.reference_kind  = u1Read(fd);
        cp->method_handle_info.reference_index = u2Read(fd);
        break;

      case CONSTANT_METHOD_TYPE:
        cp->method_type_info.descriptor_index = u2Read(fd);
        break;

      case CONSTANT_INVOKE_DYNAMIC:
        cp->invoke_dynamic_info.bootstrap_method_attr_index = u2Read(fd);
        cp->invoke_dynamic_info.name_and_type_index         = u2Read(fd);
        break;

      default:
        break;
    }
  }
  return constant_pool;
}

