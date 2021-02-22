#include "class-file.h"
#include <corecrt_malloc.h>
#include <stdio.h>
#include <string>
#include <vcruntime_string.h>

// Attribute types for string comparisson
static const char CONSTANT_VALUE[]       = "ConstantValue";
static const char CODE[]                 = "Code";
static const char EXCEPTIONS[]           = "Exceptions";
static const char INNER_CLASSES[]        = "InnerClasses";
static const char SOURCE_FILE[]          = "SourceFile";
static const char LINE_NUMBER_TABLE[]    = "LineNumberTable";
static const char LOCAL_VARIABLE_TABLE[] = "LocalVariableTable";

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

        cp->utf8_info.bytes =
            (u1*) malloc(cp->utf8_info.length * sizeof(u1));

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
        cp->invoke_dynamic_info.bootstrap_method_attr_index =
            u2Read(fd);
        cp->invoke_dynamic_info.name_and_type_index = u2Read(fd);
        break;

      default:
        break;
    }
  }
  return constant_pool;
}

AttributeInfo* readAttributes(u2        attributes_count,
                              FILE*     fd,
                              Constant* constant_pool) {
  AttributeInfo* attributes = (AttributeInfo*) malloc(
      (attributes_count) * sizeof(AttributeInfo));

  AttributeInfo* current_attribute;
  for(current_attribute = attributes;
      current_attribute < attributes + attributes_count;
      current_attribute++) {
    current_attribute->attribute_name_index = u2Read(fd);
    current_attribute->attribute_length     = u4Read(fd);

    AttributeInfoUnion* info = (AttributeInfoUnion*) malloc(
        current_attribute->attribute_length);

    Constant attribute_name_reference =
        constant_pool[current_attribute->attribute_name_index];

    if(attribute_name_reference.tag != CONSTANT_UTF8) exit(1);

    u1* attribute_name = attribute_name_reference.utf8_info.bytes;
    u2  attribute_name_size =
        attribute_name_reference.utf8_info.length;

    // TODO: Substituir memcmp por strcmp e adicionar nullbyte ao
    // final dos bytes do CONSTANT_UTF8_info
    if(!memcmp(attribute_name, CONSTANT_VALUE, attribute_name_size)) {
      // TODO: handle ConstantValueInfo
    } else if(!memcmp(attribute_name, CODE, attribute_name_size)) {
      // TODO: handle CodeInfo
    } else if(!memcmp(attribute_name,
                      EXCEPTIONS,
                      attribute_name_size)) {
      // TODO: handle ExceptionsInfo
    } else if(!memcmp(attribute_name,
                      INNER_CLASSES,
                      attribute_name_size)) {
      // TODO: handle InnerClassesInfo
    } else if(!memcmp(attribute_name,
                      SOURCE_FILE,
                      attribute_name_size)) {
      // TODO: handle SourceFileInfo
    } else if(!memcmp(attribute_name,
                      LINE_NUMBER_TABLE,
                      attribute_name_size)) {
      // TODO: handle LineNumberTableInfo
    } else if(!memcmp(attribute_name,
                      LOCAL_VARIABLE_TABLE,
                      attribute_name_size)) {
      // TODO: handle LocalVariableTableInfo
    } else {
      exit(1);
    }
  }

  return attributes;
}
