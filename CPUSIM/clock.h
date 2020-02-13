#pragma once
#include <iostream>
#include "Cpu.h"
#include "Memory.h"
#include "InstructMem.h"
using namespace std;

class Clock {
public:

	void reset();
	void reset(Memory* mem, Cpu* cp, InstructMem* imem);
	void tick(unsigned int numberOfTicks);
	void startTick();
	bool isMoreCycleWorkNeeded();
	void dump();

private:
	unsigned short currentTick = 0;
	InstructMem* imemory;
	Memory* memory;
	Cpu* cpu;

};