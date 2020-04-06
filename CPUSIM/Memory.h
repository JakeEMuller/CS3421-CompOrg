#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Memory {
public:
	unsigned int memSpeed;
	unsigned int memorySize; // in hex
	int workType;
	//basic setup
	void setup();
	//work types for Memory
	enum workType {None, MemFetch, setMem};
	//start tick operations
	void startTick();
	// do tick work
	void doTick();
	//is more work needed
	bool isMoreWorkNeeded();
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

	//load memory function
	void startMemFetch(unsigned int address, unsigned char* cpuByte, bool* cpuWaiting);
	void completeMemFetch();
	char instaReturn(unsigned int address);

	//store memory function
	void startMemStore(unsigned int address, unsigned char StoredByte, bool* cpuWaiting);
	void completeMemStore();
	void instaStore(unsigned int address, unsigned char byte);
	
private:
	
	unsigned int speedCount;
	bool* cpuWait;
	unsigned char* cpuByteReturn;
	unsigned int cpuPCvalue;
	unsigned char* memoryStored;
	unsigned char* inputValue;
	
};