#include "Memory.h"
void Memory::startTick(){
    //workType for memory will be none at the begining 
    workType = None;
}

void Memory::doTick(){
    if(workType == MemFetch){
        completeMemFetch();
    }else{
        workType = None;
    }
    
}

//is more work needed
bool Memory::isMoreWorkNeeded(){
    if(workType == None){
		return false; 
	}else{
		return true;
	}
}
//start memfetch cycle
void Memory::startMemFetch(unsigned int address, unsigned char* cpuByte, bool* cpuWaiting){
    workType = MemFetch;
    cpuPCvalue = address; //save PC value
    cpuByteReturn = cpuByte; //save location where byte will be stored
    cpuWait = cpuWaiting;
    *cpuWaiting = true; //make the cpu wait

}
//do Memory Fetch
void Memory::completeMemFetch(){
    *cpuByteReturn = memoryStored[cpuPCvalue]; //put value into cpu byte return
    *cpuWait = false;
    workType = None;
}
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
            printf("%02x ", memoryStored[i]);
        }
    }
    printf("\n");
}
//starting from given hex address set values to given values
void Memory::set(unsigned int hexAddress, unsigned int hexCount, unsigned char* hexBytes)
{
    for(unsigned int i = 0; i < hexCount; i++ ){
        memoryStored[hexAddress + i] = hexBytes[i];
    }
}
