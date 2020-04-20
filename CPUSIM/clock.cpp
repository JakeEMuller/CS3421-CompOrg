#include "clock.h"

//resets the clock to zero
void Clock::reset()
{
	currentTick = 0;
	//cout << "clock reset";
}
//resets the clock but set mem and cpu
void Clock::reset(Memory* mem, Cpu* cp, InstructMem* imem, InOut* I){
	currentTick = 0;
	memory = mem; //sets mem
	IO = I;
	cpu = cp; //sets cpu
	imemory = imem;
}


void Clock::tick(unsigned int numberOfTicks)
{
	for(unsigned int i = 0; i < numberOfTicks; i++){
		currentTick++;
		cpu->inTicks();
		startTick();
		bool workToDo = true;
		while(workToDo){
			IO->DoTick(currentTick);
			cpu->doTick();
			imemory->doTick();
			memory->doTick();
			workToDo = isMoreCycleWorkNeeded();
		}
		
		//printf("clock cycle: %d \n", currentTick);
	}
}

void Clock::startTick(){
	IO->StartTick();
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
