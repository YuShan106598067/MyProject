all: hw3

hw3: main.o atom.o variable.o number.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o atom.o variable.o number.o -lgtest
else
	g++ -o hw3 main.o atom.o variable.o number.o -lgtest -lpthread
endif
	
main.o: main.cpp utAtom.h utStruct.h utVariable.h
	g++ -std=gnu++0x -c mainTerm.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
