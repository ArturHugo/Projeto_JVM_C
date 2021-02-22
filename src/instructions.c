#include <stdio.h>
#include <stdlib.h>

#include "instructions.h"
#include "attributes.h"

instruction* instructionsRead(u1* code){
    instruction instr;
    instr.bytecode = 10;
    instr.pc = 42;
    instr.size = 1;
}

void instructionsPrint(instruction* instructions){
    printf("teste");
}

//xRead ou readX
//