#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/comparison.h"

/*
 * Branch always
 *
 * opcode:	0xc8
 * format: 	[goto, branchbyte1, branchbyte2 ]
 * stack: 	(...) -> (...)
 * description:	takes pc value from current frame
 * and update using branch offset.
 */

void go_to(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;

    int8_t byte1 = bytecode[current_frame->local_pc + 1];
    int8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    current_frame->local_pc = current_frame->local_pc + branchOffset;
}

/*
 * Branch always (wide index)
 *
 * opcode:	0xc8
 * format: 	[goto, branchbyte1, branchbyte2, branchbyte3, branchbyte4 ]
 * stack: 	(...) -> (...)
 * description:	takes pc value from current frame
 * and update using branch offset.
 */

void goto_w(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    int8_t byte1 = bytecode[current_frame->local_pc + 1];
    int8_t byte2 = bytecode[current_frame->local_pc + 2];
    int8_t byte3 = bytecode[current_frame->local_pc + 3];
    int8_t byte4 = bytecode[current_frame->local_pc + 4];
    int16_t branchOffset = ((int16_t)byte1 << 24) | ((int16_t)byte2 << 16) | ((int16_t)byte3 << 8) | ((int16_t)byte4 << 0)   ;

    current_frame->local_pc = current_frame->local_pc + branchOffset;
}

/*
 * Jump subroutine
 *
 * opcode:	0xa8
 * format: 	[jsr, branchbyte1, branchbyte2]
 * stack: 	(...) -> (..., address)
 * description:	takes pc value from current frame
 * and pushes into the operand stack..
 */
void jsr(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;

    int8_t byte1 = bytecode[current_frame->local_pc + 1];
    int8_t byte2 = bytecode[current_frame->local_pc + 2];
    uint16_t branchOffset = ((int16_t)byte1 << 8) | byte2;
    JavaType return_address;

    return_address.return_address_value = current_frame->local_pc + 3;
    pushValue(&current_frame -> operand_stack, return_address);
    current_frame->local_pc = current_frame->local_pc + branchOffset;
}

/*
 * Return from subroutine
 *
 * opcode:	0xa9
 * format: 	[ret, index]
 * stack: 	(...) -> (...)
 * description:	takes pc value from current frame
 * and pushes into the operand stack..
 */
void ret(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    int8_t index = bytecode[current_frame->local_pc + 1];

    JavaType value ;
    value = current_frame->local_variables[index];
    current_frame->local_pc = current_frame->local_pc + value.return_address_value;
}


/*
 * Return void from method
 *
 * opcode:	0xb1
 * format: 	[return]
 * stack: 	(...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack..
 */
void ireturn(){
	JavaType value;
	Frame* current_frame = peekNode(frame_stack);
	popValue(&current_frame -> operand_stack, &value);
	value.cat_tag = CAT1;

	popNode(&frame_stack);
	Frame* previous_frame = peekNode(frame_stack);
	pushValue(&previous_frame -> operand_stack, value);
}

/*
 * Return void from method
 *
 * opcode:	0xb1
 * format: 	[return]
 * stack: 	(...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack..
 */
void lreturn(){
	JavaType value;	
	Frame* current_frame = peekNode(frame_stack);
	popValue(&current_frame -> operand_stack, &value);
	value.cat_tag = CAT2;

	popNode(&frame_stack);
	Frame* previous_frame = peekNode(frame_stack);
	pushValue(&previous_frame -> operand_stack, value);
}

/*
 * Return void from method
 *
 * opcode:	0xb1
 * format: 	[return]
 * stack: 	(...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack..
 */
void freturn(){
	JavaType value;	
	Frame* current_frame = peekNode(frame_stack);
	popValue(&current_frame -> operand_stack, &value);
	value.cat_tag = CAT1;
	
	popNode(&frame_stack);
	Frame* previous_frame = peekNode(frame_stack);
	pushValue(&previous_frame -> operand_stack, value);
}

/*
 * Return void from method
 *
 * opcode:	0xb1
 * format: 	[return]
 * stack: 	(...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack..
 */
void dreturn(){
	JavaType value;	
	Frame* current_frame = peekNode(frame_stack);
	popValue(&current_frame -> operand_stack, &value);
	value.cat_tag = CAT2;
	
	popNode(&frame_stack);
	Frame* previous_frame = peekNode(frame_stack);
	pushValue(&previous_frame -> operand_stack, value);
}

/*
 * Return void from method
 *
 * opcode:	0xb1
 * format: 	[return]
 * stack: 	(...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack..
 */
void areturn(){
	JavaType value;	
	Frame* current_frame = peekNode(frame_stack);
	popValue(&current_frame -> operand_stack, &value);
	value.cat_tag = CAT1;
	
	popNode(&frame_stack);
	Frame* previous_frame = peekNode(frame_stack);
	pushValue(&previous_frame -> operand_stack, value);
}

/*
 * Return void from method
 *
 * opcode:	0xb1
 * format: 	[return]
 * stack: 	(...) -> (empty)
 * description:	takes previous frame from frame stack
 * and pushes into the operand stack..
 */
void return_op(){
  Frame* old_frame = popNode(&frame_stack);
  free(old_frame);
}

/*
 * Access jump table by key match and jump
 *
 * opcode:	0xab
 * format: 	[lookupswitch, bytepad, defaultbyte1, defaultbyte2,
			defaultbyte3, defaultbyte4, npairs1, npairs2, npairs3, npairs4,
			match-offset pairs]
 * stack: 	(..., key) -> (...)
 * description:	takes pc value from current frame
 * and update using default or offset value..
 */

void lookupswitch(){
    JavaType key;	
	Frame* current_frame = peekNode(frame_stack);
	popValue(&current_frame -> operand_stack, &key);
	uint32_t address = current_frame->local_pc;

	current_frame->local_pc++;
	while((current_frame->local_pc)% 4 != 0){
		current_frame->local_pc++;	
	}

	uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;

    int8_t byte1 = bytecode[current_frame->local_pc++];
    int8_t byte2 = bytecode[current_frame->local_pc++];
    int8_t byte3 = bytecode[current_frame->local_pc++];
    int8_t byte4 = bytecode[current_frame->local_pc++];
    int16_t default_value = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    int8_t byte5 = bytecode[current_frame->local_pc++];
    int8_t byte6 = bytecode[current_frame->local_pc++];
    int8_t byte7 = bytecode[current_frame->local_pc++];
    int8_t byte8 = bytecode[current_frame->local_pc++];    
    int16_t pairs = (byte5 << 24) | (byte6 << 16) | (byte7 << 8) | byte8;

    for(int i = 0; i < pairs; i++){
		int8_t match_byte1 = bytecode[current_frame->local_pc++];
		int8_t match_byte2 = bytecode[current_frame->local_pc++];
		int8_t match_byte3 = bytecode[current_frame->local_pc++];
		int8_t match_byte4 = bytecode[current_frame->local_pc++]; 
        int32_t match = (match_byte1 << 24) | (match_byte2 << 16) |(match_byte3 << 8) | match_byte4;

		int8_t offset_byte1 = bytecode[current_frame->local_pc++];
		int8_t offset_byte2 = bytecode[current_frame->local_pc++];
		int8_t offset_byte3 = bytecode[current_frame->local_pc++];
		int8_t offset_byte4 = bytecode[current_frame->local_pc++]; 
        int32_t offset = (offset_byte1 << 24) | (offset_byte2 << 16) | (offset_byte3 << 8) | offset_byte4;

        if ((int32_t)key.int_value == match)
			current_frame->local_pc = address + offset;
    }
	current_frame->local_pc = address + default_value;
}

/*
 * Access jump table by index and jump
 *
 * opcode:	0xaa
 * format: 	[tableswitch, bytepad, defaultbyte1, defaultbyte2,
			defaultbyte3, defaultbyte4, lowbyte1, lowbyte2, lowbyte3,
			lowbyte4, highbyte1, highbyte2, highbyte3, highbyte4, jump offsets]
 * stack: 	(..., index) -> (...)
 * description:	takes pc value from current frame
 * and update using default or offset value..
 */ 

void tableswitch(){
    JavaType key;	
	Frame* current_frame = peekNode(frame_stack);
	popValue(&current_frame -> operand_stack, &key);
	uint32_t address = current_frame->local_pc;

	current_frame->local_pc++;
	while((current_frame->local_pc)% 4 != 0){
		current_frame->local_pc++;	
	}

	uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;

    int8_t byte1 = bytecode[current_frame->local_pc++];
    int8_t byte2 = bytecode[current_frame->local_pc++];
    int8_t byte3 = bytecode[current_frame->local_pc++];
    int8_t byte4 = bytecode[current_frame->local_pc++];
    int16_t default_value = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    int8_t low_byte1 = bytecode[current_frame->local_pc++];
    int8_t low_byte2 = bytecode[current_frame->local_pc++];
    int8_t low_byte3 = bytecode[current_frame->local_pc++];
    int8_t low_byte4 = bytecode[current_frame->local_pc++];    
    int16_t low_bytes = (low_byte1 << 24) | (low_byte2 << 16) | (low_byte3 << 8) | low_byte4;

	int8_t high_bytes1 = bytecode[current_frame->local_pc++];
	int8_t high_bytes2 = bytecode[current_frame->local_pc++];
	int8_t high_bytes3 = bytecode[current_frame->local_pc++];
	int8_t high_bytes4 = bytecode[current_frame->local_pc++]; 
	int32_t high_bytes = (high_bytes1 << 24) | (high_bytes2 << 16) |(high_bytes3 << 8) | high_bytes4;

	for(int match = low_bytes; match <= high_bytes; match++){
		int8_t offset_byte1 = bytecode[current_frame->local_pc++];
		int8_t offset_byte2 = bytecode[current_frame->local_pc++];
		int8_t offset_byte3 = bytecode[current_frame->local_pc++];
		int8_t offset_byte4 = bytecode[current_frame->local_pc++]; 
        int32_t offset = (offset_byte1 << 24) | (offset_byte2 << 16) | (offset_byte3 << 8) | offset_byte4;

        if ((int32_t)key.int_value == match)
			current_frame->local_pc = address + offset;
    }
	current_frame->local_pc = address + default_value;
}