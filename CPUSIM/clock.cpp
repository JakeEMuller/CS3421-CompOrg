#include "clock.h"

//resets the clock to zero
void Clock::reset()
{
	currentTick = 0;
	//cout << "clock reset";
}
//resets the clock but set mem and cpu
void Clock::reset(Memory* mem, Cpu* cp){
	currentTick = 0;
	memory = mem; //sets mem
	cpu = cp; //sets cpu
}


void Clock::tick(unsigned int numberOfTicks)
{
	for(unsigned int i = 0; i < numberOfTicks; i++){
		startTick();
		bool workToDo = true;
		while(workToDo){
			memory->doTick();
			cpu->doTick();
			workToDo = isMoreCycleWorkNeeded();
		}
		currentTick++;
	}
}

void Clock::startTick(){
	memory->startTick();
	cpu->startTick();
}

void Clock::doCycleWork(){
	memory->doTick();
	cpu->doTick();
}

bool Clock::isMoreCycleWorkNeeded(){
	return (memory->isMoreWorkNeeded() || cpu->isMoreWorkNeeded());
}

void Clock::dump()
{
	printf("Clock: %hu \n", currentTick);
}
