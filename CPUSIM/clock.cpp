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
	memory = *mem; //sets mem
	cpu = *cp; //sets cpu
}


void Clock::tick(int numberOfTicks)
{
	for(int i = 0; i < numberOfTicks; i++){
		startTick();
		doCycleWork();
		isMoreCycleWorkNeeded();
	}
}

void Clock::startTick(){

}

void Clock::doCycleWork(){

}

void Clock::isMoreCycleWorkNeeded(){
	
}

void Clock::dump()
{
	printf("Clock: %hu \n", currentTick);
}
