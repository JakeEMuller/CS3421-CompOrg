#pragma once
#include <iostream>
#include "Cpu.h"
#include "Memory.h"
using namespace std;

class Clock {
public:

	void reset();
	void reset(Memory* mem, Cpu* cp);
	void tick(unsigned int numberOfTicks);
	void startTick();
	void doCycleWork();
	bool isMoreCycleWorkNeeded();
	void dump();

private:
	unsigned short currentTick = 0;
	Memory* memory;
	Cpu* cpu;

};