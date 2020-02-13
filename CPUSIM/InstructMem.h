#include <iostream>

using namespace std;

class InstructMem{

    public:
    enum workType {None, returnInsturct};
    void create(unsigned int hexBytes);
    void setup();
    void reset();
    void dump(unsigned int hexAdr, unsigned int count);
    void set(unsigned int hexAdr, char* fileDir);
    void startTick();
    void doTick();
    bool isMoreWorkNeeded();

    // return Instruction methods
    void startInstructFetch(unsigned int address, unsigned int* cpuInstruct, bool* cpuWaiting);
    void completeInstructFetch();

    private:
    int workType;
    unsigned int* instructionArray;
    unsigned int memorySize;
    //cpu values
    bool* cpuWait;
	unsigned int* cpuByteReturn;
	unsigned int cpuPCvalue;

};