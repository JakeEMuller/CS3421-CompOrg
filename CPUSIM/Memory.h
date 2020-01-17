#pragma once
#include <iostream>
using namespace std;

class Memory {
public:
	//create a number of memory addresses starting at 0x00
	void create(int hexSize);
	//sets all memory to 0x00
	void reset();
	//dump values staring at memory address given 
	void dump(int hexAddress, int hexCount);
	//starting from given hex address set values to given values
	void set(int hexAddress, int hexCount, int hexBytes[] ); 
private:
	int* memoryHead;
	int memorySize; // in hex
};