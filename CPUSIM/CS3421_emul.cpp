#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cpu.h"
#include "Memory.h"
#include "clock.h"
using namespace std;



int main(int argc, char** argv) {

	if(argc <= 1){
		return 0;
	}

	//get the name of the file from the command line
	char* fileName = argv[1];

	//create the three devices
	//memory
	Memory memory; //memory should be initalized on memory create command
	
	//cpu
	Cpu cpu;
	cpu.reset(&memory);
	
	//clock
	Clock clock;
	clock.reset(&memory, &cpu);
	


	FILE* inputFile = fopen(fileName, "r");
	int junk = 0; //because input files should always be perfect fscanf feedback can be ignored
	char command[30]; //thirty characters should be enought for the numbers
	char secondCommand[30];
	unsigned int hexValue = 0x00;
	unsigned char cpuReg = 'X';
	while ( fscanf( inputFile, "%s %s" , command, secondCommand ) != EOF ) {
		strcat(command, " "); // parse the two words
		strcat(command, secondCommand); 
		//printf("%s: \n", command);
		
		//check clock functions
		if (!strcmp("clock reset", command)) {
			clock.reset();
			//printf("clock reset \n");
		}
		else if (!strcmp("clock tick", command)) {
			int ticks = 0;
			junk = fscanf(inputFile, "%d", &ticks);
			clock.tick(ticks);
			//printf("clock tick \n");
		}
		else if (!strcmp("clock dump", command)) {
			clock.dump();
			//printf("clock dump \n");
		}
		else
		//check memory functions
		if (!strcmp("memory create", command)) {
			junk = fscanf(inputFile, "%x", &hexValue); 
			memory.create(hexValue);
			//printf("memory create \n");
		}
		else if (!strcmp("memory reset", command)) {
			memory.reset();
			//printf("memory reset \n");
		}
		else if (!strcmp("memory dump", command)) {
			unsigned int count = 0x00;
			junk = fscanf(inputFile ,"%x", &hexValue);
			junk = fscanf(inputFile, "%x", &count);
			memory.dump(hexValue, count);
			//printf("memory dump \n");
		}
		else if (!strcmp("memory set", command)) {
			junk = fscanf(inputFile, "%x", &hexValue);
			unsigned int count = 0x00;
			junk = fscanf(inputFile, "%x", &count);
			unsigned char* byteArray = (unsigned char*) malloc(count * sizeof(unsigned char));
			unsigned int temp;
			for(unsigned int i = 0; i < count; i++){
				junk = fscanf(inputFile, "%x", &temp);
				byteArray[i] = (unsigned char)temp;
				//printf( "%x ", byteArray[i]);
			}
			memory.set(hexValue, count, byteArray);
			//printf("memory set \n");
		}
		else
		//check cpu functions
		if (!strcmp("cpu reset", command)) {
			cpu.reset();
			//printf("cpu reset \n");
		}
		else if (!strcmp("cpu set", command)) {
			junk = fscanf(inputFile, "%s ", command);
			junk = fscanf(inputFile, "%c", &cpuReg);
			//special condition for PC 
			if (cpuReg == 'P') {
				junk = fscanf(inputFile, "%c", &cpuReg);
				junk = fscanf(inputFile, "%x", &hexValue);
				cpu.setReg('P', hexValue);
			}
			else {
				junk = fscanf(inputFile, "%c", &cpuReg);
				junk = fscanf(inputFile, "%x", &hexValue);
				cpu.setReg(cpuReg, hexValue);
			}
			//printf("cpu set \n");
			
		}
		else if (!strcmp("cpu dump", command)) {
			cpu.dump();
			//printf("Cpu dump \n");
		}
	}

	if(junk == EOF){
		exit(1);
	}
	memory.kill(); //frees any allocated memory
}