#pragma once
#include <iostream>
using namespace std;

class Cpu {
public:

	//resets all registers to 0x00
	void reset();
	//set a register with a hex byte
    void setReg(char secondRegisterLetter , unsigned int hexByte);
	//dumps all values of registers too the console
	void dump();


	

private:
	//Declare Registers
	char PC, RA, RB, RC, RD, RE, RF, RG, RH;

};