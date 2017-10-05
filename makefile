all: hw2

hw2: mainTerm.o atom.o variable.o number.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o atom.o variable.o number.o -lgtest
else
	g++ -o hw2 mainTerm.o atom.o variable.o number.o -lgtest -lpthread
endif
	
mainTerm.o: mainTerm.cpp utTerm.h
	g++ -std=gnu++0x -c mainTerm.cpp


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
