#include "Cache.h"

void Cache::setup(Memory* m){
    memory = m;
    workType = None;
    state = false; // 0 = OFF 1 = ON
    storedMem = (unsigned char*) malloc(sizeof(unsigned char) * 8 );
    CLO = 0;
    previousWrite = (bool*) calloc(8, sizeof(bool));
    dataWriten = (bool*) calloc(8, sizeof(bool)); 
    validData = false;
    

}

void Cache::reset(){
    state = false;
    CLO = 0;
    validData = false;
}

void Cache::kill(){
    free(storedMem);
    free(dataWriten);
    free(previousWrite);
    storedMem = NULL;
    dataWriten = NULL;
    previousWrite = NULL;
}

void Cache::dump(){
    printf("CLO        : 0x%02X \n", CLO);
    printf("cache data : 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X \n", storedMem[0], storedMem[1], storedMem[2], storedMem[3], storedMem[4], storedMem[5], storedMem[6], storedMem[7]);
    printf("Flags      :   ");
    for(int i = 0; i < 8; i++){
        if(dataWriten[i] == 1){
            printf("W    ");
        }else if(previousWrite[i] == 1 && storedMem[i] == memory->instaReturn((CLO*8)+i)){
            printf("V    ");
        }else if(validData){
            printf("V    ");
        }else if(!validData){
            printf("I    ");
        }
    }
    printf("\n\n");

}

void Cache::on(){
    state = true;
}

void Cache::off(){
    state = false;
}



//************************************
// Tick Work
//************************************
//This should be simplifyed But im lazy (ONE FOR LOOP WITH IF STATEMENT DECLARING "ADDRESS" FOR INSTASTORE)
void Cache::flush(){
    
    if(cpudata != 0xFF){ //when just flushing this action is not needed
        //printf("getting here: %X \n", CLO);
        for(int i = 0; i < 8; i++){
            if(dataWriten[i] == true){
                //printf("Writen Data %X, addy %X \n", storedMem[i], CLO*8+i);
                memory->instaStore((CLO*8)+i, storedMem[i]);
                dataWriten[i] = false;
                previousWrite[i] = true;
            }else{
                previousWrite[i] = false;
            }
        }
        if(address == 0xFF){
            CLO = 0;
        }else{
            CLO = address / 8;
        }
        storedMem[address % 8] = cpudata;
    } else {
        //printf("getting here not FF\n");
        for(int i = 0; i < 8; i++){
            if(dataWriten[i] == true){
                memory->instaStore((CLO*8)+i, storedMem[i]); 
                dataWriten[i] = false;
                previousWrite[i] = true;
            }else{
                previousWrite[i] = false;
            }
        }
        
        validData = false;
    }

}

void Cache::write(char location, unsigned int value){
    storedMem[(unsigned int)location] = value;
    dataWriten[(unsigned int)location] = 1; //declare write 
}

unsigned char Cache::read(unsigned char location){
    return storedMem[location];
}

char Cache::load(){
    validData = true;
    CLO = address / 8;

    for(int i = 0; i < 8; i++){
        dataWriten[i] = 0;
        storedMem[i] = memory->instaReturn(CLO*8 + i);
    }
    return storedMem[address % 8];
    
}


void Cache::startTick(){

}

void Cache::doTick(){

}

bool Cache::isWritten(char location){
    return dataWriten[(unsigned int) location];
}

bool Cache::hasWritten(){
    for(int i = 0; i < 8; i++){
        if(dataWriten[i] == 1){
            return 1;
        }
    }
    return 0;
}

bool Cache::isMoreWorkNeeded(){

 return false;
}