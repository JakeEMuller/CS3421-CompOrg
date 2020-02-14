#include "InstructMem.h"

void InstructMem::setup(){
    workType = None;
}

void InstructMem::create(unsigned int hexBytes){
    memorySize = hexBytes;
    instructionArray = (unsigned int*) malloc(hexBytes * sizeof(unsigned int));
}

void InstructMem::reset(){
    free(instructionArray);
    instructionArray = (unsigned int*) calloc(memorySize, sizeof(unsigned int));
}

void InstructMem::kill(){
    free(instructionArray);
}

void InstructMem::dump(unsigned int hexAdr, unsigned int count){
    printf("Addr     0     1     2     3     4     5     6");
    int label = 0;
    for(unsigned int i = 0; i < count + hexAdr && i < memorySize; i++){
        //print the label 
        if((i % 7) == 0){
            if(label < 0x10){
                printf(" \n0x0%x ", label);
            }else{
                printf(" \n0x%x ", label);
            }
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

void InstructMem::set(unsigned int hexAdr, char* fileDir){
    FILE* file = fopen(fileDir, "r");
    unsigned int temp = 0;
    unsigned int i = 0;
    while(fscanf(file, "%X", &temp) != EOF && (i + hexAdr) != memorySize){
        temp = 0xfffff & temp; //make into 20 bit for my sanity
        instructionArray[hexAdr + i] = temp;
        i++;
    }
}

//begin clock methods
void InstructMem::startTick(){
    
}

void InstructMem::doTick(){
    if(workType == returnInsturct){
        completeInstructFetch();
    }
}

bool InstructMem::isMoreWorkNeeded(){
    return false;
}


//******************************************
// return Insctrction methods
//******************************************

void InstructMem::startInstructFetch(unsigned int address, unsigned int* cpuInstruct, bool* cpuWaiting){
    workType = returnInsturct;
    cpuPCvalue = address;
    cpuByteReturn = cpuInstruct;
    cpuWait  = cpuWaiting;
    *cpuWaiting = true;
}

void InstructMem::completeInstructFetch(){
    *cpuByteReturn = instructionArray[cpuPCvalue];
    *cpuWait = false;
    workType = None;
}


