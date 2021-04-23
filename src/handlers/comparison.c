#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/comparison.h"

/*
 * Compare long
 *
 * opcode:  0x94
 * format:  [lcmp]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type long from operand stack
 * and pushes into the operand stack..
 */

void lcmp(){
    JavaType value1;
    JavaType value2;
    JavaType result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if (value1.long_value > value2.long_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;
    } else if (value1.long_value == value2.long_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)0;
    } else if (value1.long_value < value2.long_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)-1;
    }

    pushValue(&current_frame -> operand_stack, result);
    current_frame -> local_pc ++;
}

/*
 * Compare float
 *
 * opcode:  0x95
 * format:  [fcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type float from operand stack
 * and pushes into the operand stack..
 */
void fcmpl(){
    JavaType value1;
    JavaType value2;
    JavaType result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if (value1.float_value > value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;
    } else if (value1.float_value == value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)0;
    } else if (value1.float_value < value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)-1;
    } else {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;  
    }

    pushValue(&current_frame -> operand_stack, result);
    current_frame -> local_pc ++;
}

/*
 * Compare float
 *
 * opcode:  0x96
 * format:  [fcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type float from operand stack
 * and pushes into the operand stack..
 */
void fcmpg(){
    JavaType value1;
    JavaType value2;
    JavaType result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if (value1.float_value > value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;
    } else if (value1.float_value == value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)0;
    } else if (value1.float_value < value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)-1;
    } else {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;  
    }

    pushValue(&current_frame -> operand_stack, result);
    current_frame -> local_pc ++;
}

/*
 * Compare double
 *
 * opcode:  0x97
 * format:  [dcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type double from operand stack
 * and pushes into the operand stack..
 */
void dcmpl(){
    JavaType value1;
    JavaType value2;
    JavaType result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if (value1.double_value > value2.double_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;
    } else if (value1.double_value == value2.double_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)0;
    } else if (value1.double_value < value2.double_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)-1;
    }

    pushValue(&current_frame -> operand_stack, result);
    current_frame -> local_pc ++;
}

/*
 * Compare double
 *
 * opcode:  0x98
 * format:  [dcmp<op>]
 * stack:   (..., value1, value2) -> (..., result)
 * description: takes two values of type double from operand stack
 * and pushes into the operand stack..
 */
void dcmpg(){
    JavaType value1;
    JavaType value2;
    JavaType result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if (value1.double_value > value2.double_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;
    } else if (value1.double_value == value2.double_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)0;
    } else if (value1.double_value < value2.double_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)-1;
    }

    pushValue(&current_frame -> operand_stack, result);
    current_frame -> local_pc ++;
}

/*
 * Branch if int comparison with zero succeeds
 *
 * opcode:  0x99
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value..
 */
void ifeq(){
    Frame* current_frame = peekNode(frame_stack);
    JavaType value;
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    popValue(&current_frame -> operand_stack, &value);

    if ((int32_t)value.int_value == 0) {
            current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame-> local_pc = current_frame->local_pc + 2 + 1;
}

/*
 * Branch if int comparison with zero succeeds
 *
 * opcode:  0x9a
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value..
 */
void ifne(){
    Frame* current_frame = peekNode(frame_stack);
    JavaType value;
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    popValue(&current_frame -> operand_stack, &value);

    if ((int32_t)value.int_value != 0) {
            current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame-> local_pc = current_frame->local_pc + 2 + 1;
}

/*
 * Branch if int comparison with zero succeeds
 *
 * opcode:  0x9b
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value..
 */
void iflt(){
    Frame* current_frame = peekNode(frame_stack);
    JavaType value;
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    popValue(&current_frame -> operand_stack, &value);

    if ((int32_t)value.int_value < 0) {
            current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame-> local_pc = current_frame->local_pc + 2 + 1;
}

/*
 * Branch if int comparison with zero succeeds
 *
 * opcode:  0x9c
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value..
 */
void ifge(){
    Frame* current_frame = peekNode(frame_stack);
    JavaType value;
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint32_t baseAddress = current_frame->local_pc;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    popValue(&current_frame -> operand_stack, &value);

    if ((int32_t)value.int_value >= 0) {
            current_frame->local_pc = baseAddress + branchOffset;
    }
    current_frame-> local_pc = current_frame->local_pc + 2 + 1;
}

/*
 * Branch if int comparison with zero succeeds
 *
 * opcode:  0x9d
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value..
 */
void ifgt(){
    Frame* current_frame = peekNode(frame_stack);
    JavaType value;
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint32_t baseAddress = current_frame->local_pc;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    popValue(&current_frame -> operand_stack, &value);

    if ((int32_t)value.int_value > 0) {
            current_frame->local_pc = baseAddress + branchOffset;
    }
    current_frame-> local_pc = current_frame->local_pc + 2 + 1;
}
/*
 * Branch if int comparison with zero succeeds
 *
 * opcode:  0x9e
 * format:  [if<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value) -> (...)
 * description: takes values of type int from operand stack
 * and update pc value..
 */
void ifle(){
    Frame* current_frame = peekNode(frame_stack);
    JavaType value;
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint32_t baseAddress = current_frame->local_pc;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    popValue(&current_frame -> operand_stack, &value);

    if ((int32_t)value.int_value <= 0) {
            current_frame->local_pc = baseAddress + branchOffset;
    }
    current_frame-> local_pc = current_frame->local_pc + 2 + 1;
}

/*
 * Branch if int comparison succeeds
 *
 * opcode:  0x9f
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value..
 */
void if_icmpeq(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if ((int32_t)value1.int_value == (int32_t)value2.int_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;
}

/*
 * Branch if int comparison succeeds
 *
 * opcode:  0xa0
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value..
 */
void if_icmpne(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if ((int32_t)value1.int_value != (int32_t)value2.int_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;  
}

/*
 * Branch if int comparison succeeds
 *
 * opcode:  0xa1
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value..
 */
void if_icmplt(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if ((int32_t)value1.int_value < (int32_t)value2.int_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;  
}

/*
 * Branch if int comparison succeeds
 *
 * opcode:  0xa2
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value..
 */
void if_icmpge(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if ((int32_t)value1.int_value >= (int32_t)value2.int_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;   
}

/*
 * Branch if int comparison succeeds
 *
 * opcode:  0xa3
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value..
 */
void if_icmpgt(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if ((int32_t)value1.int_value > (int32_t)value2.int_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;   
}

/*
 * Branch if int comparison succeeds
 *
 * opcode:  0xa4
 * format:  [if_icmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type int from operand stack
 * and update pc value..
 */
void if_icmple(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if ((int32_t)value1.int_value <= (int32_t)value2.int_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;   
}

/*
 * Branch if reference comparison succeeds
 *
 * opcode:  0xa5
 * format:  [if_acmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type reference from operand stack
 * and update pc value..
 */
void if_acmpeq(){
    //testar
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if (value1.reference_value == value2.reference_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;
}

/*
 * Branch if reference comparison succeeds
 *
 * opcode:  0xa6
 * format:  [if_acmp<cond>, branchbyte1, branchbyte2]
 * stack:   (..., value1, value2) -> (...)
 * description: takes two values of type reference from operand stack
 * and update pc value..
 */
void if_acmpne(){
    Frame* current_frame = peekNode(frame_stack);  
    uint8_t* bytecode = current_frame->current_method->attributes->code_info.code;
    uint8_t byte1 = bytecode[current_frame->local_pc + 1];
    uint8_t byte2 = bytecode[current_frame->local_pc + 2];
    int16_t branchOffset = ((int16_t)byte1 << 8) | byte2;

    JavaType value1;
    JavaType value2;
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    if (value1.reference_value != value2.reference_value) {
        current_frame->local_pc = current_frame->local_pc + branchOffset;
    }
    current_frame->local_pc = current_frame->local_pc + 2 + 1;
}