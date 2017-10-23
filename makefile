all: hw4

hw4: main.o 
ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o -lgtest
else
	g++ -o hw4 main.o -lgtest -lpthread
endif
	
main.o: main.cpp utAtom.h utStruct.h utVariable.h utScanner.h utList.h
	g++ -std=gnu++0x -c main.cpp


clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw* utAtom.h utStruct.h utVariable.h utScanner.h utList.h
endif

stat:
	wc *.h *.cpp
