#include "handlers/extended.h"
#include "frame.h"
#include "global.h"

// Widened instructions
void wide_tload(const u1* instruction);
void wide_tstore(const u1* instruction);
void wide_ret(const u1* instruction);
void wide_iinc(const u1* instruction);

// Auxiliary function to multianewarray
void multianewarray_aux(Array*    current_array_ref,
                        JavaType* counts,
                        int       dimensions,
                        int       current_dimension);

/*
 * format 1:  [wide, <opcode>, indexbyte1, indexbyte2]
 * format 2:  [wide, iinc, indexbyte1, indexbyte2, constbyte1, constbyte2]
 * stack:     same as modified instruction
 * description: takes value of type t from local_variables[index]
 * and pushes into the operand stack.
 */
void wide(const u1* instruction) {
  const u1* widened_instruction = instruction + 1;
  if(*widened_instruction >= 0x15 && *widened_instruction <= 0x19) {
    // tload
    wide_tload(widened_instruction);
  } else if(*widened_instruction >= 0x36 && *widened_instruction <= 0x3a) {
    // tstore
    wide_tstore(widened_instruction);
  } else if(*widened_instruction == 0xa9) {
    // ret
    wide_ret(widened_instruction);
  } else if(*widened_instruction == 0x84) {
    // iinc
    wide_iinc(widened_instruction);
  }
}

/*
 * format:  [multianewarray, indexbyte1, indexbyte2, dimensions]
 * stack:   (..., count1, [count2, ...]) -> (..., arrayref)
 * description: pops a number of count values from the operand stack equals to the
 * number of dimensions. Looks for an array, class or interface symbolic reference
 * into current frame's constant pool at the index formed
 * by (indexbyte1 << 8) | indexbyte2. Resolves that reference and checks if the
 * dimensionality is at least of dimensions. Then proceeds to allocate a new multiarray:
 * an array with count1 elements of type reference that are references to arrays
 * with count2 elements and so on.
 */
// FIXME ainda não ta funcionando
void multianewarray(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  u2 wide_index = (operands[0] << 8) | operands[1];
  u1 dimensions = operands[2];

  JavaType* counts = malloc(dimensions * sizeof(JavaType));
  for(int i = dimensions - 1; i >= 0; i--) {
    popValue(&current_frame->operand_stack, &counts[i]);
    if(counts[i].int_value < 0) {
      printf("NegativeArraySizeException at %x", current_frame->local_pc);
      exit(1);
    }
  }

  // TODO tem que fazer alguma coisa com os indexbytes? A gente ja tava
  // resolvendo as referencias simbolicas internas em tempo de carregamento né?
  // No exemplo que eu to testando (multi.class), essa referencia é pra classe
  // [[java/lang/String;. Faz sentido resolver isso como uma referência externa?

  // char* array_name = current_frame->constant_pool[wide_index].class_info._name;

  Array multiarray;
  multianewarray_aux(&multiarray, counts, dimensions, 0);

  JavaType array_ref = {.cat_tag = CAT1, .reference_value = &multiarray};
  pushValue(&current_frame->operand_stack, array_ref);

  free(counts);
}

void ifnull(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  int16_t wide_branch = (operands[0] << 8) | operands[1];

  JavaType value;
  popValue(&current_frame->operand_stack, &value);

  if(value.reference_value == NULL) {
    current_frame->local_pc += wide_branch;
  } else {
    current_frame->local_pc += 3;
  }
}

void ifnonnull(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  int16_t wide_branch = (operands[0] << 8) | operands[1];

  JavaType value;
  popValue(&current_frame->operand_stack, &value);

  if(value.reference_value != NULL) {
    current_frame->local_pc += wide_branch;
  } else {
    current_frame->local_pc += 3;
  }
}

void goto_w(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  int64_t superwide_branch =
      (operands[0] << 24) | (operands[1] << 16) | (operands[2] << 8) | operands[3];

  current_frame->local_pc += superwide_branch;
}

void jsr_w(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  int64_t superwide_branch =
      (operands[0] << 24) | (operands[1] << 16) | (operands[2] << 8) | operands[3];

  JavaType return_address = {.cat_tag = CAT1, .return_address_value = current_frame->local_pc + 1};
  pushValue(&current_frame->operand_stack, return_address);

  current_frame->local_pc += superwide_branch;
}

// Implementation of widened instructions
void wide_tload(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  u2 wide_index = (operands[0] << 8) | operands[1];

  pushValue(&current_frame->operand_stack, current_frame->local_variables[wide_index]);
  current_frame->local_pc += 4;
}

void wide_tstore(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  u2 wide_index = (operands[0] << 8) | operands[1];

  popValue(&current_frame->operand_stack, current_frame->local_variables + wide_index);
  current_frame->local_pc += 4;
}

void wide_ret(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  u2 wide_index = (operands[0] << 8) | operands[1];

  current_frame->local_pc = current_frame->local_variables[wide_index].return_address_value;
}

void wide_iinc(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);

  u2 wide_index = (operands[0] << 8) | operands[1];

  int16_t wide_const = (operands[2] << 8) | operands[3];

  current_frame->local_variables[wide_index].int_value += wide_const;
  current_frame->local_pc += 6;
}

// Implementation of multianewarray_aux
void multianewarray_aux(Array*    current_array,
                        JavaType* counts,
                        int       dimensions,
                        int       current_dimension) {
  current_array->length   = counts[current_dimension].int_value;
  current_array->elements = malloc(current_array->length * sizeof(JavaType));

  if(current_dimension == dimensions - 1) {
    return;
  }

  for(int i = 0; i < current_array->length; i++) {
    Array new_subarray;
    multianewarray_aux(&new_subarray, counts, dimensions, current_dimension + 1);

    JavaType new_subarray_ref = {.cat_tag = CAT1, .reference_value = &new_subarray};

    current_array->elements[i] = new_subarray_ref;
  }
}