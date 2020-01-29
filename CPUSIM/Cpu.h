#pragma once
#include <iostream>
#include "Memory.h"
using namespace std;

class Cpu {
public:
	enum workType {None, fetchMem, cycleReg};
	//start new tick
	void startTick();
	//do tick work
	void doTick();
	//is more work needed
	bool isMoreWorkNeeded();
	//cycle registers
	void cycleResisters();
	//resets all registers to 0x00
	void reset();
	//reset but sets memory
	void reset(Memory* m);
	//set a register with a hex byte
    void setReg(char secondRegisterLetter , unsigned char hexByte);
	//dumps all values of registers too the console
	void dump();


	

private:
	//Declare Registers
	Memory* memory;
	int workType;
	bool waitingOnMem;
	unsigned char receivedByte; //byte to receive from memory
	unsigned char PC, RA, RB, RC, RD, RE, RF, RG, RH;

};