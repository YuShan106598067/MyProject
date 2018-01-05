all:  hw8

hw8:mainScanner.o atom.o list.o struct.o scanner.h  parser.h exception.h
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainScanner.o atom.o list.o struct.o -lgtest
else
	g++ -o hw8 mainScanner.o atom.o list.o struct.o -lgtest -lpthread
endif


atom.o: atom.cpp atom.h variable.h
	g++ --std=gnu++0x -c atom.cpp

list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp

mainScanner.o: mainScanner.cpp  scanner.h  atom.h struct.h variable.h parser.h   exception.h  
		g++ -std=gnu++0x -c mainScanner.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o madRace utAtom utVariable utScanner hw8
endif

stat:
	wc *.h *.cpp
