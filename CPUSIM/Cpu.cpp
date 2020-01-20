#include "Cpu.h"

//resets all registers to 0x00
void Cpu::reset()
{
	PC = 0x00;
	RA = 0x00;
	RB = 0x00;
	RC = 0x00;
	RD = 0x00;
	RE = 0x00;
	RF = 0x00;
	RG = 0x00;
	RH = 0x00;
}
//set a register with a hex byte
void Cpu::setReg(char secondRegisterLetter, int hexByte)
{
	//special condition for PC
	if (secondRegisterLetter == 'P') {
		PC = hexByte;
	}
	else if (secondRegisterLetter == 'A') {
		RA = hexByte;
	}
	else if (secondRegisterLetter == 'B') {
		RB = hexByte;
	}
	else if (secondRegisterLetter == 'C') {
		RC = hexByte;
	}
	else if (secondRegisterLetter == 'D') {
		RD = hexByte;
	}
	else if (secondRegisterLetter == 'E') {
		RE = hexByte;
	}
	else if (secondRegisterLetter == 'F') {
		RF = hexByte;
	}
	else if (secondRegisterLetter == 'G') {
		RG = hexByte;
	}
	else if (secondRegisterLetter == 'H') {
		RH = hexByte;
	}
}

//dumps all values of registers too the console
void Cpu::dump()
{
	printf("PC: 0x%02x \n", PC);
	printf("RA: 0x%02x \n", RA);
	printf("RB: 0x%02x \n", RB);
	printf("RC: 0x%02x \n", RC);
	printf("RD: 0x%02x \n", RD);
	printf("RE: 0x%02x \n", RE);
	printf("RF: 0x%02x \n", RF);
	printf("RG: 0x%02x \n", RG);
	printf("RH: 0x%02x \n", RH);
}
