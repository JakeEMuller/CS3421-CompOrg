CC = g++
CFLAGS = -pedantic -Wall -Wextra -O1
LDFLAGS = -lm 

# standard "make" 
default: clean Cpu.o Clock.o Memory.o Parser
# makes Cpu
Cpu.o: Cpu.cpp Cpu.h
	g++ -pedantic -Wall -Wextra -O1 -c Cpu.cpp -o Cpu ${LDFLAGS}
# makes Clock
Clock.o: clock.cpp clock.h
	g++ -pedantic -Wall -Wextra -O1 -c clock.cpp -o Clock ${LDFLAGS}
# makes memory
Memory.o: Memory.cpp Memory.h
	g++ -pedantic -Wall -Wextra -O1 -c Memory.cpp -o Memory ${LDFLAGS}
# makes the full
Parser: CS3421_emul.cpp clock.h Memory.h Cpu.h
	g++ -Wunused-result -pedantic -Wall -Wextra -O1 CS3421_emul.cpp Cpu Clock Memory -o CS3421_emul ${LDFLAGS}
# clean 
clean: 
	rm -f Cpu Clock Memory CS3421_emul
