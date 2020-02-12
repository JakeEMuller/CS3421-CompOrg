#include <iostream>

using namespace std;

class InstructMem{

    public:

    void create(unsigned int hexBytes);
    void reset();
    void dump(unsigned int hexAdr, unsigned int count);
    void set(unsigned int hexAdr, char* fileDir);


    private:

    unsigned int* instructionArray;
    unsigned int memorySize;

};