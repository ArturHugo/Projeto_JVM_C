#include "class-file.h"
#include "fields.h"
#include "frame.h"
#include "global.h"
#include "map.h"
#include "methods.h"
#include "object.h"

#include <string.h>

static char* access_flag_table[16] = {"public",      // 0x1
                                      NULL,          // 0x2
                                      NULL,          // 0x4
                                      NULL,          // 0x8
                                      "final",       // 0x10
                                      "super",       // 0x20
                                      NULL,          // 0x40
                                      NULL,          // 0x80
                                      NULL,          // 0x100
                                      "interface",   // 0x200
                                      "abstract",    // 0x400
                                      NULL,          // 0x800
                                      "synthetic",   // 0x1000
                                      "annotation",  // 0x2000
                                      "enum",        // 0x4000
                                      NULL};         // 0x8000

void printAccessFlags(u2 access_flags) {
  for(int i = 0; i < 16; i++) {
    if((access_flags & 1) && (access_flag_table[i] != NULL)) {
      printf("%s ", access_flag_table[i]);
    }
    access_flags >>= 1;
  }
}

void printGeneralInfo(ClassFile* class_file) {
  printf("--------\nGeneral info:\n--------\n");
  printf("Minor version:       %d\n", class_file->minor_version);
  printf("Major version:       %d\n", class_file->major_version);
  printf("Constant pool count: %d\n", class_file->constant_pool_count);

  printf("Access flags:        0x%04x [", class_file->access_flags);
  printAccessFlags(class_file->access_flags);
  printf("]\n");

  u2 class_name_index = class_file->constant_pool[class_file->this_class].class_info.name_index;
  printf("This class:          cp_info #%d <%s>\n",
         class_file->this_class,
         class_file->constant_pool[class_name_index].utf8_info.bytes);

  class_name_index = class_file->constant_pool[class_file->super_class].class_info.name_index;
  printf("Super class:         cp_info #%d <%s>\n",
         class_file->this_class,
         class_file->constant_pool[class_name_index].utf8_info.bytes);

  printf("Interfaces count:    %d\n", class_file->interfaces_count);
  printf("Fields count:        %d\n", class_file->fields_count);
  printf("Methods count:       %d\n", class_file->methods_count);
  printf("Attrinbutes count:   %d\n", class_file->attributes_count);
}

int isVersionValid(u2 major_version) {
  if(major_version >= 46 && major_version <= 55)
    return 1;
  else
    return 0;
}

int isMagicValid(ClassFile* class_file) { return class_file->magic == 0xCAFEBABE ? 1 : 0; }

u2* readInterfaces(u2 interfaces_count, File* fd) {
  u2* interfaces = malloc(interfaces_count * sizeof(*interfaces));

  for(u2 i = 0; i < interfaces_count; i++) {
    interfaces[i] = u2Read(fd);
  }

  return interfaces;
}

void printInterfaces(u2 interfaces_count, u2* interfaces, ConstantPoolInfo* cp) {
  if(interfaces_count == 0)
    return;

  u1   num_of_strings = 0;
  u1** utf8_strings   = NULL;

  printf("-------\nInterfaces:\n-------\n");
  for(u2 i = 0; i < interfaces_count; i++) {
    printf("Interface %d: #%d ", i, interfaces[i]);
    utf8_strings = getUtf8Strings(&num_of_strings, cp, interfaces[i]);
    printf("<%s>\n", (char*) utf8_strings[0]);
  }
}

ClassFile* readClassFile(File* fd) {
  ClassFile* class_file = (ClassFile*) malloc(sizeof(ClassFile));

  class_file->magic = u4Read(fd);
  if(isMagicValid(class_file) == 0) {
    printf("Erro: nao tem cafebabe!\n");
    exit(2);
  }

  class_file->minor_version = u2Read(fd);
  class_file->major_version = u2Read(fd);
  if(!isVersionValid(class_file->major_version)) {
    printf("Erro: versao errada do Java!\n");
    exit(3);
  }
  class_file->constant_pool_count = u2Read(fd);
  class_file->constant_pool       = readConstantPool(class_file->constant_pool_count, fd);
  class_file->access_flags        = u2Read(fd);
  class_file->this_class          = u2Read(fd);
  class_file->super_class         = u2Read(fd);
  class_file->interfaces_count    = u2Read(fd);
  class_file->interfaces          = readInterfaces(class_file->interfaces_count, fd);
  class_file->fields_count        = u2Read(fd);
  class_file->fields        = readFields(class_file->fields_count, fd, class_file->constant_pool);
  class_file->methods_count = u2Read(fd);
  class_file->methods       = readMethods(class_file->methods_count, fd, class_file->constant_pool);
  class_file->attributes_count = u2Read(fd);
  class_file->attributes =
      readAttributes(class_file->attributes_count, fd, class_file->constant_pool);

  class_file->_status      = loaded;
  class_file->_super_class = NULL;

  return class_file;
}

void printClassFile(ClassFile* class_file) {
  printGeneralInfo(class_file);
  printConstantPool(class_file->constant_pool_count, class_file->constant_pool);
  printInterfaces(class_file->interfaces_count, class_file->interfaces, class_file->constant_pool);
  printFields(class_file->fields_count, class_file->fields, class_file->constant_pool);
  printMethods(class_file->methods_count, class_file->methods, class_file->constant_pool);
  printAttributes(class_file->attributes_count, class_file->attributes, class_file->constant_pool);
}

char* getSourceFile(ClassFile* class_file) {
  for(int i = 0; i < class_file->attributes_count; i++) {
    if(!strcmp(class_file->attributes[i]._attribute_name, "SourceFile")) {
      u2 index = class_file->attributes[i].source_file_info.sourcefile_index;
      return (char*) class_file->constant_pool[index].utf8_info.bytes;
    }
  }
  return NULL;
}

char* trimSuffix(char* file_path, char* suffix) {
  int   size = strlen(file_path) - strlen(suffix);
  char* name = calloc(size + 1, sizeof(char));
  memcpy(name, file_path, size);
  return name;
}

void loadObjectClass() {
  File* fd   = malloc(sizeof(*fd));
  fd->seek   = 0;
  fd->buffer = Object_class;

  ClassFile* class_file = readClassFile(fd);
  mapAdd(method_area.loaded_classes, "java/lang/Object", class_file);
  class_file->_status = initialized;
  free(fd);
}

Class* loadClass(char* class_name) {
  Class* class = mapGet(method_area.loaded_classes, class_name);

  if(!class) {
    int   class_name_length = strlen(class_name);
    char* file_path         = calloc(class_name_length + 7, sizeof(*file_path));
    strncpy(file_path, class_name, class_name_length);
    strcat(file_path, ".class");

    FILE* file = fopen(file_path, "rb");
    File* fd   = convertFile(file);
    fclose(file);

    class = readClassFile(fd);

    char* source_file_path = getSourceFile(class);
    char* source_file_name = trimSuffix(source_file_path, ".java");

    if(strcmp(source_file_name, class_name)) {
      printf("Em %s\n", class_name);
      printf("Erro: nome do source file e do class file sao diferentes!\n");
      exit(1);
    }

    // If current class is not loaded
    // Add to method_area
    mapAdd(method_area.loaded_classes, class_name, class);

    // If current class is not Object
    char* super_class_name = (char*) getUtf8String(class->constant_pool, class->super_class);

    free(fd->buffer);
    free(fd);
    free(source_file_name);

    // Load super class
    loadClass(super_class_name);

    // a razão pelo 1.5 é porque é perto do inverso do fator de carga para resize do map (0.7)
    class->_method_map = _newMap(class->methods_count * 1.5);
    class->_field_map  = _newMap(class->fields_count * 1.5);

    // popula o map de methods
    for(u2 index = 0; index < class->methods_count; index++) {
      MethodInfo* method      = class->methods + index;
      char*       method_name = (char*) getUtf8String(class->constant_pool, method->name_index);
      // TODO: if final, initialize it
      mapAdd(class->_method_map, method_name, method);
    }

    // popula o map de fields
    for(u2 index = 0; index < class->fields_count; index++) {
      FieldInfo* field      = class->fields + index;
      char*      field_name = (char*) getUtf8String(class->constant_pool, field->name_index);
      mapAdd(class->_field_map, field_name, field);
    }
  }

  return class;
}

/// Função para resolver referências da constant pool
void resolveReferences(ClassFile* class_file) {
  ConstantPoolInfo* cp = class_file->constant_pool;

  for(int i = 1; i < class_file->constant_pool_count; i++) {
    switch(cp[i].tag) {
      case CONSTANT_CLASS:
        cp[i].class_info._name = cp[cp[i].class_info.name_index].utf8_info.bytes;
        break;

      case CONSTANT_FIELDREF: {
        u2 name_and_type_index = cp[i].fieldref_info.name_and_type_index;

        u2 class_name_index        = cp[cp[i].fieldref_info.class_index].class_info.name_index;
        cp[i].fieldref_info._class = cp[class_name_index].utf8_info.bytes;

        u2 name_index             = cp[name_and_type_index].name_and_type_info.name_index;
        cp[i].fieldref_info._name = cp[name_index].utf8_info.bytes;

        u2 descriptor_index = cp[name_and_type_index].name_and_type_info.descriptor_index;
        cp[i].fieldref_info._descriptor = cp[descriptor_index].utf8_info.bytes;
      } break;

      case CONSTANT_METHODREF: {
        u2 name_and_type_index = cp[i].methodref_info.name_and_type_index;

        u2 class_name_index         = cp[cp[i].methodref_info.class_index].class_info.name_index;
        cp[i].methodref_info._class = cp[class_name_index].utf8_info.bytes;

        u2 descriptor_index = cp[name_and_type_index].name_and_type_info.descriptor_index;
        cp[i].methodref_info._descriptor = cp[descriptor_index].utf8_info.bytes;

        u2 name_index              = cp[name_and_type_index].name_and_type_info.name_index;
        cp[i].methodref_info._name = cp[name_index].utf8_info.bytes;
      } break;

      case CONSTANT_INTERFACE_METHODREF: {
        u2 name_and_type_index = cp[i].interface_methodref_info.name_and_type_index;

        u2 class_name_index = cp[cp[i].interface_methodref_info.class_index].class_info.name_index;
        cp[i].interface_methodref_info._interface = cp[class_name_index].utf8_info.bytes;

        u2 name_index = cp[name_and_type_index].name_and_type_info.name_index;
        cp[i].interface_methodref_info._name = cp[name_index].utf8_info.bytes;

        u2 descriptor_index = cp[name_and_type_index].name_and_type_info.descriptor_index;
        cp[i].interface_methodref_info._descriptor = cp[descriptor_index].utf8_info.bytes;
      } break;

      case CONSTANT_STRING:
        cp[i].string_info._value = cp[cp[i].string_info.string_index].utf8_info.bytes;
        break;

      default:
        break;
    }
  }

  if(class_file->super_class) {
    class_file->_super_class =
        mapGet(method_area.loaded_classes, (char*) cp[class_file->super_class].class_info._name);

    resolveReferences(class_file->_super_class);
  }
}

void initializeClass(Class* class) {
  if(class->_status == initialized)
    return;

  // Inicializa super classes recursivamente
  if(class->super_class) {
    initializeClass(class->_super_class);
  }

  /** FIXME da pra otimizar essa call */
  void* has_clinit = mapGet(class->_method_map, "<clinit>");

  /* executa clinit, se exisit */
  if(has_clinit) {
    Frame* frame = newFrame(class, "<clinit>");
    pushNode(&frame_stack, frame);
  }

  class->_status = initialized;
}
