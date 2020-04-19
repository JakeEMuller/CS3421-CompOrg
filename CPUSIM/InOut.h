#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Memory.h"

using namespace std;

class InOut {
    public:
    bool IOExists;
    void setup(Memory* m);
    void Reset();
    void Load(char* file);
    void Dump();
    void DoTick(int tick);
    void StartTick();
    void Read();
    void Write();

    private:
    Memory* memory;
    bool workingOnMem;
    unsigned char IOReg; //
    FILE* input;
    int nextTick;
    bool nextType; // 0 == read 1 == write
    unsigned char address;
    unsigned int temp;
    unsigned char waitTime;


};