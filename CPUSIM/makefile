CC = g++
CFLAGS = -pedantic -Wall -Wextra -O1
LDFLAGS = -lm 

# standard "make" 
default: clean Memory.o InstructMem.o Cpu.o Clock.o Parser
# makes Cpu
Cpu.o: Cpu.cpp Cpu.h
	g++ -pedantic -Wall -Wextra -O1 -c Cpu.cpp -o Cpu ${LDFLAGS}
# makes Clock
Clock.o: clock.cpp clock.h
	g++ -pedantic -Wall -Wextra -O1 -c clock.cpp -o Clock ${LDFLAGS}
# make imemory
InstructMem.o: InstructMem.cpp InstructMem.h
	g++ -pedantic -Wall -Wextra -O1 -c InstructMem.cpp -o InstructMem ${LDFLAGS}
# makes memory
Memory.o: Memory.cpp Memory.h
	g++ -pedantic -Wall -Wextra -O1 -c Memory.cpp -o Memory ${LDFLAGS}
# makes the full
Parser: CS3421_emul.cpp clock.h Memory.h Cpu.h
	g++ -Wunused-result -pedantic -Wall -Wextra -O1 CS3421_emul.cpp Cpu Clock InstructMem Memory -o CS3421_emul ${LDFLAGS}
# clean 
clean: 
	rm -f Cpu Clock Memory InstructMem CS3421_emul
