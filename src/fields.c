#include "/home/gui/Área de Trabalho/Projeto_JVM_C/include/fields.h"
#include "/home/gui/Área de Trabalho/Projeto_JVM_C/include/class-file.h"
#include <inttypes.h>
#include "common.h"

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

static bool isMagicValid(ClassFile *class_file){
  return class_file-> == 0xCAFEBABE ? true : false;
}

static void set_interface(FILE *fp, ClassFile *class_file){
    class_file->interfaces = (u2*) malloc(sizeof(u2) * class_file->interfaces_count);
    for (u2 i = 0; i < class_file->interfaces_count; i++) {
        class_file->interfaces[i] = readU2(fp);
    }
}

static void set_fields(FILE *fp, ClassFile *classFile) {
    classFile->fields = (field_info*) malloc(sizeof(field_info) * classFile->fields_count);
    for (u2 i = 0; i < classFile->fields_count; i++) {
        field_info field;
        
        field.access_flags = readU2(fp);
        field.name_index = readU2(fp);
        field.descriptor_index = readU2(fp);
        field.attributes_count = readU2(fp);
        
        field.attributes = (attribute_info*) malloc(sizeof(attribute_info) * field.attributes_count);
        
        for (u2 j = 0; j < field.attributes_count; j++) {
            field.attributes[j] = readAttributes(field.attributes_count, fp, class_file->constant_pool);
        }
        
        classFile->fields[i] = field;
    }
}

static void set_methods(FILE *fp, ClassFile *classFile) {
    classFile->methods = (method_info*) malloc(sizeof(method_info) * classFile->methods_count);
    for (u2 i = 0; i < classFile->methods_count; i++) {
        classFile->methods[i].access_flags = readU2(fp);
        classFile->methods[i].name_index = readU2(fp);
        classFile->methods[i].descriptor_index = readU2(fp);
        classFile->methods[i].attributes_count = readU2(fp);
        
        classFile->methods[i].attributes = (attribute_info*) malloc(sizeof(attribute_info) * classFile->methods[i].attributes_count);
        for (u2 j = 0; j < classFile->methods[i].attributes_count; j++) {
            classFile->methods[i].attributes[j] = readAttributes(classFile->methods[i].attributes_count, fp, class_file->constant_pool);
        }
    }
}

ClassFile* readClassFile(FILE *fp, ConstantPoolInfo* cp){
  ClassFile *class_file = (ClassFile*) malloc(sizeof(ClassFile));

  class_file->magic = u4Read(fp);
  if(isMagicValid(class_file) == false){
    printf("Class Format Error - :\\ \n");
    exit(3);
  }

  class_file->minor_version = u2Read(fp);
  class_file->major_version = u2Read(fp);
  class_file-> constant_pool_count = u2Read(fp);
  readConstantPool((class_file-> constant_pool_count), fp);
  class_file->access_flags = u2Read(fp);
  class_file->this_class = u2Read(fp);
  class_file->super_class = u2Read(fp);
  class_file->interfaces_count = u2Read(fp);
  set_interface(fp, class_file);
  class_file->fields_count = u2Read(fp);
  set_fields(fp, class_file);
  class_file->methods_count = u2Read(fp);
  set_methods(fp, class_file);
  class_file->attributes_count = u2Read(fp);
  class_file->attributes = readAttributes(class_file->attributes_count, fp, cp);

  return class_file
}


