#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/comparison.h"

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

void fcmpl(){
    JavaType value1;
    JavaType value2;
    JavaType result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    //VERIFICAR SE NO POP JA CONSEGUE PEGAR O FLOAT VALUE OU PEGAR 
    // INT E FAZER CONVERSAO 

    if (value1.float_value > value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;
    } else if (value1.float_value == value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)0;
    } else if (value1.float_value < value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)-1;
    }

    pushValue(&current_frame -> operand_stack, result);
    current_frame -> local_pc ++;
}

void fcmpg(){
    JavaType value1;
    JavaType value2;
    JavaType result;
    Frame* current_frame = peekNode(frame_stack);
    popValue(&current_frame -> operand_stack, &value2);
    popValue(&current_frame -> operand_stack, &value1);

    //VERIFICAR SE NO POP JA CONSEGUE PEGAR O FLOAT VALUE OU PEGAR 
    // INT E FAZER CONVERSAO pra FLOAT

    if (value1.float_value > value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)1;
    } else if (value1.float_value == value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)0;
    } else if (value1.float_value < value2.float_value) {
        result.cat_tag = CAT1;
        result.int_value = (int32_t)-1;
    }

    pushValue(&current_frame -> operand_stack, result);
    current_frame -> local_pc ++;
}

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