#include <stdio.h>
#include <stdlib.h>

#include "class-file.h"
#include "common.h"
#include "instructions.h"

int main() {
  FILE* fd = fopen("HelloWorld.class", "rb");
  for(int i = 0; i < 10; i++) {
    getc(fd);
  }
  ConstantPoolInfo* constant_pool = readConstantPool(29, fd);
  ConstantPoolInfo* cp;
  for(cp = constant_pool; cp < constant_pool + 29 - 1; cp++) {
    printf("\n#%zd", cp - constant_pool + 1);
    printf("\tu1 tag\t\t\t= %d ", cp->tag);
    switch(cp->tag) {
      case CONSTANT_CLASS:
        // cp->class_info.name_index = u2Read(fd);
        printf("(CONSTANT_Class_info);\n");
        printf("\tu2 name_index\t\t= %d;\n",
               cp->class_info.name_index);
        break;

      case CONSTANT_FIELDREF:
        // cp->fieldref_info.class_index         =
        // u2Read(fd); cp->fieldref_info.name_and_type_index
        // = u2Read(fd);
        printf("(CONSTANT_Fieldref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->fieldref_info.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->fieldref_info.name_and_type_index);
        break;

      case CONSTANT_METHODREF:
        // cp->methodref_info.class_index         =
        // u2Read(fd);
        // cp->methodref_info.name_and_type_index =
        // u2Read(fd);
        printf("(CONSTANT_Methodref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->methodref_info.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->methodref_info.name_and_type_index);
        break;

      case CONSTANT_INTERFACE_METHODREF:
        // cp->interface_methodref_info.class_index =
        // u2Read(fd);
        // cp->interface_methodref_info.name_and_type_index
        // = u2Read(fd);
        printf("(CONSTANT_InterfaceMethodref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->interface_methodref_info.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->interface_methodref_info.name_and_type_index);
        break;

      case CONSTANT_STRING:
        // cp->string_info.string_index = u2Read(fd);
        printf("(CONSTANT_String_info);\n");
        printf("\tu2 string_index\t\t= %d;\n",
               cp->string_info.string_index);
        break;

      case CONSTANT_INTEGER:
        // cp->integer_info.bytes = u4Read(fd);
        printf("(CONSTANT_Integer_info);\n");
        printf("\tu4 bytes\t\t= %d;\n", cp->integer_info.bytes);
        break;

      case CONSTANT_FLOAT:
        // cp->float_info.bytes = u4Read(fd);
        printf("(CONSTANT_Float_info);\n");
        printf("\tu4 bytes\t\t= %d;\n", cp->float_info.bytes);
        break;

      case CONSTANT_LONG:
        // cp->long_info.high_bytes = u4Read(fd);
        // cp->long_info.low_bytes  = u4Read(fd);
        printf("(CONSTANT_Long_info);\n");
        printf("\tu4 high_bytes\t\t= %d;\n",
               cp->long_info.high_bytes);
        printf("\tu4 low_bytes\t\t= %d;\n", cp->long_info.low_bytes);
        break;

      case CONSTANT_DOUBLE:
        // cp->double_info.high_bytes = u4Read(fd);
        // cp->double_info.low_bytes  = u4Read(fd);
        printf("(CONSTANT_Double_info);\n");
        printf("\tu4 high_bytes\t\t= %d;\n",
               cp->double_info.high_bytes);
        printf("\tu4 low_bytes\t\t= %d;\n",
               cp->double_info.low_bytes);
        break;

      case CONSTANT_NAME_AND_TYPE:
        // cp->name_and_type_info.name_index       =
        // u2Read(fd);
        // cp->name_and_type_info.descriptor_index =
        // u2Read(fd);
        printf("(CONSTANT_NameAndType_info);\n");
        printf("\tu2 name_index\t\t= %d;\n",
               cp->name_and_type_info.name_index);
        printf("\tu2 descriptor_index\t= %d;\n",
               cp->name_and_type_info.descriptor_index);
        break;

      case CONSTANT_UTF8:
        // cp->utf8_info.length = u2Read(fd);

        // cp->utf8_info.bytes =
        //     (u1*) malloc(cp->utf8_info.length *
        //     sizeof(u1));

        // // TODO: testar esse bagulho aqui
        // u1* bytes_ptr = cp->utf8_info.bytes;
        // u2  num_bytes = cp->utf8_info.length;
        // while(num_bytes--) {
        //   *bytes_ptr++ = getc(fd);
        // }
        printf("(CONSTANT_Utf8_info);\n");
        printf("\tu2 length\t\t= %d;\n", cp->utf8_info.length);
        printf("\tu2 descriptor_index\t= ");
        u1* bytes_ptr = cp->utf8_info.bytes;
        u2  num_bytes = cp->utf8_info.length;
        while(num_bytes--) {
          printf("%c", *bytes_ptr++);
        }
        printf(";\n");
        break;

      case CONSTANT_METHOD_HANDLE:
        // cp->method_handle_info.reference_kind  =
        // getc(fd); cp->method_handle_info.reference_index
        // = u2Read(fd);
        printf("(CONSTANT_MethodHandle_info);\n");
        printf("\tu2 reference_kind\t= %d;\n",
               cp->method_handle_info.reference_kind);
        printf("\tu2 reference_index\t= %d;\n",
               cp->method_handle_info.reference_index);
        break;

      case CONSTANT_METHOD_TYPE:
        // cp->method_type_info.descriptor_index =
        // u2Read(fd);
        printf("(CONSTANT_MethodType_info);\n");
        printf("\tu2 descriptor_index\t= %d;\n",
               cp->method_type_info.descriptor_index);
        break;

      case CONSTANT_INVOKE_DYNAMIC:
        // cp->invoke_dynamic_info.bootstrap_method_attr_index
        // =
        //     u2Read(fd);
        // cp->invoke_dynamic_info.name_and_type_index =
        // u2Read(fd);
        printf("(CONSTANT_InvokeDynamic_info);\n");
        printf("\tu2 bootstrap_method_attr_index\t\t= %d;\n",
               cp->invoke_dynamic_info.bootstrap_method_attr_index);
        printf("\tu2 name_and_type_index\t\t= %d;\n",
               cp->invoke_dynamic_info.name_and_type_index);
        break;

      default:
        break;
    }
  }

  fclose(fd);
  return (0);
}