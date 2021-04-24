#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/comparison.h"

void go_to() {
  Frame*   current_frame = peekNode(frame_stack);
  uint8_t* bytecode      = current_frame->current_method->attributes->code_info.code;

  int8_t  byte1        = bytecode[current_frame->local_pc + 1];
  int8_t  byte2        = bytecode[current_frame->local_pc + 2];
  int16_t branchOffset = ((int16_t) byte1 << 8) | byte2;

  current_frame->local_pc = current_frame->local_pc + branchOffset;
}

void jsr() {
  Frame*   current_frame = peekNode(frame_stack);
  uint8_t* bytecode      = current_frame->current_method->attributes->code_info.code;

  int8_t   byte1        = bytecode[current_frame->local_pc + 1];
  int8_t   byte2        = bytecode[current_frame->local_pc + 2];
  uint16_t branchOffset = ((int16_t) byte1 << 8) | byte2;
  JavaType return_address;

  return_address.return_address_value = current_frame->local_pc + 3;
  pushValue(&current_frame->operand_stack, return_address);
  current_frame->local_pc = current_frame->local_pc + branchOffset;
}

void ret() {
  Frame*   current_frame = peekNode(frame_stack);
  uint8_t* bytecode      = current_frame->current_method->attributes->code_info.code;
  int8_t   index         = bytecode[current_frame->local_pc + 1];

  JavaType value;
  value                   = current_frame->local_variables[index];
  current_frame->local_pc = current_frame->local_pc + value.return_address_value;
}

void ireturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT1;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}

void lreturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT2;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}

void freturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT1;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}

void dreturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT2;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}

void areturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT1;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}

void return_op() {
  Frame* old_frame = popNode(&frame_stack);
  free(old_frame);
}

void lookupswitch() {
  JavaType key;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &key);
  uint32_t address = current_frame->local_pc;

  current_frame->local_pc++;
  while((current_frame->local_pc) % 4 != 0) {
    current_frame->local_pc++;
  }

  uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;

  int8_t  byte1         = bytecode[current_frame->local_pc++];
  int8_t  byte2         = bytecode[current_frame->local_pc++];
  int8_t  byte3         = bytecode[current_frame->local_pc++];
  int8_t  byte4         = bytecode[current_frame->local_pc++];
  int16_t default_value = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

  int8_t  byte5 = bytecode[current_frame->local_pc++];
  int8_t  byte6 = bytecode[current_frame->local_pc++];
  int8_t  byte7 = bytecode[current_frame->local_pc++];
  int8_t  byte8 = bytecode[current_frame->local_pc++];
  int16_t pairs = (byte5 << 24) | (byte6 << 16) | (byte7 << 8) | byte8;

  for(int i = 0; i < pairs; i++) {
    int8_t  match_byte1 = bytecode[current_frame->local_pc++];
    int8_t  match_byte2 = bytecode[current_frame->local_pc++];
    int8_t  match_byte3 = bytecode[current_frame->local_pc++];
    int8_t  match_byte4 = bytecode[current_frame->local_pc++];
    int32_t match = (match_byte1 << 24) | (match_byte2 << 16) | (match_byte3 << 8) | match_byte4;

    int8_t  offset_byte1 = bytecode[current_frame->local_pc++];
    int8_t  offset_byte2 = bytecode[current_frame->local_pc++];
    int8_t  offset_byte3 = bytecode[current_frame->local_pc++];
    int8_t  offset_byte4 = bytecode[current_frame->local_pc++];
    int32_t offset =
        (offset_byte1 << 24) | (offset_byte2 << 16) | (offset_byte3 << 8) | offset_byte4;

    if((int32_t) key.int_value == match) {
      current_frame->local_pc = address + offset;
      return;
    }
  }
  current_frame->local_pc = address + default_value;
}

void tableswitch() {
  JavaType key;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &key);
  uint32_t address = current_frame->local_pc;

  current_frame->local_pc++;
  while((current_frame->local_pc) % 4 != 0) {
    current_frame->local_pc++;
  }

  uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;

  int8_t  byte1         = bytecode[current_frame->local_pc++];
  int8_t  byte2         = bytecode[current_frame->local_pc++];
  int8_t  byte3         = bytecode[current_frame->local_pc++];
  int8_t  byte4         = bytecode[current_frame->local_pc++];
  int16_t default_value = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

  int8_t  low_byte1 = bytecode[current_frame->local_pc++];
  int8_t  low_byte2 = bytecode[current_frame->local_pc++];
  int8_t  low_byte3 = bytecode[current_frame->local_pc++];
  int8_t  low_byte4 = bytecode[current_frame->local_pc++];
  int16_t low_bytes = (low_byte1 << 24) | (low_byte2 << 16) | (low_byte3 << 8) | low_byte4;

  int8_t  high_bytes1 = bytecode[current_frame->local_pc++];
  int8_t  high_bytes2 = bytecode[current_frame->local_pc++];
  int8_t  high_bytes3 = bytecode[current_frame->local_pc++];
  int8_t  high_bytes4 = bytecode[current_frame->local_pc++];
  int32_t high_bytes = (high_bytes1 << 24) | (high_bytes2 << 16) | (high_bytes3 << 8) | high_bytes4;

  for(int match = low_bytes; match <= high_bytes; match++) {
    int8_t  offset_byte1 = bytecode[current_frame->local_pc++];
    int8_t  offset_byte2 = bytecode[current_frame->local_pc++];
    int8_t  offset_byte3 = bytecode[current_frame->local_pc++];
    int8_t  offset_byte4 = bytecode[current_frame->local_pc++];
    int32_t offset =
        (offset_byte1 << 24) | (offset_byte2 << 16) | (offset_byte3 << 8) | offset_byte4;

    if((int32_t) key.int_value == match) {
      current_frame->local_pc = address + offset;
      return;
    }
  }
  current_frame->local_pc = address + default_value;
}