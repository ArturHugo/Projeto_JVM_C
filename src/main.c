#include <stdio.h>
#include <stdlib.h>

#include "class-file.h"

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
        // cp->info.class_info.name_index = u2Read(fd);
        printf("(CONSTANT_Class_info);\n");
        printf("\tu2 name_index\t\t= %d;\n",
               cp->info.class_info.name_index);
        break;

      case CONSTANT_FIELDREF:
        // cp->info.fieldref_info.class_index         =
        // u2Read(fd); cp->info.fieldref_info.name_and_type_index
        // = u2Read(fd);
        printf("(CONSTANT_Fieldref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->info.fieldref_info.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->info.fieldref_info.name_and_type_index);
        break;

      case CONSTANT_METHODREF:
        // cp->info.methodref_info.class_index         =
        // u2Read(fd);
        // cp->info.methodref_info.name_and_type_index =
        // u2Read(fd);
        printf("(CONSTANT_Methodref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->info.methodref_info.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->info.methodref_info.name_and_type_index);
        break;

      case CONSTANT_INTERFACE_METHODREF:
        // cp->info.interface_methodref_info.class_index =
        // u2Read(fd);
        // cp->info.interface_methodref_info.name_and_type_index
        // = u2Read(fd);
        printf("(CONSTANT_InterfaceMethodref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->info.interface_methodref_info.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->info.interface_methodref_info.name_and_type_index);
        break;

      case CONSTANT_STRING:
        // cp->info.string_info.string_index = u2Read(fd);
        printf("(CONSTANT_String_info);\n");
        printf("\tu2 string_index\t\t= %d;\n",
               cp->info.string_info.string_index);
        break;

      case CONSTANT_INTEGER:
        // cp->info.integer_info.bytes = u4Read(fd);
        printf("(CONSTANT_Integer_info);\n");
        printf("\tu4 bytes\t\t= %d;\n", cp->info.integer_info.bytes);
        break;

      case CONSTANT_FLOAT:
        // cp->info.float_info.bytes = u4Read(fd);
        printf("(CONSTANT_Float_info);\n");
        printf("\tu4 bytes\t\t= %d;\n", cp->info.float_info.bytes);
        break;

      case CONSTANT_LONG:
        // cp->info.long_info.high_bytes = u4Read(fd);
        // cp->info.long_info.low_bytes  = u4Read(fd);
        printf("(CONSTANT_Long_info);\n");
        printf("\tu4 high_bytes\t\t= %d;\n",
               cp->info.long_info.high_bytes);
        printf("\tu4 low_bytes\t\t= %d;\n",
               cp->info.long_info.low_bytes);
        break;

      case CONSTANT_DOUBLE:
        // cp->info.double_info.high_bytes = u4Read(fd);
        // cp->info.double_info.low_bytes  = u4Read(fd);
        printf("(CONSTANT_Double_info);\n");
        printf("\tu4 high_bytes\t\t= %d;\n",
               cp->info.double_info.high_bytes);
        printf("\tu4 low_bytes\t\t= %d;\n",
               cp->info.double_info.low_bytes);
        break;

      case CONSTANT_NAME_AND_TYPE:
        // cp->info.name_and_type_info.name_index       =
        // u2Read(fd);
        // cp->info.name_and_type_info.descriptor_index =
        // u2Read(fd);
        printf("(CONSTANT_NameAndType_info);\n");
        printf("\tu2 name_index\t\t= %d;\n",
               cp->info.name_and_type_info.name_index);
        printf("\tu2 descriptor_index\t= %d;\n",
               cp->info.name_and_type_info.descriptor_index);
        break;

      case CONSTANT_UTF8:
        // cp->info.utf8_info.length = u2Read(fd);

        // cp->info.utf8_info.bytes =
        //     (u1*) malloc(cp->info.utf8_info.length *
        //     sizeof(u1));

        // // TODO: testar esse bagulho aqui
        // u1* bytes_ptr = cp->info.utf8_info.bytes;
        // u2  num_bytes = cp->info.utf8_info.length;
        // while(num_bytes--) {
        //   *bytes_ptr++ = getc(fd);
        // }
        printf("(CONSTANT_Utf8_info);\n");
        printf("\tu2 length\t\t= %d;\n", cp->info.utf8_info.length);
        printf("\tu2 descriptor_index\t= ");
        u1* bytes_ptr = cp->info.utf8_info.bytes;
        u2  num_bytes = cp->info.utf8_info.length;
        while(num_bytes--) {
          printf("%c", *bytes_ptr++);
        }
        printf(";\n");
        break;

      case CONSTANT_METHOD_HANDLE:
        // cp->info.method_handle_info.reference_kind  =
        // getc(fd); cp->info.method_handle_info.reference_index
        // = u2Read(fd);
        printf("(CONSTANT_MethodHandle_info);\n");
        printf("\tu2 reference_kind\t= %d;\n",
               cp->info.method_handle_info.reference_kind);
        printf("\tu2 reference_index\t= %d;\n",
               cp->info.method_handle_info.reference_index);
        break;

      case CONSTANT_METHOD_TYPE:
        // cp->info.method_type_info.descriptor_index =
        // u2Read(fd);
        printf("(CONSTANT_MethodType_info);\n");
        printf("\tu2 descriptor_index\t= %d;\n",
               cp->info.method_type_info.descriptor_index);
        break;

      case CONSTANT_INVOKE_DYNAMIC:
        // cp->info.invoke_dynamic_info.bootstrap_method_attr_index
        // =
        //     u2Read(fd);
        // cp->info.invoke_dynamic_info.name_and_type_index =
        // u2Read(fd);
        printf("(CONSTANT_InvokeDynamic_info);\n");
        printf(
            "\tu2 bootstrap_method_attr_index\t\t= %d;\n",
            cp->info.invoke_dynamic_info.bootstrap_method_attr_index);
        printf("\tu2 name_and_type_index\t\t= %d;\n",
               cp->info.invoke_dynamic_info.name_and_type_index);
        break;

      default:
        break;
    }
  }

  fclose(fd);

  return (0);
}