#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Cpu.h"
#include "Memory.h"
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
	unsigned short currentTick;
	InstructMem* imemory;
	Memory* memory;
	Cpu* cpu;

};