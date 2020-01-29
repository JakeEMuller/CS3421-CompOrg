#pragma once
#include <iostream>

using namespace std;

class Memory {
public:

	void doTick();
	//create a number of memory addresses starting at 0x00
	void create(unsigned int hexSize);
	//sets all memory to 0x00
	void reset();
	//kill memory at end of program
	void kill();
	//dump values staring at memory address given 
	void dump(unsigned int hexAddress, unsigned int hexCount);
	//starting from given hex address set values to given values
	void set( unsigned int hexAddress, unsigned int hexCount, unsigned char hexBytes[] ); 
private:
	unsigned char* memoryStored;
	unsigned int memorySize; // in hex
};