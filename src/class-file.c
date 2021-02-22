#include "class-file.h"

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

ConstantPoolInfo* readConstantPool(u2 cp_count, FILE* fd) {
  ConstantPoolInfo* constant_pool = (ConstantPoolInfo*) malloc(
      (cp_count - 1) * sizeof(ConstantPoolInfo));

  ConstantPoolInfo* cp;
  for(cp = constant_pool; cp < constant_pool + cp_count - 1; cp++) {
    cp->tag = u1Read(fd);
    switch(cp->tag) {
      case CONSTANT_CLASS:
        cp->info.class_info.name_index = u2Read(fd);
        break;

      case CONSTANT_FIELDREF:
        cp->info.fieldref_info.class_index         = u2Read(fd);
        cp->info.fieldref_info.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_METHODREF:
        cp->info.methodref_info.class_index         = u2Read(fd);
        cp->info.methodref_info.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_INTERFACE_METHODREF:
        cp->info.interface_methodref_info.class_index = u2Read(fd);
        cp->info.interface_methodref_info.name_and_type_index =
            u2Read(fd);
        break;

      case CONSTANT_STRING:
        cp->info.string_info.string_index = u2Read(fd);
        break;

      case CONSTANT_INTEGER:
        cp->info.integer_info.bytes = u4Read(fd);
        break;

      case CONSTANT_FLOAT:
        cp->info.float_info.bytes = u4Read(fd);
        break;

      case CONSTANT_LONG:
        cp->info.long_info.high_bytes = u4Read(fd);
        cp->info.long_info.low_bytes  = u4Read(fd);
        break;

      case CONSTANT_DOUBLE:
        cp->info.double_info.high_bytes = u4Read(fd);
        cp->info.double_info.low_bytes  = u4Read(fd);
        break;

      case CONSTANT_NAME_AND_TYPE:
        cp->info.name_and_type_info.name_index       = u2Read(fd);
        cp->info.name_and_type_info.descriptor_index = u2Read(fd);
        break;

      case CONSTANT_UTF8:
        cp->info.utf8_info.length = u2Read(fd);

        cp->info.utf8_info.bytes =
            (u1*) malloc(cp->info.utf8_info.length * sizeof(u1));

        // TODO: testar esse bagulho aqui
        u1* bytes_ptr = cp->info.utf8_info.bytes;
        u2  num_bytes = cp->info.utf8_info.length;
        while(num_bytes--) {
          *bytes_ptr++ = u1Read(fd);
        }
        break;

      case CONSTANT_METHOD_HANDLE:
        cp->info.method_handle_info.reference_kind  = u1Read(fd);
        cp->info.method_handle_info.reference_index = u2Read(fd);
        break;

      case CONSTANT_METHOD_TYPE:
        cp->info.method_type_info.descriptor_index = u2Read(fd);
        break;

      case CONSTANT_INVOKE_DYNAMIC:
        cp->info.invoke_dynamic_info.bootstrap_method_attr_index =
            u2Read(fd);
        cp->info.invoke_dynamic_info.name_and_type_index = u2Read(fd);
        break;

      default:
        break;
    }
  }
  return constant_pool;
}