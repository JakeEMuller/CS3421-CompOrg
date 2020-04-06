#include "Memory.h"

//create a number of memory addresses starting at 0x00
void Memory::create(unsigned int hexSize)
{
    memorySize = hexSize;
    //printf("Mem size is: %09d\n", memorySize);
    //printf("hexSize * sizeof(unsigned char) = %d\n", hexSize * sizeof(unsigned char));
    memoryStored = (unsigned char*) malloc(hexSize * sizeof(unsigned char)); 
}
//sets all memory to 0x00
void Memory::reset()
{
    free(memoryStored);
    memoryStored = (unsigned char*) calloc(memorySize, sizeof(unsigned char)); //use calloc to initalize memory to zero
}
//kill the memory stored before ending program
void Memory::kill(){
    //printf("kill\n");
    free(memoryStored);
    memoryStored = NULL;
    
}

//dump values staring at memory address given 
void Memory::dump(unsigned int hexAddress, unsigned int hexCount)
{
    //print table
    printf("Addr   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    int label = 0;
    for(unsigned int i = 0; i < hexCount + hexAddress && i < memorySize; i++){
        //print the label 
        if((i % 16) == 0){
            printf(" \n0x%d0   ", label);
            label++;
        }
        if(i < hexAddress){ //untill the hexAddres wanted is found print spaces
            printf("   ");
        }else{
            printf("%02X ", memoryStored[i]);
        }
    }
    printf("\n\n");
}
//starting from given hex address set values to given values
void Memory::set(unsigned int hexAddress, unsigned int hexCount, unsigned char* hexBytes)
{
    for(unsigned int i = 0; i < hexCount; i++ ){
        memoryStored[hexAddress + i] = hexBytes[i];
    }
}

void Memory::setup(){
    speedCount = 0;
    memSpeed = 5;
    workType = None;
}

void Memory::startTick(){
    
}

void Memory::doTick(){
    if(workType == MemFetch){
        completeMemFetch();
    }else if(workType == setMem){
        completeMemStore();
    }
}

//is more work needed
bool Memory::isMoreWorkNeeded(){
    return false;
}
//*******************************
// Load memory methods
//*******************************
void Memory::startMemFetch(unsigned int address, unsigned char* cpuByte, bool* cpuWaiting){
    workType = MemFetch;
    cpuPCvalue = address; //save PC value
    cpuByteReturn = cpuByte; //save location where byte will be stored
    cpuWait = cpuWaiting;
    *cpuWaiting = true; //make the cpu wait
    //printf("start mem, address: %4X \n", address);

}
//do Memory Fetch
void Memory::completeMemFetch(){
    if(speedCount < memSpeed - 1){ //make sure 
        speedCount++;
    } else {
        *cpuByteReturn = memoryStored[cpuPCvalue]; //put value into cpu byte return
        *cpuWait = false;
        workType = None;
        //printf("completeMemFetch, Byte Return: %X \n", *cpuByteReturn);
        speedCount = 0;
    }
    //printf("L memTime: %d \n", speedCount);
    
}

char Memory::instaReturn(unsigned int address){
    if(address >= memorySize){
        printf("InstaReturn error");
    }
    return memoryStored[address];
}

//**************************
// store memory methods
//**************************

void Memory::startMemStore(unsigned int address, unsigned char StoredByte, bool* cpuWaiting){
    
    workType = setMem;
    //printf("startMemStore, Address: %X, StoredByte: %X, cpuWaiting: %X  \n", address, StoredByte, cpuWaiting);
    cpuPCvalue = address; 
    cpuByteReturn = (unsigned char*) malloc(sizeof(char) * 1); //find spot to temp store value
    *cpuByteReturn = StoredByte; //reuse memory fetch varables 
    cpuWait = cpuWaiting;
    *cpuWaiting = true;
    
    //printf("start mem store, address: %4X, byte: %2X  \n", cpuPCvalue, *cpuByteReturn);
}

void Memory::completeMemStore(){
    if(speedCount < memSpeed - 1){ //make sure 
        speedCount++;
    } else {
        //printf("completeMemStore");
        memoryStored[cpuPCvalue] = *cpuByteReturn; 
        //printf("memory stored: %2X \n", *cpuByteReturn);
        free(cpuByteReturn); //free address to avoid mem leak
        *cpuWait = false;
        workType = None;
        speedCount = 0;
    }
    //printf("S memTime: %d \n", speedCount);
}


void Memory::instaStore(unsigned int address, unsigned char byte){
    if(address >= memorySize){
        printf("InstaStore Error");
    }
    memoryStored[address] = byte;
}