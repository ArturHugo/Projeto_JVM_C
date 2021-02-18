#include <stdio.h>
#include <stdlib.h>

#include "class-file.h"

int main() {

  FILE* fd = fopen("HelloWorld.class", "rb");
  for(int i = 0; i < 10; i++) {
    getc(fd);
  }
  Constant* constant_pool = readConstantPool(29, fd);
  Constant* cp;
  for(cp = constant_pool; cp < constant_pool + 29 - 1; cp++) {
    printf("\n#%zd", cp - constant_pool + 1);
    printf("\tu1 tag\t\t\t= %d ", cp->tag);
    switch(cp->tag) {
      case CONSTANT_CLASS:
        // cp->info.Class.name_index = u2Read(fd);
        printf("(CONSTANT_Class_info);\n");
        printf("\tu2 name_index\t\t= %d;\n",
               cp->info.Class.name_index);
        break;

      case CONSTANT_FIELDREF:
        // cp->info.Fieldref.class_index         = u2Read(fd);
        // cp->info.Fieldref.name_and_type_index = u2Read(fd);
        printf("(CONSTANT_Fieldref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->info.Fieldref.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->info.Fieldref.name_and_type_index);
        break;

      case CONSTANT_METHODREF:
        // cp->info.Methodref.class_index         = u2Read(fd);
        // cp->info.Methodref.name_and_type_index = u2Read(fd);
        printf("(CONSTANT_Methodref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->info.Methodref.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->info.Methodref.name_and_type_index);
        break;

      case CONSTANT_INTERFACE_METHODREF:
        // cp->info.InterfaceMethodref.class_index         =
        // u2Read(fd); cp->info.InterfaceMethodref.name_and_type_index
        // = u2Read(fd);
        printf("(CONSTANT_InterfaceMethodref_info);\n");
        printf("\tu2 class_index\t\t= %d;\n",
               cp->info.InterfaceMethodref.class_index);
        printf("\tu2 name_and_type_index\t= %d;\n",
               cp->info.InterfaceMethodref.name_and_type_index);
        break;

      case CONSTANT_STRING:
        // cp->info.String.string_index = u2Read(fd);
        printf("(CONSTANT_String_info);\n");
        printf("\tu2 string_index\t\t= %d;\n",
               cp->info.String.string_index);
        break;

      case CONSTANT_INTEGER:
        // cp->info.Integer.bytes = u4Read(fd);
        printf("(CONSTANT_Integer_info);\n");
        printf("\tu4 bytes\t\t= %d;\n", cp->info.Integer.bytes);
        break;

      case CONSTANT_FLOAT:
        // cp->info.Float.bytes = u4Read(fd);
        printf("(CONSTANT_Float_info);\n");
        printf("\tu4 bytes\t\t= %d;\n", cp->info.Float.bytes);
        break;

      case CONSTANT_LONG:
        // cp->info.Long.high_bytes = u4Read(fd);
        // cp->info.Long.low_bytes  = u4Read(fd);
        printf("(CONSTANT_Long_info);\n");
        printf("\tu4 high_bytes\t\t= %d;\n",
               cp->info.Long.high_bytes);
        printf("\tu4 low_bytes\t\t= %d;\n", cp->info.Long.low_bytes);
        break;

      case CONSTANT_DOUBLE:
        // cp->info.Double.high_bytes = u4Read(fd);
        // cp->info.Double.low_bytes  = u4Read(fd);
        printf("(CONSTANT_Double_info);\n");
        printf("\tu4 high_bytes\t\t= %d;\n",
               cp->info.Double.high_bytes);
        printf("\tu4 low_bytes\t\t= %d;\n",
               cp->info.Double.low_bytes);
        break;

      case CONSTANT_NAME_AND_TYPE:
        // cp->info.NameAndType.name_index       = u2Read(fd);
        // cp->info.NameAndType.descriptor_index = u2Read(fd);
        printf("(CONSTANT_NameAndType_info);\n");
        printf("\tu2 name_index\t\t= %d;\n",
               cp->info.NameAndType.name_index);
        printf("\tu2 descriptor_index\t= %d;\n",
               cp->info.NameAndType.descriptor_index);
        break;

      case CONSTANT_UTF8:
        // cp->info.Utf8.length = u2Read(fd);

        // cp->info.Utf8.bytes =
        //     (u1*) malloc(cp->info.Utf8.length * sizeof(u1));

        // // TODO: testar esse bagulho aqui
        // u1* bytes_ptr = cp->info.Utf8.bytes;
        // u2  num_bytes = cp->info.Utf8.length;
        // while(num_bytes--) {
        //   *bytes_ptr++ = getc(fd);
        // }
        printf("(CONSTANT_Utf8_info);\n");
        printf("\tu2 length\t\t= %d;\n", cp->info.Utf8.length);
        printf("\tu2 descriptor_index\t= ");
        u1* bytes_ptr = cp->info.Utf8.bytes;
        u2  num_bytes = cp->info.Utf8.length;
        while(num_bytes--) {
          printf("%c", *bytes_ptr++);
        }
        printf(";\n");
        break;

      case CONSTANT_METHOD_HANDLE:
        // cp->info.MethodHandle.reference_kind  = getc(fd);
        // cp->info.MethodHandle.reference_index = u2Read(fd);
        printf("(CONSTANT_MethodHandle_info);\n");
        printf("\tu2 reference_kind\t= %d;\n",
               cp->info.MethodHandle.reference_kind);
        printf("\tu2 reference_index\t= %d;\n",
               cp->info.MethodHandle.reference_index);
        break;

      case CONSTANT_METHOD_TYPE:
        // cp->info.MethodType.descriptor_index = u2Read(fd);
        printf("(CONSTANT_MethodType_info);\n");
        printf("\tu2 descriptor_index\t= %d;\n",
               cp->info.MethodType.descriptor_index);
        break;

      case CONSTANT_INVOKE_DYNAMIC:
        // cp->info.InvokeDynamic.bootstrap_method_attr_index =
        //     u2Read(fd);
        // cp->info.InvokeDynamic.name_and_type_index = u2Read(fd);
        printf("(CONSTANT_InvokeDynamic_info);\n");
        printf("\tu2 bootstrap_method_attr_index\t\t= %d;\n",
               cp->info.InvokeDynamic.bootstrap_method_attr_index);
        printf("\tu2 name_and_type_index\t\t= %d;\n",
               cp->info.InvokeDynamic.name_and_type_index);
        break;

      default:
        break;
    }
  }

  fclose(fd);

  return (0);
}