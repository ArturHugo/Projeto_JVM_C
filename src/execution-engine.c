#include "execution-engine.h"

void noop() {
  Frame* current_frame = peekNode(frame_stack);
  current_frame->local_pc++;
}

void (*const instructions_handlers[256])(const u1*) = {
    /* 0x00 */ nop,
    /* 0x01 */ aconst_null,
    /* 0x02 */ iconst_n,
    /* 0x03 */ iconst_n,
    /* 0x04 */ iconst_n,
    /* 0x05 */ iconst_n,
    /* 0x06 */ iconst_n,
    /* 0x07 */ iconst_n,
    /* 0x08 */ iconst_n,
    /* 0x09 */ lconst_n,
    /* 0x0a */ lconst_n,
    /* 0x0b */ fconst_n,
    /* 0x0c */ fconst_n,
    /* 0x0d */ fconst_n,
    /* 0x0e */ dconst_n,
    /* 0x0f */ dconst_n,
    /* 0x10 */ bipush,
    /* 0x11 */ sipush,
    /* 0x12 */ ldc,
    /* 0x13 */ ldc,
    /* 0x14 */ ldc2_w,
    /* 0x15 */ tload,
    /* 0x16 */ tload,
    /* 0x17 */ tload,
    /* 0x18 */ tload,
    /* 0x19 */ tload,
    /* 0x1a */ iload_n,
    /* 0x1b */ iload_n,
    /* 0x1c */ iload_n,
    /* 0x1d */ iload_n,
    /* 0x1e */ lload_n,
    /* 0x1f */ lload_n,
    /* 0x20 */ lload_n,
    /* 0x21 */ lload_n,
    /* 0x22 */ fload_n,
    /* 0x23 */ fload_n,
    /* 0x24 */ fload_n,
    /* 0x25 */ fload_n,
    /* 0x26 */ dload_n,
    /* 0x27 */ dload_n,
    /* 0x28 */ dload_n,
    /* 0x29 */ dload_n,
    /* 0x2a */ aload_n,
    /* 0x2b */ aload_n,
    /* 0x2c */ aload_n,
    /* 0x2d */ aload_n,
    /* 0x2e */ taload,
    /* 0x2f */ taload,
    /* 0x30 */ taload,
    /* 0x31 */ taload,
    /* 0x32 */ taload,
    /* 0x33 */ taload,
    /* 0x34 */ taload,
    /* 0x35 */ NULL,
    /* 0x36 */ tstore,
    /* 0x37 */ tstore,
    /* 0x38 */ tstore,
    /* 0x39 */ tstore,
    /* 0x3a */ tstore,
    /* 0x3b */ istore_n,
    /* 0x3c */ istore_n,
    /* 0x3d */ istore_n,
    /* 0x3e */ istore_n,
    /* 0x3f */ lstore_n,
    /* 0x40 */ lstore_n,
    /* 0x41 */ lstore_n,
    /* 0x42 */ lstore_n,
    /* 0x43 */ fstore_n,
    /* 0x44 */ fstore_n,
    /* 0x45 */ fstore_n,
    /* 0x46 */ fstore_n,
    /* 0x47 */ dstore_n,
    /* 0x48 */ dstore_n,
    /* 0x49 */ dstore_n,
    /* 0x4a */ dstore_n,
    /* 0x4b */ astore_n,
    /* 0x4c */ astore_n,
    /* 0x4d */ astore_n,
    /* 0x4e */ astore_n,
    /* 0x4f */ tastore,
    /* 0x50 */ tastore,
    /* 0x51 */ tastore,
    /* 0x52 */ tastore,
    /* 0x53 */ tastore,
    /* 0x54 */ tastore,
    /* 0x55 */ tastore,
    /* 0x56 */ tastore,
    /* 0x57 */ pop_instruction,
    /* 0x58 */ pop2,
    /* 0x59 */ dup_instruction,
    /* 0x5a */ dup_x1,
    /* 0x5b */ dup_x2,
    /* 0x5c */ dup2_instruction,
    /* 0x5d */ dup2_x1,
    /* 0x5e */ dup2_x2,
    /* 0x5f */ swap,
    /* 0x60 */ NULL,
    /* 0x61 */ NULL,
    /* 0x62 */ NULL,
    /* 0x63 */ NULL,
    /* 0x64 */ NULL,
    /* 0x65 */ NULL,
    /* 0x66 */ NULL,
    /* 0x67 */ NULL,
    /* 0x68 */ NULL,
    /* 0x69 */ NULL,
    /* 0x6a */ NULL,
    /* 0x6b */ NULL,
    /* 0x6c */ NULL,
    /* 0x6d */ NULL,
    /* 0x6e */ NULL,
    /* 0x6f */ NULL,
    /* 0x70 */ NULL,
    /* 0x71 */ NULL,
    /* 0x72 */ NULL,
    /* 0x73 */ NULL,
    /* 0x74 */ NULL,
    /* 0x75 */ NULL,
    /* 0x76 */ NULL,
    /* 0x77 */ NULL,
    /* 0x78 */ NULL,
    /* 0x79 */ NULL,
    /* 0x7a */ NULL,
    /* 0x7b */ NULL,
    /* 0x7c */ NULL,
    /* 0x7d */ NULL,
    /* 0x7e */ NULL,
    /* 0x7f */ NULL,
    /* 0x80 */ NULL,
    /* 0x81 */ NULL,
    /* 0x82 */ NULL,
    /* 0x83 */ NULL,
    /* 0x84 */ NULL,
    /* 0x85 */ noop,
    /* 0x86 */ l2f,
    /* 0x87 */ l2d,
    /* 0x88 */ noop,
    /* 0x89 */ l2f,
    /* 0x8a */ l2d,
    /* 0x8b */ f2l,
    /* 0x8c */ f2l,
    /* 0x8d */ f2d,
    /* 0x8e */ d2l,
    /* 0x8f */ d2l,
    /* 0x90 */ d2f,
    /* 0x91 */ i2b,
    /* 0x92 */ i2c,
    /* 0x93 */ i2s,
    /* 0x94 */ NULL,
    /* 0x95 */ NULL,
    /* 0x96 */ NULL,
    /* 0x97 */ NULL,
    /* 0x98 */ NULL,
    /* 0x99 */ NULL,
    /* 0x9a */ NULL,
    /* 0x9b */ NULL,
    /* 0x9c */ NULL,
    /* 0x9d */ NULL,
    /* 0x9e */ NULL,
    /* 0x9f */ NULL,
    /* 0xa0 */ NULL,
    /* 0xa1 */ NULL,
    /* 0xa2 */ NULL,
    /* 0xa3 */ NULL,
    /* 0xa4 */ NULL,
    /* 0xa5 */ NULL,
    /* 0xa6 */ NULL,
    /* 0xa7 */ NULL,
    /* 0xa8 */ NULL,
    /* 0xa9 */ NULL,
    /* 0xaa */ NULL,
    /* 0xab */ NULL,
    /* 0xac */ NULL,
    /* 0xad */ NULL,
    /* 0xae */ NULL,
    /* 0xaf */ NULL,
    /* 0xb0 */ NULL,
    /* 0xb1 */ NULL,
    /* 0xb2 */ getstatic,
    /* 0xb3 */ putstatic,
    /* 0xb4 */ getfield,
    /* 0xb5 */ putfield,
    /* 0xb6 */ NULL,
    /* 0xb7 */ NULL,
    /* 0xb8 */ invokestatic,
    /* 0xb9 */ NULL,
    /* 0xba */ NULL,
    /* 0xbb */ new,
    /* 0xbc */ newarray,
    /* 0xbd */ anewarray,
    /* 0xbe */ arraylength,
    /* 0xbf */ NULL,
    /* 0xc0 */ NULL,
    /* 0xc1 */ NULL,
    /* 0xc2 */ NULL,
    /* 0xc3 */ NULL,
    /* 0xc4 */ NULL,
    /* 0xc5 */ NULL,
    /* 0xc6 */ NULL,
    /* 0xc7 */ NULL,
    /* 0xc8 */ NULL,
    /* 0xc9 */ NULL,
    /* 0xca */ NULL,
    /* 0xcb */ NULL,
    /* 0xcc */ NULL,
    /* 0xcd */ NULL,
    /* 0xce */ NULL,
    /* 0xcf */ NULL,
    /* 0xd0 */ NULL,
    /* 0xd1 */ NULL,
    /* 0xd2 */ NULL,
    /* 0xd3 */ NULL,
    /* 0xd4 */ NULL,
    /* 0xd5 */ NULL,
    /* 0xd6 */ NULL,
    /* 0xd7 */ NULL,
    /* 0xd8 */ NULL,
    /* 0xd9 */ NULL,
    /* 0xda */ NULL,
    /* 0xdb */ NULL,
    /* 0xdc */ NULL,
    /* 0xdd */ NULL,
    /* 0xde */ NULL,
    /* 0xdf */ NULL,
    /* 0xe0 */ NULL,
    /* 0xe1 */ NULL,
    /* 0xe2 */ NULL,
    /* 0xe3 */ NULL,
    /* 0xe4 */ NULL,
    /* 0xe5 */ NULL,
    /* 0xe6 */ NULL,
    /* 0xe7 */ NULL,
    /* 0xe8 */ NULL,
    /* 0xe9 */ NULL,
    /* 0xea */ NULL,
    /* 0xeb */ NULL,
    /* 0xec */ NULL,
    /* 0xed */ NULL,
    /* 0xee */ NULL,
    /* 0xef */ NULL,
    /* 0xf0 */ NULL,
    /* 0xf1 */ NULL,
    /* 0xf2 */ NULL,
    /* 0xf3 */ NULL,
    /* 0xf4 */ NULL,
    /* 0xf5 */ NULL,
    /* 0xf6 */ NULL,
    /* 0xf7 */ NULL,
    /* 0xf8 */ NULL,
    /* 0xf9 */ NULL,
    /* 0xfa */ NULL,
    /* 0xfb */ NULL,
    /* 0xfc */ NULL,
    /* 0xfd */ NULL,
    /* 0xfe */ NULL,
    /* 0xff */ NULL,
};

void run(char* starting_class_name) {
  frame_stack = NULL;

  // execution engine
  ClassFile* starting_class = mapGet(method_area.loaded_classes, starting_class_name);
  initializeClass(starting_class);

  // criando frame
  Frame* starting_frame;
  starting_frame = newFrame(starting_class, "main");

  // empilhando primeiro frame
  pushNode(&frame_stack, starting_frame);

  /*
  1) iniciar stack de frames com um frame contendo o método main da classe inicial

  2) handler das instruções invoke empilham um frame

  3) no while, o frame "no controle" eh o do topo da pilha

  */

  while(peekNode(frame_stack)) {
    Frame* current_frame        = (Frame*) peekNode(frame_stack);
    u1*    current_instructions = current_frame->current_method->attributes[0].code_info.code;
    u1*    current_instruction  = current_instructions + current_frame->local_pc;
    // void (*instruction)(u1*)        = instructions_handlers[*current_instruction];
    void (*instruction)(const u1*) = instructions_handlers[0];
    instruction(current_instruction);
  }
}