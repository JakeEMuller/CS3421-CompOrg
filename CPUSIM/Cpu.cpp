#include "Cpu.h"

//resets all registers to 0x00
void Cpu::reset()
{
	waitingOnMem = false;
	free(regs);
	regs = (unsigned char*) calloc(9, sizeof(unsigned char));
	receivedByte = 0x00;
}
void Cpu::reset(Memory* m, InstructMem* i){
	reset();
	regs = (unsigned char*) malloc(9);
	memory = m;
	imemory = i;
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
		regs[0] = hexByte;
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
	}else if(waitingOnMem){
		return false;
	} else {
		return true;
	}
}

void Cpu::doTick(){
	//************************
	// legacy features
	//************************
	if(workType == fetchMem){ //wants memory so it sends a signal to memory
		memory->startMemFetch(regs[0], &receivedByte, &waitingOnMem);
		workType = cycleReg;
	}else if(workType == cycleReg && !waitingOnMem) //only cycles if not waiting for mem
	{
		cycleResisters();
		workType = None;	

	
	}
	//***************************************
	//ticks for finding the instrcution
	//***************************************
	else if(workType = findInstruct){ //start to find next instruciton
		imemory->startInstructFetch(regs[0], &instruction, &waitingOnMem);
		workType = doInstruct;
	} else if(workType == doInstruct && !waitingOnMem){ //read function
		doInstruction();
	} 
	//ticks for lw
	else if(workType = storeInReg && !waitingOnMem){
		unsigned int regNum = (instruction >> 14) & 0x7; //get address to store in
		regs[regNum + 1] = receivedByte;
		workType = None; 
	}
}


//******************************
// Read/Do instruction 
//******************************
void Cpu::doInstruction(){
	unsigned int type = instruction >> 17;
	//set Worktype
	if(type == 0b101){ //load word
		unsigned int add = (instruction >> 8) & 0x7; //find memory address to get
		memory->startMemFetch(add, &receivedByte, &waitingOnMem);
		workType = storeInReg;

	}else if(type = 0b110){
		
	}
}


//******************************
//cycle regsiters *legacy*
//******************************
//void Cpu::cycleResisters(){
//	//cycle all registers down one
//	RH = RG;
//	RG = RF;
//	RF = RE;
//	RE = RD;
//	RD = RC;
//	RC = RB;
//	RB = RA;
//	//set new RA reg
//	RA = receivedByte;
//	if(PC >= memory->memorySize){
//		PC = 0;
//	}else {
//		PC++;
//	}
//	workType = None;
//}
