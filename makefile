all: hw4

hw4: main.o atom.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o atom.o list.o -lgtest
else
	g++ -o hw4 main.o atom.o list.o -lgtest -lpthread
endif
	
main.o: main.cpp utAtom.h utStruct.h utList.h utScanner.h utVariable.h
	g++ -std=gnu++0x -c main.cpp
	
atom.o: atom.cpp atom.h variable.h
	g++ -std=c++11 -c atom.cpp

list.o: list.cpp list.h atom.h variable.h
	g++ -std=c++11 -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw* utAtom.h utStruct.h utVariable.h utScanner.h utList.h
endif

stat:
	wc *.h *.cpp
