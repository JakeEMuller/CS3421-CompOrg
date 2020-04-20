#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"
#include "InstructMem.h"
#include "Cache.h"
using namespace std;

class Cpu {
public:
	int ticks;
	enum workType {None, findInstruct, readInstruct, doInstruct, storeInReg, finMemSw, WaitOnCPU, WaitOnflush, WaitOnLoad, HALT};
	//start new tick
	void startTick();
	//do tick work
	void doTick();
	//is more work needed
	bool isMoreWorkNeeded();
	//increment PC
	void incPC();
	//cycle registers
	void cycleResisters();
	//resets all registers to 0x00
	void reset();
	//reset but sets memory
	void reset(Memory* m, InstructMem* i, Cache* c);
	//kill register mem
	void kill();
	//set a register with a hex byte
    void setReg(char secondRegisterLetter , unsigned char hexByte);
	//dumps all values of registers too the console
	void dump();
	void inTicks();
	//do instruction 
	void doInstruction();


	

private:
	//Declare Registers
	Memory* memory;
	InstructMem* imemory;
	Cache* cache;
	int workType;
	//return varables
	bool waitingOnMem;
	unsigned int instruction;
	unsigned char receivedByte; //byte to receive from memory
	unsigned char* regs;
	unsigned int cyclesNeeded;
	//unsigned char PC, RA, RB, RC, RD, RE, RF, RG, RH;
	

};