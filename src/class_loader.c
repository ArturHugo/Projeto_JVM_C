#include "class-file.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Attribute types for string comparisson
static const char CONSTANT_VALUE[]       = "ConstantValue";
static const char CODE[]                 = "Code";
static const char EXCEPTIONS[]           = "Exceptions";
static const char INNER_CLASSES[]        = "InnerClasses";
static const char SOURCE_FILE[]          = "SourceFile";
static const char LINE_NUMBER_TABLE[]    = "LineNumberTable";
static const char LOCAL_VARIABLE_TABLE[] = "LocalVariableTable";
static const char STACK_MAP_TABLE[]      = "StackMapTable";

u1 b1Read(FILE* fd) {
  u1 result = 0;
  fread(&result, sizeof(u1), 1, fd);
  return result;
}

u2 b2Read(FILE* fd) {
  u2 toReturn = b1Read(fd);
  toReturn    = (toReturn << 8) | (b1Read(fd));
  return toReturn;
}

u4 b4Read(FILE* fd) {
  u4 toReturn = b2Read(fd);
  toReturn    = (toReturn << 16) | (b2Read(fd));
  return toReturn;
}

u1 u1Read(File* fd) { return fd->buffer[fd->seek++]; }

u2 u2Read(File* fd) {
  u2 toReturn = u1Read(fd);
  toReturn    = (toReturn << 8) | (u1Read(fd));
  return toReturn;
}

u4 u4Read(File* fd) {
  u4 toReturn = u2Read(fd);
  toReturn    = (toReturn << 16) | (u2Read(fd));
  return toReturn;
}

AttributeInfo* readAttributes(u2                attributes_count,
                              File*             fd,
                              ConstantPoolInfo* cp) {
  AttributeInfo* attributes =
      malloc((attributes_count) * sizeof(*attributes));

  AttributeInfo* attribute;
  for(attribute = attributes;
      attribute < attributes + attributes_count;
      attribute++) {
    attribute->attribute_name_index = u2Read(fd);
    attribute->attribute_length     = u4Read(fd);

    // TODO: check if index is on range
    ConstantPoolInfo attribute_name_reference =
        cp[attribute->attribute_name_index];

    u1* attribute_name = attribute_name_reference.utf8_info.bytes;
    u2  attribute_name_size =
        attribute_name_reference.utf8_info.length;

    // TODO: Substituir memcmp por strcmp e adicionar nullbyte ao
    // final dos bytes do CONSTANT_UTF8_info
    if(!strcmp((char*) attribute_name, CONSTANT_VALUE)) {
      attribute->constant_value_info.constant_value_index =
          u2Read(fd);
    } else if(!strcmp((char*) attribute_name, CODE)) {
      attribute->code_info.max_stack  = u2Read(fd);
      attribute->code_info.max_locals = u2Read(fd);

      // Read code
      attribute->code_info.code_length = u4Read(fd);
      u1* code =
          malloc(attribute->code_info.code_length * sizeof(u1));
      attribute->code_info.code = code;

      for(; code < attribute->code_info.code_length +
                       attribute->code_info.code;
          code++)
        *code = u1Read(fd);

      // Read exception_table
      attribute->code_info.exception_table_length = u2Read(fd);
      ExceptionTable* exception_table =
          malloc(attribute->code_info.exception_table_length *
                 sizeof(ExceptionTable));
      attribute->code_info.exception_table = exception_table;
      for(; exception_table <
            attribute->code_info.exception_table_length +
                attribute->code_info.exception_table;
          exception_table++) {
        exception_table->start_pc   = u2Read(fd);
        exception_table->end_pc     = u2Read(fd);
        exception_table->handler_pc = u2Read(fd);
        exception_table->catch_type = u2Read(fd);
      }

      // Read code attributes (recusive)
      attribute->code_info.attributes_count = u2Read(fd);
      attribute->code_info.atttributes =
          readAttributes(attribute->code_info.attributes_count,
                         fd,
                         cp);

    } else if(!strcmp((char*) attribute_name, EXCEPTIONS)) {
      attribute->exceptions_info.number_of_exceptions = u2Read(fd);
      u2* exception =
          malloc(attribute->exceptions_info.number_of_exceptions *
                 sizeof(*exception));
      attribute->exceptions_info.exception_index_table = exception;

      for(; exception <
            attribute->exceptions_info.exception_index_table +
                attribute->exceptions_info.number_of_exceptions;
          exception++) {
        *exception = u2Read(fd);
      }

    } else if(!strcmp((char*) attribute_name, INNER_CLASSES)) {
      u2 number_of_classes = u2Read(fd);
      attribute->inner_classes_info.number_of_classes =
          number_of_classes;

      InnerClass* classes =
          malloc(number_of_classes * sizeof(*classes));

      InnerClass* current_class = classes;
      while(number_of_classes--) {
        current_class->inner_class_info_index   = u2Read(fd);
        current_class->outer_class_info_index   = u2Read(fd);
        current_class->inner_name_index         = u2Read(fd);
        current_class->inner_class_access_flags = u2Read(fd);
        current_class++;
      }

      attribute->inner_classes_info.classes = classes;
    } else if(!strcmp((char*) attribute_name, SOURCE_FILE)) {
      attribute->source_file_info.sourcefile_index = u2Read(fd);
    } else if(!strcmp((char*) attribute_name, LINE_NUMBER_TABLE)) {
      u2 line_number_table_length = u2Read(fd);
      attribute->line_number_table_info.line_number_table_length =
          line_number_table_length;

      LineNumber* line_number_table = malloc(
          line_number_table_length * sizeof(*line_number_table));
      LineNumber* current_line_number = line_number_table;
      while(line_number_table_length--) {
        current_line_number->start_pc    = u2Read(fd);
        current_line_number->line_number = u2Read(fd);
        current_line_number++;
      }

      attribute->line_number_table_info.line_number_table =
          line_number_table;
    } else if(!memcmp(attribute_name,
                      LOCAL_VARIABLE_TABLE,
                      attribute_name_size)) {
      // TODO: handle LocalVariableTableInfo
      fd->seek += attribute->attribute_length;
    } else if(!strcmp((char*) attribute_name, STACK_MAP_TABLE)) {
      // TODO: handle StackMapTableInfo
      fd->seek += attribute->attribute_length;
    } else {
      // Ignore silently unkown attributes
      fd->seek += attribute->attribute_length;
    }
  }

  return attributes;
}

ConstantPoolInfo* readConstantPool(u2 cp_count, FILE* fd) {
  ConstantPoolInfo* constant_pool = (ConstantPoolInfo*) malloc(
      (cp_count) * sizeof(ConstantPoolInfo));

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

int isVersionValid(u2 major_version) {
  if(major_version >= 46 && major_version <= 55)
    return 1;
  else
    return 0;
}

int isMagicValid(ClassFile* class_file) {
  return class_file->magic == 0xCAFEBABE ? 1 : 0;
}

void set_interface(FILE* fp, ClassFile* class_file) {
  class_file->interfaces =
      (u2*) malloc(sizeof(u2) * class_file->interfaces_count);
  for(u2 i = 0; i < class_file->interfaces_count; i++) {
    class_file->interfaces[i] = b2Read(fp);
  }
}

void set_fields(FILE*             fp,
                ClassFile*        classFile,
                ConstantPoolInfo* cp) {
  classFile->fields = (FieldInfo*) malloc(sizeof(FieldInfo) *
                                          classFile->fields_count);
  for(u2 i = 0; i < classFile->fields_count; i++) {
    FieldInfo field;

    field.access_flag      = b2Read(fp);
    field.name_index       = b2Read(fp);
    field.descriptor_index = b2Read(fp);
    field.attributes_count = b2Read(fp);
    /*
            printf("--->acess flag %" PRIu16 "\n",field.access_flag);
            printf("--->name_index %" PRIu16 "\n",field.name_index);
            printf("--->descriptor_index %" PRIu16 "\n",
       field.descriptor_index); printf("--->attributes_count %" PRIu16
       "\n", field.attributes_count);
    */

    field.attributes = (AttributeInfo*) malloc(
        sizeof(AttributeInfo) * field.attributes_count);
    if(field.attributes_count > 0) {
      /*File* fd = convert(fp);
field.attributes = readAttributes(field.attributes_count, fd, cp);*/
    }

    classFile->fields[i] = field;
  }
}

void set_methods(FILE*             fp,
                 ClassFile*        classFile,
                 ConstantPoolInfo* cp) {
  classFile->methods = (MethodInfo*) malloc(sizeof(MethodInfo) *
                                            classFile->methods_count);
  for(u2 i = 0; i < classFile->methods_count; i++) {
    classFile->methods[i].access_flags     = b2Read(fp);
    classFile->methods[i].name_index       = b2Read(fp);
    classFile->methods[i].descriptor_index = b2Read(fp);
    classFile->methods[i].attributes_count = b2Read(fp);

    /*printf("--->acess flag:");
printf("%" PRIu16 "\n",classFile->methods[i].access_flags);
printf("--->name index:");
printf("%" PRIu16 "\n",classFile->methods[i].name_index);
printf("--->descriptor_index:");
printf("%" PRIu16 "\n",classFile->methods[i].descriptor_index);
printf("--->attributes_count:");
printf("%" PRIu16 "\n",classFile->methods[i].attributes_count);    */

    classFile->methods[i].attributes = (AttributeInfo*) malloc(
        sizeof(AttributeInfo) *
        classFile->methods[i].attributes_count);
    File* fd = convert(fp);
    if(classFile->methods[i].attributes_count > 0) {
      // PERGUNTAR PROS MLK
      // classFile->methods[i].attributes =
      // readAttributes(classFile->methods[i].attributes_count, fd ,
      // cp);
    }
  }
}

ClassFile* readClassFile(FILE* fp) {
  ClassFile* class_file = (ClassFile*) malloc(sizeof(ClassFile));

  class_file->magic = b4Read(fp);
  if(isMagicValid(class_file) == 0) {
    printf("Class Format Error \n");
    exit(2);
  }

  class_file->minor_version = b2Read(fp);
  class_file->major_version = b2Read(fp);
  if(!isVersionValid(class_file->major_version)) {
    printf("Java version is invalid");
    exit(3);
  }
  class_file->constant_pool_count = b2Read(fp);
  ConstantPoolInfo* cp =
      readConstantPool(class_file->constant_pool_count, fp);
  class_file->access_flags     = b2Read(fp);
  class_file->this_class       = b2Read(fp);
  class_file->super_class      = b2Read(fp);
  class_file->interfaces_count = b2Read(fp);
  set_interface(fp, class_file);
  class_file->fields_count = b2Read(fp);
  set_fields(fp, class_file, cp);
  class_file->methods_count = b2Read(fp);
  set_methods(fp, class_file, cp);
  class_file->attributes_count = b2Read(fp);
  // class_file->attributes =
  // readAttributes(class_file->attributes_count, fp, cp);

  return class_file;
}

static void printFields(FILE* stream, ClassFile* class_file) {
  fprintf(stream, "**********\n* Fields *\n**********\n");
  fprintf(stream, "Field count: %u\n", class_file->fields_count);
  for(u2 i = 0; i < class_file->fields_count; i++) {
    fprintf(stream, "Field Number %d\n", i);
    fprintf(stream,
            "--->acess flag %" PRIu16 "\n",
            class_file->fields[i].access_flag);
    fprintf(stream,
            "--->name_index %" PRIu16 "\n",
            class_file->fields[i].name_index);
    fprintf(stream,
            "--->descriptor_index %" PRIu16 "\n",
            class_file->fields[i].descriptor_index);
    fprintf(stream,
            "--->attributes_count %" PRIu16 "\n",
            class_file->fields[i].attributes_count);
  }
  fprintf(stream, "\n");
}
static void printMethods(FILE* stream, ClassFile* class_file) {
  fprintf(stream, "**********\n* Methods *\n**********\n");
  fprintf(stream, "methods_count: %u\n", class_file->methods_count);
  for(u2 i = 0; i < class_file->methods_count; i++) {
    fprintf(stream, "Method Number %d\n", i);
    fprintf(stream,
            "--->acess flag %" PRIu16 "\n",
            class_file->methods[i].access_flags);
    fprintf(stream,
            "--->name_index %" PRIu16 "\n",
            class_file->methods[i].name_index);
    fprintf(stream,
            "--->descriptor_index %" PRIu16 "\n",
            class_file->methods[i].descriptor_index);
    fprintf(stream,
            "--->attributes_count %" PRIu16 "\n",
            class_file->methods[i].attributes_count);
  }
  fprintf(stream, "\n");
}

int main() {

  FILE*      file       = fopen("HelloWorld.class", "rb");
  ClassFile* JAVA_CLASS = readClassFile(file);
  FILE*      out        = fopen("output.txt", "w+");
  printMethods(out, JAVA_CLASS);
  fclose(file);
  return (0);
}
