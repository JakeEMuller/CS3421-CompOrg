#pragma once
#include <iostream>
using namespace std;

class Clock {
public:

	void reset();
	void tick(int numberOfTicks);
	void dump();

private:
	unsigned short currentTick = 0;

};