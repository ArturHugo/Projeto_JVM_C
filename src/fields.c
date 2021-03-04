#include "fields.h"
#include "class-file.h"
#include <inttypes.h>
#include "common.h"
#include <stdbool.h>

u1 b1Read(File* fd) { return fd->buffer[fd->seek++]; }

u2 b2Read(File* fd) {
  u2 toReturn = b1Read(fd);
  toReturn    = (toReturn << 8) | (b1Read(fd));
  return toReturn;
}

u4 b4Read(File* fd) {
  u4 toReturn = b2Read(fd);
  toReturn    = (toReturn << 16) | (b2Read(fd));
  return toReturn;
}
/*AttributeInfo getAttributeInfo(FILE *fp, ClassFile *classFile) {
    AttributeInfo result;
    result.attribute_name_index = b2Read(fp);
    result.attribute_length = b4Read(fp);
    
    CONSTANT_Utf8_info name = getUtf8FromConstantPool(result.attribute_name_index, classFile);
    if (Utils::compareUtf8WithString(name, "ConstantValue")) {
        result.constant_value_info= readU2(fp);
    } else if (Utils::compareUtf8WithString(name, "Code")) {
        result.code_info = getAttributeCode(fp, classFile);
    } else if (Utils::compareUtf8WithString(name, "Exceptions")) {
        result.exceptions_info = getAttributeExceptions(fp);
    } else if (Utils::compareUtf8WithString(name, "InnerClasses")) {
        result.inner_classes_info; = getAttributeInnerClasses(fp);
    } else if (Utils::compareUtf8WithString(name, "SourceFile")) {
        result.source_file_info; = getAttributeSourceFile(fp);
    } else if (Utils::compareUtf8WithString(name, "LineNumberTable")) {
        result.line_number_table_info = getAttributeLineNumberTable(fp);
    } else if (Utils::compareUtf8WithString(name, "LocalVariableTable")) {
        result.local_variable_table_info = getAttributeLocalVariable(fp);
    } else {
        cerr << "Arquivo .class possui uma um atributo invalido." << endl;
        exit(6);
    }
    
    return result;
}*/

ConstantPoolInfo* readConstantPool2(u2 cp_count, File* fd) {
  ConstantPoolInfo* constant_pool = (ConstantPoolInfo*) malloc(
      (cp_count - 1) * sizeof(ConstantPoolInfo));

  ConstantPoolInfo* cp;
  for(cp = constant_pool; cp < constant_pool + cp_count - 1; cp++) {
    cp->tag = b1Read(fd);
    switch(cp->tag) {
      case CONSTANT_CLASS:
        cp->class_info.name_index = b2Read(fd);
        break;

      case CONSTANT_FIELDREF:
        cp->fieldref_info.class_index         = b2Read(fd);
        cp->fieldref_info.name_and_type_index = b2Read(fd);
        break;

      case CONSTANT_METHODREF:
        cp->methodref_info.class_index         = b2Read(fd);
        cp->methodref_info.name_and_type_index = b2Read(fd);
        break;

      case CONSTANT_INTERFACE_METHODREF:
        cp->interface_methodref_info.class_index         = b2Read(fd);
        cp->interface_methodref_info.name_and_type_index = b2Read(fd);
        break;

      case CONSTANT_STRING:
        cp->string_info.string_index = b2Read(fd);
        break;

      case CONSTANT_INTEGER:
        cp->integer_info.bytes = b4Read(fd);
        break;

      case CONSTANT_FLOAT:
        cp->float_info.bytes = b4Read(fd);
        break;

      case CONSTANT_LONG:
        cp->long_info.high_bytes = b4Read(fd);
        cp->long_info.low_bytes  = b4Read(fd);
        break;

      case CONSTANT_DOUBLE:
        cp->double_info.high_bytes = b4Read(fd);
        cp->double_info.low_bytes  = b4Read(fd);
        break;

      case CONSTANT_NAME_AND_TYPE:
        cp->name_and_type_info.name_index       = b2Read(fd);
        cp->name_and_type_info.descriptor_index = b2Read(fd);
        break;

      case CONSTANT_UTF8:
        cp->utf8_info.length = b2Read(fd);

        cp->utf8_info.bytes =
            (u1*) malloc(cp->utf8_info.length * sizeof(u1));

        // TODO: testar esse bagulho aqui
        u1* bytes_ptr = cp->utf8_info.bytes;
        u2  num_bytes = cp->utf8_info.length;
        while(num_bytes--) {
          *bytes_ptr++ = b1Read(fd);
        }
        break;

      case CONSTANT_METHOD_HANDLE:
        cp->method_handle_info.reference_kind  = b1Read(fd);
        cp->method_handle_info.reference_index = b2Read(fd);
        break;

      case CONSTANT_METHOD_TYPE:
        cp->method_type_info.descriptor_index = b2Read(fd);
        break;

      case CONSTANT_INVOKE_DYNAMIC:
        cp->invoke_dynamic_info.bootstrap_method_attr_index =
            b2Read(fd);
        cp->invoke_dynamic_info.name_and_type_index = b2Read(fd);
        break;

      default:
        break;
    }
  }
  return constant_pool;
}

bool isMagicValid(ClassFile *class_file){
  return class_file->magic == 0xCAFEBABE ? true : false;
}

void set_interface(File *fp, ClassFile *class_file){
    class_file->interfaces = (u2*) malloc(sizeof(u2) * class_file->interfaces_count);
    for (u2 i = 0; i < class_file->interfaces_count; i++) {
        class_file->interfaces[i] = b2Read(fp);
    }
}

void set_fields(File *fp, ClassFile *classFile) {
    classFile->fields = (FieldInfo*) malloc(sizeof(FieldInfo) * classFile->fields_count);
    for (u2 i = 0; i < classFile->fields_count; i++) {
        FieldInfo field;
        
        field.access_flag = b2Read(fp);
        field.name_index = b2Read(fp);
        field.descriptor_index = b2Read(fp);
        field.attributes_count = b2Read(fp);
        
        field.attributes = (AttributeInfo*) malloc(sizeof(AttributeInfo) * field.attributes_count);
        
        for (u2 j = 0; j < field.attributes_count; j++) {
            //field.attributes[j] = getAttributeInfo(fp, classFile);
        }
        
        classFile->fields[i] = field;
    }
}

void set_methods(File *fp, ClassFile *classFile) {
    classFile->methods = (MethodInfo*) malloc(sizeof(MethodInfo) * classFile->methods_count);
    for (u2 i = 0; i < classFile->methods_count; i++) {
        classFile->methods[i].access_flags = b2Read(fp);
        classFile->methods[i].name_index = b2Read(fp);
        classFile->methods[i].descriptor_index = b2Read(fp);
        classFile->methods[i].attributes_count = b2Read(fp);
        
        classFile->methods[i].attributes = (AttributeInfo*) malloc(sizeof(AttributeInfo) * classFile->methods[i].attributes_count);
        for (u2 j = 0; j < classFile->methods[i].attributes_count; j++) {
           //classFile->methods[i].attributes[j] = getAttributeInfo(fp, classFile);
         }
    }
}

ClassFile* readClassFile(File *fp, ConstantPoolInfo* cp){
  ClassFile *class_file = (ClassFile*) malloc(sizeof(ClassFile));

  class_file->magic = b4Read(fp);
  if(isMagicValid(class_file) == false){
    printf("Class Format Error - :\\ \n");
    exit(3);
  }

  class_file->minor_version = b2Read(fp);
  class_file->major_version = b2Read(fp);
  class_file-> constant_pool_count = b2Read(fp);
  readConstantPool2((class_file-> constant_pool_count), fp);
  class_file->access_flags = b2Read(fp);
  class_file->this_class = b2Read(fp);
  class_file->super_class = b2Read(fp);
  class_file->interfaces_count = b2Read(fp);
  set_interface(fp, class_file);
  class_file->fields_count = b2Read(fp);
  set_fields(fp, class_file);
  class_file->methods_count = b2Read(fp);
  set_methods(fp, class_file);
  class_file->attributes_count = b2Read(fp);
  class_file->attributes = readAttributes(class_file->attributes_count, fp, cp);

  return class_file;
}

int main(){
  return 0;
}
