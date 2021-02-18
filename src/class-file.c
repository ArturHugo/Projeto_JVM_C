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

Constant* readConstantPool(u2 cp_count, FILE* fd) {
  Constant* constant_pool =
      (Constant*) malloc((cp_count - 1) * sizeof(Constant));

  Constant* cp;
  for(cp = constant_pool; cp < constant_pool + cp_count - 1; cp++) {
    cp->tag = u1Read(fd);
    switch(cp->tag) {
      case CONSTANT_CLASS:
        cp->info.Class.name_index = u2Read(fd);
        break;

      case CONSTANT_FIELDREF:
        cp->info.Fieldref.class_index         = u2Read(fd);
        cp->info.Fieldref.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_METHODREF:
        cp->info.Methodref.class_index         = u2Read(fd);
        cp->info.Methodref.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_INTERFACE_METHODREF:
        cp->info.InterfaceMethodref.class_index         = u2Read(fd);
        cp->info.InterfaceMethodref.name_and_type_index = u2Read(fd);
        break;

      case CONSTANT_STRING:
        cp->info.String.string_index = u2Read(fd);
        break;

      case CONSTANT_INTEGER:
        cp->info.Integer.bytes = u4Read(fd);
        break;

      case CONSTANT_FLOAT:
        cp->info.Float.bytes = u4Read(fd);
        break;

      case CONSTANT_LONG:
        cp->info.Long.high_bytes = u4Read(fd);
        cp->info.Long.low_bytes  = u4Read(fd);
        break;

      case CONSTANT_DOUBLE:
        cp->info.Double.high_bytes = u4Read(fd);
        cp->info.Double.low_bytes  = u4Read(fd);
        break;

      case CONSTANT_NAME_AND_TYPE:
        cp->info.NameAndType.name_index       = u2Read(fd);
        cp->info.NameAndType.descriptor_index = u2Read(fd);
        break;

      case CONSTANT_UTF8:
        cp->info.Utf8.length = u2Read(fd);

        cp->info.Utf8.bytes =
            (u1*) malloc(cp->info.Utf8.length * sizeof(u1));

        // TODO: testar esse bagulho aqui
        u1* bytes_ptr = cp->info.Utf8.bytes;
        u2  num_bytes = cp->info.Utf8.length;
        while(num_bytes--) {
          *bytes_ptr++ = u1Read(fd);
        }
        break;

      case CONSTANT_METHOD_HANDLE:
        cp->info.MethodHandle.reference_kind  = u1Read(fd);
        cp->info.MethodHandle.reference_index = u2Read(fd);
        break;

      case CONSTANT_METHOD_TYPE:
        cp->info.MethodType.descriptor_index = u2Read(fd);
        break;

      case CONSTANT_INVOKE_DYNAMIC:
        cp->info.InvokeDynamic.bootstrap_method_attr_index =
            u2Read(fd);
        cp->info.InvokeDynamic.name_and_type_index = u2Read(fd);
        break;

      default:
        break;
    }
  }
  return constant_pool;
}