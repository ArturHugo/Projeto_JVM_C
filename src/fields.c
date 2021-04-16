#include "fields.h"
#include "class-file.h"
#include "constant-pool.h"

static char* access_flag_table[16] = {"public",     // 0x1
                                      "private",    // 0x2
                                      "protected",  // 0x4
                                      "static",     // 0x8
                                      "final",      // 0x10
                                      NULL,         // 0x20
                                      "volatile",   // 0x40
                                      "transient",  // 0x80
                                      NULL,         // 0x100
                                      NULL,         // 0x200
                                      NULL,         // 0x400
                                      NULL,         // 0x800
                                      "synthetic",  // 0x1000
                                      NULL,         // 0x2000
                                      "enum",       // 0x4000
                                      NULL};        // 0x8000

void printFieldAccessFlags(u2 access_flags) {
  for(int i = 0; i < 16; i++) {
    if((access_flags & 1) && (access_flag_table[i] != NULL)) {
      printf("%s ", access_flag_table[i]);
    }
    access_flags >>= 1;
  }
}

FieldInfo* readFields(u2 fields_count, File* fd, ConstantPoolInfo* cp) {
  FieldInfo* fields = malloc(fields_count * sizeof(*fields));
  for(u2 i = 0; i < fields_count; i++) {
    FieldInfo field;

    field.access_flags     = u2Read(fd);
    field.name_index       = u2Read(fd);
    field.descriptor_index = u2Read(fd);
    field.attributes_count = u2Read(fd);

    field.attributes = readAttributes(field.attributes_count, fd, cp);

    fields[i] = field;
  }
  return fields;
}

void printFields(u2 fields_count, FieldInfo* fields, ConstantPoolInfo* cp) {
  printf("----------\n  Fields  \n----------\n");
  printf("Field count: %u\n", fields_count);
  for(u2 i = 0; i < fields_count; i++) {
    printf("Field number: [%d]\n", i);
    printf("\tName:             cp_info #%d\n", fields[i].name_index);
    printf("\tDescriptor_index: cp_info #%d\n", fields[i].descriptor_index);
    printf("\tAcess flag:       0x%04x ", fields[i].access_flags);
    printFieldAccessFlags(fields[i].access_flags);
    printf("\n");
    printf("\tAttributes_count: %d\n", fields[i].attributes_count);

    printAttributes(fields[i].attributes_count, fields[i].attributes, cp);
  }
  printf("\n");
}
