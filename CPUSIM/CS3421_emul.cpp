#include <iostream>
#include "Cpu.h"
#include "Memory.h"
#include "clock.h"
using namespace std;

int main(int argc, char** argv) {

	//get the name of the file from the command line
	char* fileName = argv[1];

	//create the three devices
	//clock
	Clock clock;
	clock.reset();
	//cpu
	Cpu cpu;
	cpu.reset();
	//memory
	Memory memory;
	//TODO: Assign memory of zero bytes to avoid issues


	FILE* inputFile = fopen(fileName, "r");
	char* command = NULL;
	int hexValue = NULL;
	char cpuReg = NULL;
	while ( fscanf( inputFile, "%s %s" , command) != EOF ) {
		
		//check clock functions
		if (!strcmp("clock reset", command)) {
			clock.reset();
		}
		else if (!strcmp("clock tick", command)) {
			fscanf(inputFile, "%x", hexValue);
			clock.tick(hexValue);
		}
		else if (!strcmp("clock dump", command)) {
			clock.dump();
		}
		else
		//check memory functions
		if (!strcmp("memory create", command)) {
			fscanf(inputFile, "%x", hexValue);
			memory.create(hexValue);
		}
		else if (!strcmp("memory reset", command)) {
			memory.reset();
		}
		else if (!strcmp("memory dump", command)) {
			int count = NULL;
			fscanf(inputFile ,"%x", hexValue);
			fscanf(inputFile, "%x", count);
			memory.dump(hexValue, count);
		}
		else if (!strcmp("memory set", command)) {
			fscanf(inputFile, "%x", hexValue);
			//TODO: parse hex values that will need to be changed 

		}
		else
		//check cpu functions
		if (!strcmp("cpu reset", command)) {
			cpu.reset();
		}
		else if (!strcmp("cpu set", command)) {
			fscanf(inputFile, "%s", command);
			fscanf(inputFile, "%c", cpuReg);
			//special condition for PC 
			if (cpuReg == 'P') {
				fscanf(inputFile, "%c", cpuReg);
				fscanf(inputFile, "%x", hexValue);
				cpu.setReg('P', hexValue);
			}
			else {
				fscanf(inputFile, "%c", cpuReg);
				fscanf(inputFile, "%x", hexValue);
				cpu.setReg(cpuReg, hexValue);
			}
			
		}
		else if (!strcmp("cpu dump", command)) {
			cpu.dump();
		}
	}


}