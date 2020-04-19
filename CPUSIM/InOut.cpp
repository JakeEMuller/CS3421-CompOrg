 #include "InOut.h"
 
 void InOut::setup(Memory* m){
    memory = m;
    IOReg = 0;
    nextTick = -1;
    address = 0;
    temp = 0;
    waitTime = 0;
    IOExists = false;
    workingOnMem = false;
 }


 void InOut::Reset(){
     IOReg = 0;
 }

 void InOut::Load(char* file){
     IOExists = true;
     input = fopen(file, "r");
 }

 void InOut::Dump(){
     printf("IO Device: 0x%02X \n", IOReg);
 }
 
 void InOut::StartTick(){
    if(nextTick == -1 && IOExists == true){ //if -1 then get next IO instruction
        int junk = 0;    
        char tempS[6] = "";
        junk = fscanf(input, "%d %s %X", &nextTick, tempS, (unsigned int*) &address);
        if(junk == EOF){
            return;
        }
        if(!strcmp("write", tempS)){
            nextType = 1; //next IO instruction type
            junk = fscanf(input, "%X", &temp); //set write value
        }else{
            nextType = 0;
            temp = 0;
        }
        if(junk == EOF){
            printf("BIG OOPPPSSSS, INOUT EOF ERROR \n");
        }
        //printf("%d %s %02X %02X \n", nextTick, tempS, address, temp); //check parsing was handled correctly
    }
 }

 void InOut::DoTick(int tick){
     if(nextTick == tick){ //if its time to do next tick type
        //printf("next tick: %d \n", nextTick);
        if(memory->BeingUsed == true && workingOnMem == false){ //if memory is being used wait on it
            nextTick++;
        }else{
            workingOnMem = true;
            nextTick++;
            if(nextType == 0){ //if its a read 
                Read();
            }else{             //if its a write
                Write();
            }
            
        }
     }
 }

 void InOut::Read(){
     if(waitTime < memory->memSpeed-1){ //wait five ticks
        memory->BeingUsed = true;
        waitTime++;
     }else{
        IOReg = memory->instaReturn(address);         
        memory->BeingUsed = false;
        nextTick = -1;
        waitTime = 0;
        workingOnMem = false;
     }
 }

 void InOut::Write(){
     if(waitTime < memory->memSpeed-1){ //wait five ticks
        memory->BeingUsed = true;
        waitTime++;
     }else{
        memory->instaStore(address, temp); //store 
        memory->BeingUsed = false; 
        nextTick = -1;
        waitTime = 0;
        workingOnMem = false;
     }
 }