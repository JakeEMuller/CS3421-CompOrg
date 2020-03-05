#include "clock.h"

//resets the clock to zero
void Clock::reset()
{
	currentTick = 0;
	//cout << "clock reset";
}
//resets the clock but set mem and cpu
void Clock::reset(Memory* mem, Cpu* cp, InstructMem* imem){
	currentTick = 0;
	memory = mem; //sets mem
	cpu = cp; //sets cpu
	imemory = imem;
}


void Clock::tick(unsigned int numberOfTicks)
{
	for(unsigned int i = 0; i < numberOfTicks; i++){
		startTick();
		bool workToDo = true;
		while(workToDo){
			
			cpu->doTick();
			imemory->doTick();
			memory->doTick();
			workToDo = isMoreCycleWorkNeeded();
			printf("work \n");
		}
		currentTick++;
		printf("clock cycle: %d \n", currentTick);
	}
}

void Clock::startTick(){
	memory->startTick();
	cpu->startTick();
	imemory->startTick();
}

bool Clock::isMoreCycleWorkNeeded(){
	return (memory->isMoreWorkNeeded() || cpu->isMoreWorkNeeded() || imemory->isMoreWorkNeeded());
}

void Clock::dump()
{
	printf("Clock: %hu \n\n", currentTick);
}
