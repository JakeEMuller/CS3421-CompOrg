#include "Cpu.h"

//resets all registers to 0x00
void Cpu::reset()
{
	waitingOnMem = false;
	free(regs);
	regs = (unsigned char*) calloc(9, sizeof(unsigned char)); //set all registers to zero
	receivedByte = 0x00;
	workType = None;
	memory->setup(); //reset memory in case memory is doing somthing for cpu
}
void Cpu::reset(Memory* m, InstructMem* i){
	waitingOnMem = false;
	receivedByte = 0x00;
	regs = (unsigned char*) calloc(9, sizeof(unsigned char));
	memory = m;
	imemory = i;
	workType = None;

}

void Cpu::kill(){
	free(regs);
	regs = NULL;
}

//set a register with a hex byte
void Cpu::setReg(char secondRegisterLetter, unsigned char hexByte)
{
	//special condition for PC
	if (secondRegisterLetter == 'P') {
		regs[0] = hexByte; //TEST TO MAKE SURE EVERTHING WITH THIS WORKS
		workType = None;
		memory->setup(); //reset memory to cancel instruction
	}
	else if (secondRegisterLetter == 'A') {
		regs[1] = hexByte;
	}
	else if (secondRegisterLetter == 'B') {
		regs[2] = hexByte;
	}
	else if (secondRegisterLetter == 'C') {
		regs[3] = hexByte;
	}
	else if (secondRegisterLetter == 'D') {
		regs[4] = hexByte;
	}
	else if (secondRegisterLetter == 'E') {
		regs[5] = hexByte;
	}
	else if (secondRegisterLetter == 'F') {
		regs[6] = hexByte;
	}
	else if (secondRegisterLetter == 'G') {
		regs[7] = hexByte;
	}
	else if (secondRegisterLetter == 'H') {
		regs[8] = hexByte;
	}
}

//dumps all values of registers too the console
void Cpu::dump()
{
	printf("PC: 0x%02X \n", regs[0]);
	printf("RA: 0x%02X \n", regs[1]);
	printf("RB: 0x%02X \n", regs[2]);
	printf("RC: 0x%02X \n", regs[3]);
	printf("RD: 0x%02X \n", regs[4]);
	printf("RE: 0x%02X \n", regs[5]);
	printf("RF: 0x%02X \n", regs[6]);
	printf("RG: 0x%02X \n", regs[7]);
	printf("RH: 0x%02X \n\n", regs[8]);
}
//******************************************
//  Tick work
//******************************************
void Cpu::startTick(){
	//if cpu is not working look for new instruction
	if(workType == None){
		workType = findInstruct;
	}
}

// check if more work is needed
bool Cpu::isMoreWorkNeeded(){
	if(workType == None){
		return false; 
	}else if(waitingOnMem){ //if waiting on memory cpu cant do anything
		return false;
	} else {
		return true;
	}
}

//increment program counter
void Cpu::incPC(){
	//printf("mem size: %X", imemory->memorySize);
	if(regs[0] < imemory->memorySize -1){
		regs[0]++;
	}else {
		regs[0] = 0;
	}
	
}

void Cpu::doTick(){
	if(workType == findInstruct){ //start to find next instruciton
		imemory->startInstructFetch(regs[0], &instruction, &waitingOnMem);
		workType = doInstruct;
	} else if(workType == doInstruct && !waitingOnMem){ //read function
		doInstruction();
	} 
	//ticks for lw
	else if(workType == storeInReg && !waitingOnMem){
		unsigned int regNum = (instruction >> 14) & 0x7; //get address to store in
		regs[regNum + 1] = receivedByte;
		workType = None; 
		incPC();
	}
	//ticks for sw
	else if(workType == finMemSw && !waitingOnMem){
		workType = None; //finish instruction so new instruction is started yet  
		incPC();
	}
	//printf("Work done: %d \n", workType);
}


//******************************
// Read/Do instruction 
//******************************
void Cpu::doInstruction(){
	unsigned int type = instruction >> 17;
	//printf("type: %d \n", type);
	//set Worktype
	if(type == 5){ //load word
		unsigned int add = (instruction >> 8) & 0x7; //find memory address to get
		//printf("lw address: %d \n", add);
		memory->startMemFetch(regs[add+1], &receivedByte, &waitingOnMem);
		workType = storeInReg;

	}else if(type == 6){ //store word
		unsigned int add = (instruction >> 8) & 0x7; //find address to store in
		//printf("sw address: %d \n", add);
		unsigned int value = regs[((instruction >> 11) & 0x7) + 1];
		//printf("value: %X", value);
		memory->startMemStore(regs[add+1], value, &waitingOnMem);
		workType = finMemSw;
	} else {
		workType = None;
		printf("No work: %X \n", type);
	}
	
}

