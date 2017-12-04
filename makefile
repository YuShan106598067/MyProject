all: hw7

hw7: utIterator
	
utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread
	
atom.o: atom.cpp atom.h variable.h
	-std=gnu11 -c atom.cpp

list.o: list.cpp list.h atom.h variable.h
	-std=gnu11 -c list.cpp	
	
struct.o:struct.cpp struct.h
	-std=gnu11 -c struct.cpp	

mainIterator.o: mainIterator.cpp utIterator.h
	-std=gnu11 -c mainIterator.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw* utAtom.h utStruct.h
endif

stat:
	wc *.h *.cpp
