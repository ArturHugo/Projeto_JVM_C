#include "constant-pool.h"
#include "class-file.h"

#include "string.h"
#include <stdio.h>

ConstantPoolInfo* readConstantPool(u2 cp_count, File* fd) {
  ConstantPoolInfo* constant_pool = (ConstantPoolInfo*) malloc(cp_count * sizeof(ConstantPoolInfo));

  ConstantPoolInfo* cp;
  for(cp = constant_pool + 1; cp < constant_pool + cp_count; cp++) {
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
        memcpy(&cp->float_info._value, &cp->float_info.bytes, sizeof(float));
        break;

      case CONSTANT_LONG:
        cp->long_info.high_bytes = u4Read(fd);
        cp->long_info.low_bytes  = u4Read(fd);
        cp->long_info._value =
            ((int64_t) cp->long_info.high_bytes << 32) | ((int64_t) cp->long_info.low_bytes);
        cp++;  // Skip next constant pool slot, because 8 byte
               // constants occupy 2 slots.
        break;

      case CONSTANT_DOUBLE:
        cp->double_info.high_bytes = u4Read(fd);
        cp->double_info.low_bytes  = u4Read(fd);
        cp->double_info._value =
            ((int64_t) cp->double_info.high_bytes << 32) | ((int64_t) cp->double_info.low_bytes);
        cp++;  // Skip next constant pool slot, because 8 byte
               // constants occupy 2 slots.
        break;

      case CONSTANT_NAME_AND_TYPE:
        cp->name_and_type_info.name_index       = u2Read(fd);
        cp->name_and_type_info.descriptor_index = u2Read(fd);
        break;

      case CONSTANT_UTF8:
        cp->utf8_info.length = u2Read(fd);

        cp->utf8_info.bytes = (u1*) malloc((cp->utf8_info.length + 1) * sizeof(u1));

        u1* bytes_ptr = cp->utf8_info.bytes;
        u2  num_bytes = cp->utf8_info.length;
        while(num_bytes--) {
          *bytes_ptr++ = u1Read(fd);
        }
        *bytes_ptr = 0;
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

u1* getUtf8String(ConstantPoolInfo* constant_pool, uint16_t index) {
  switch(constant_pool[index].tag) {
    case CONSTANT_CLASS:;
      u2 class_name_index = constant_pool[index].class_info.name_index;
      return constant_pool[class_name_index].utf8_info.bytes;
    case CONSTANT_STRING:;
      u2 string_index = constant_pool[index].string_info.string_index;
      return constant_pool[string_index].utf8_info.bytes;
    case CONSTANT_UTF8:
      return constant_pool[index].utf8_info.bytes;
    default:
      return NULL;
  }
}

u1** getUtf8Strings(u1* num_of_strings, ConstantPoolInfo* constant_pool, uint16_t index) {
  u1** utf8_strings;
  *num_of_strings = 0;
  u2 class_index, name_and_type_index;
  switch(constant_pool[index].tag) {
    case CONSTANT_CLASS:
      *num_of_strings = 1;
      utf8_strings    = (u1**) malloc(*num_of_strings * sizeof(u1*));

      u2 class_name_index = constant_pool[index].class_info.name_index;
      utf8_strings[0]     = constant_pool[class_name_index].utf8_info.bytes;
      break;

    case CONSTANT_FIELDREF:
      class_index         = constant_pool[index].fieldref_info.class_index;
      name_and_type_index = constant_pool[index].fieldref_info.name_and_type_index;
      break;

    case CONSTANT_METHODREF:
      class_index         = constant_pool[index].methodref_info.class_index;
      name_and_type_index = constant_pool[index].methodref_info.name_and_type_index;
      break;

    case CONSTANT_INTERFACE_METHODREF:
      class_index         = constant_pool[index].interface_methodref_info.class_index;
      name_and_type_index = constant_pool[index].interface_methodref_info.name_and_type_index;
      break;

    case CONSTANT_STRING:
      *num_of_strings = 1;
      utf8_strings    = (u1**) malloc(*num_of_strings * sizeof(u1*));

      u2 string_index = constant_pool[index].string_info.string_index;
      utf8_strings[0] = constant_pool[string_index].utf8_info.bytes;
      break;

    case CONSTANT_NAME_AND_TYPE:
      *num_of_strings = 2;
      utf8_strings    = (u1**) malloc(*num_of_strings * sizeof(u1*));

      u2 name_index   = constant_pool[index].name_and_type_info.name_index;
      utf8_strings[0] = constant_pool[name_index].utf8_info.bytes;

      u2 descriptor_index = constant_pool[index].name_and_type_info.descriptor_index;
      utf8_strings[1]     = constant_pool[descriptor_index].utf8_info.bytes;
      break;

    default:
      utf8_strings = NULL;
      break;
  }

  if((constant_pool[index].tag == CONSTANT_FIELDREF) ||
     (constant_pool[index].tag == CONSTANT_METHODREF) ||
     (constant_pool[index].tag == CONSTANT_INTERFACE_METHODREF)) {

    *num_of_strings = 3;
    utf8_strings    = (u1**) malloc(*num_of_strings * sizeof(u1*));

    u2 class_name_index = constant_pool[class_index].class_info.name_index;
    utf8_strings[0]     = constant_pool[class_name_index].utf8_info.bytes;

    u2 field_name_index = constant_pool[name_and_type_index].name_and_type_info.name_index;
    utf8_strings[1]     = constant_pool[field_name_index].utf8_info.bytes;

    u2 descriptor_index = constant_pool[name_and_type_index].name_and_type_info.descriptor_index;
    utf8_strings[2]     = constant_pool[descriptor_index].utf8_info.bytes;
  }
  return utf8_strings;
}

// TODO pq esa função existe?
void printConstantValue(ConstantPoolInfo* constant_pool, u2 index) {
  switch(constant_pool[index].tag) {
    case CONSTANT_STRING:;  // TODO ta dando um erro mto estranho
      u1   num_of_strings = 0;
      u1** utf8_strings   = getUtf8Strings(&num_of_strings, constant_pool, index);

      if(num_of_strings)
        printf("<%s>", utf8_strings[0]);

      free(utf8_strings);
      break;
    case CONSTANT_INTEGER:
      printf("<%d>", constant_pool[index].integer_info.bytes);
      break;
    case CONSTANT_DOUBLE:
      printf("<%f>", constant_pool[index].double_info._value);
      break;
    case CONSTANT_LONG:
      printf("<%ld>", constant_pool[index].long_info._value);
      break;
    case CONSTANT_FLOAT:
      printf("<%f>", constant_pool[index].float_info._value);
      break;
    default:
      break;
  }
}

void printConstantPoolInfo(ConstantPoolInfo* constant_pool, int index) {
  u1   num_of_strings = 0;
  u1** utf8_strings   = getUtf8Strings(&num_of_strings, constant_pool, index);
  switch(constant_pool[index].tag) {
    case CONSTANT_CLASS:
      printf("CONSTANT_Class_info\n");

      if(num_of_strings)
        printf("\tClass name:           cp_info #%02d <%s>\n",
               constant_pool[index].class_info.name_index,
               (char*) utf8_strings[0]);
      break;

    case CONSTANT_FIELDREF:
      printf("CONSTANT_Fieldref_info\n");

      if(num_of_strings) {
        printf("\tClass name:           cp_info #%02d <%s>\n",
               constant_pool[index].fieldref_info.class_index,
               (char*) utf8_strings[0]);
        printf("\tName and type:        cp_info #%02d <%s%s>\n",
               constant_pool[index].fieldref_info.name_and_type_index,
               (char*) utf8_strings[1],
               (char*) utf8_strings[2]);
      }
      break;

    case CONSTANT_METHODREF:
      printf("CONSTANT_Methodref_info\n");

      if(num_of_strings) {
        printf("\tClass name:           cp_info #%02d <%s>\n",
               constant_pool[index].methodref_info.class_index,
               (char*) utf8_strings[0]);
        printf("\tName and type:        cp_info #%02d <%s%s>\n",
               constant_pool[index].methodref_info.name_and_type_index,
               (char*) utf8_strings[1],
               (char*) utf8_strings[2]);
      }
      break;

    case CONSTANT_INTERFACE_METHODREF:
      printf("CONSTANT_InterfaceMethodref_info\n");

      if(num_of_strings) {
        printf("\tClass name:              cp_info #%02d <%s>\n",
               constant_pool[index].interface_methodref_info.class_index,
               (char*) utf8_strings[0]);
        printf("\tName and type:        cp_info #%02d <%s%s>\n",
               constant_pool[index].interface_methodref_info.name_and_type_index,
               (char*) utf8_strings[1],
               (char*) utf8_strings[2]);
      }
      break;

    case CONSTANT_STRING:
      printf("CONSTANT_String_info\n");

      if(num_of_strings)
        printf("\tString                cp_info #%02d <%s>\n",
               constant_pool[index].string_info.string_index,
               (char*) utf8_strings[0]);
      break;

    case CONSTANT_INTEGER:
      printf("CONSTANT_Integer_info\n");
      printf("\tBytes:                0x%08x\n", constant_pool[index].integer_info.bytes);
      printf("\tInteger:              %d\n", (int32_t) constant_pool[index].integer_info.bytes);
      break;

    case CONSTANT_FLOAT:
      printf("CONSTANT_Float_info\n");
      printf("\tBytes:                0x%08x\n", constant_pool[index].float_info.bytes);

      float float_num;
      memcpy(&float_num, &constant_pool[index].float_info.bytes, sizeof(float));

      printf("\tFloat:                %f\n", float_num);
      break;

    case CONSTANT_LONG:
      printf("CONSTANT_Long_info\n");
      printf("\tHigh bytes:           0x%08x\n", constant_pool[index].long_info.high_bytes);
      printf("\tLow bytes:            0x%08x\n", constant_pool[index].long_info.low_bytes);

      u4 long_high = constant_pool[index].long_info.high_bytes;
      u4 long_low  = constant_pool[index].long_info.low_bytes;

      int64_t long_num;
      long_num = ((uint64_t) long_high << 32) | ((uint64_t) long_low);

      printf("\tLong:                 %zd\n", long_num);
      break;

    case CONSTANT_DOUBLE:
      printf("CONSTANT_Double_info\n");
      printf("\tHigh bytes:           0x%08x\n", constant_pool[index].double_info.high_bytes);
      printf("\tLow bytes:            0x%08x\n", constant_pool[index].double_info.low_bytes);

      u4 double_high = constant_pool[index].double_info.high_bytes;
      u4 double_low  = constant_pool[index].double_info.low_bytes;

      int64_t double_bytes;
      double_bytes = ((int64_t) double_high << 32) | ((int64_t) double_low);

      double double_num;
      memcpy(&double_num, &double_bytes, sizeof(double));

      printf("\tDouble:               %f\n", double_num);
      break;

    case CONSTANT_NAME_AND_TYPE:
      printf("CONSTANT_NameAndType_info\n");

      if(num_of_strings) {
        printf("\tName:                 cp_info #%02d <%s>\n",
               constant_pool[index].name_and_type_info.name_index,
               (char*) utf8_strings[0]);
        printf("\tDescriptor:           cp_info #%02d <%s>\n",
               constant_pool[index].name_and_type_info.descriptor_index,
               (char*) utf8_strings[1]);
      }
      break;

    case CONSTANT_UTF8:
      printf("CONSTANT_Utf8_info\n");
      printf("\tLength of byte array: %d\n", constant_pool[index].utf8_info.length);
      printf("\tLength of string:     %d\n", constant_pool[index].utf8_info.length);
      printf("\tString:               %s\n", (char*) constant_pool[index].utf8_info.bytes);
      break;

    case CONSTANT_METHOD_HANDLE:
      printf("CONSTANT_MethodHandle_info\n");
      break;

    case CONSTANT_METHOD_TYPE:
      printf("CONSTANT_MethodType_info\n");
      break;

    case CONSTANT_INVOKE_DYNAMIC:
      printf("CONSTANT_InvokeDynamic_info\n");
      break;

    default:
      printf("(large numeric continued)\n");
      break;
  }
  free(utf8_strings);
}

void printConstantPool(ConstantPoolInfo* constant_pool, u2 cp_count) {

  printf("Constant pool\n{\n");

  for(int i = 1; i < cp_count; i++) {
    printf("\n[%02d] ", i);
    printConstantPoolInfo(constant_pool, i);
  }

  printf("}\n");
}
