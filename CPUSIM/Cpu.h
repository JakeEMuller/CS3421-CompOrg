#pragma once
#include <iostream>
#include "Memory.h"
using namespace std;

class Cpu {
public:
	void doTick();
	//resets all registers to 0x00
	void reset();
	//set a register with a hex byte
    void setReg(char secondRegisterLetter , unsigned char hexByte);
	//dumps all values of registers too the console
	void dump();


	

private:
	//Declare Registers
	bool waitingOnMem;
	char receivedByte;
	unsigned char PC, RA, RB, RC, RD, RE, RF, RG, RH;

};