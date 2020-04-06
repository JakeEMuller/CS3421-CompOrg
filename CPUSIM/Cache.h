#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"

using namespace std;

class Cache {
public:
unsigned int cpudata;
unsigned char address;
bool state;
unsigned char CLO;
bool validData;
enum workType{None, Read, Write};
void setup(Memory* m);
void on();
void off();
void reset();
void kill();
void dump();
void startTick();
void doTick();
bool isMoreWorkNeeded(); //might not be needed 
void flush();
void write(char location, unsigned int value);
unsigned char read(unsigned char location);
char load();
bool hasWritten();
bool isWritten(char location);


private:
int workType;
Memory* memory;
unsigned char* storedMem;

bool* dataWriten; //0 = nothing 1 = written


//cpu values



};