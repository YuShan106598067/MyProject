all: hw4 utAtom utVariable utNumber utStruct utList

hw4: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o -lgtest
else
	g++ -o hw4 main.o -lgtest -lpthread
endif
main.o: main.cpp utTerm.h utAtom.h utVariable.h utNumber.h utList.h
	g++ -std=gnu++0x -c  main.cpp



clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw* utAtom utNumber utVariable utStruct utList
endif

stat:
	wc *.h *.cp
