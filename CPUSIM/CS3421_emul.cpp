#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cpu.h"
#include "Memory.h"
#include "clock.h"
using namespace std;

int main(int argc, char** argv) {

	//get the name of the file from the command line
	char* fileName = argv[1];

	//create the three devices
	//cpu
	Cpu cpu;
	cpu.reset();
	//memory
	Memory memory;
	//TODO: Assign memory of zero bytes to avoid issues
	//clock
	Clock clock;
	clock.reset(&memory, &cpu);
	


	FILE* inputFile = fopen(fileName, "r");
	char command[20]; //twenty characters should be enought for the numbers
	char secondCommand[20];
	unsigned int hexValue = 0x00;
	char* cpuReg = " ";
	while ( fscanf( inputFile, "%s %s" , command, secondCommand ) != EOF ) {
		strcat(command, " "); // parse the two words
		strcat(command, secondCommand); 
		printf("%s: \n", command);
		
		//check clock functions
		if (!strcmp("clock reset", command)) {
			clock.reset();
			printf("clock reset \n");
		}
		else if (!strcmp("clock tick", command)) {
			fscanf(inputFile, "%x", &hexValue);
			clock.tick(hexValue);
			printf("clock tick \n");
		}
		else if (!strcmp("clock dump", command)) {
			clock.dump();
			printf("clock dump \n");
		}
		else
		//check memory functions
		if (!strcmp("memory create", command)) {
			fscanf(inputFile, "%x", &hexValue); 
			memory.create(hexValue);
			printf("memory create \n");
		}
		else if (!strcmp("memory reset", command)) {
			memory.reset();
			printf("memory reset \n");
		}
		else if (!strcmp("memory dump", command)) {
			unsigned int count = 0x00;
			fscanf(inputFile ,"%x", &hexValue);
			fscanf(inputFile, "%x", &count);
			memory.dump(hexValue, count);
			printf("memory dump \n");
		}
		else if (!strcmp("memory set", command)) {
			fscanf(inputFile, "%x", &hexValue);
			unsigned int count = 0x00;
			fscanf(inputFile, "%x", &count);
			unsigned char byteArray[count];
			unsigned int temp;
			for(unsigned int i = 0; i < count; i++){
				fscanf(inputFile, "%x", &temp);
				byteArray[i] = (unsigned char)temp;
				//printf( "%x ", byteArray[i]);
			}
			memory.set(hexValue, count, byteArray);
			printf("memory set \n");
		}
		else
		//check cpu functions
		if (!strcmp("cpu reset", command)) {
			cpu.reset();
			printf("cpu reset \n");
		}
		else if (!strcmp("cpu set", command)) {
			fscanf(inputFile, "%s", command);
			fscanf(inputFile, "%c", cpuReg);
			//special condition for PC 
			if (*cpuReg == 'P') {
				fscanf(inputFile, "%c", cpuReg);
				fscanf(inputFile, "%x", &hexValue);
				cpu.setReg('P', hexValue);
			}
			else {
				fscanf(inputFile, "%c", cpuReg);
				fscanf(inputFile, "%x", &hexValue);
				cpu.setReg(cpuReg[0], hexValue);
			}
			printf("cpu set \n");
			
		}
		else if (!strcmp("cpu dump", command)) {
			cpu.dump();
			printf("Cpu dump \n");
		}
	}
	memory.kill(); //frees any allocated memory
}