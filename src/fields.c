#include "fields.h"
#include "class-file.h"
#include "constant-pool.h"
#include <inttypes.h>

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
    printf("    Name: cp_info #%" PRIu16 "\n", fields[i].name_index);
    printf("    Descriptor_index: cp_info #%" PRIu16 "\n", fields[i].descriptor_index);
    if(fields[i].access_flags < 10)
      printf("    Acess flag: 0x000%" PRIu16 "\n", fields[i].access_flags);
    else
      printf("    Acess flag: 0x00%" PRIu16 "\n", fields[i].access_flags);

    printf("    Attributes_count: %" PRIu16 "\n", fields[i].attributes_count);

    printAttributes(fields[i].attributes_count, fields[i].attributes, cp);
  }
  printf("\n");
}