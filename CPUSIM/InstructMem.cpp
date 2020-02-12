#include "InstructMem.h"

void InstrucMem::create(unsigned int hexBytes){
    memorySize = hexBytes;
    instructionArray = (unsigned int*) malloc(hexBytes * sizeof(unsigned int));
}

void InstrucMem::reset(){
    free(instructionArray);
    instructionArray = (unsigned int*) calloc(memorySize, sizeof(unsigned int));
}

void InstrucMem::dump(unsigned int hexAdr, unsigned int count){
    printf("Addr      0     1     2     3     4     5     6");
    int label = 0;
    for(unsigned int i = 0; i < count + hexAdr && i < memorySize; i++){
        //print the label 
        if((i % 7) == 0){
            printf(" \n0x%x ", label);
            label = label + 0x8;
        }
        if(i < hexAdr){ //untill the hexAddres wanted is found print spaces
            printf("      ");
        }else{
            printf("%05X ", instructionArray[i]);
        }
    }
    printf("\n\n");
}

void InstrucMem::set(unsigned int hexAdr, char* fileDir){

}