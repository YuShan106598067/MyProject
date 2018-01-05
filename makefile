all: hw8

hw8: utIterator
	
utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
ifeq (${OS}, Windows_NT)
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest 
else
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread
endif	
	
atom.o: atom.cpp atom.h variable.h
	g++ -std=c++11 -c atom.cpp

list.o: list.cpp list.h atom.h variable.h
	g++ -std=c++11 -c list.cpp	
	
struct.o:struct.cpp struct.h
		g++ -std=c++11 -c struct.cpp	

mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw* utAtom.h utStruct.h
endif

stat:
	wc *.h *.cpp
