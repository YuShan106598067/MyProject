all:  utScanner


atom.o: atom.cpp atom.h variable.h
	g++ -std=c++11 -c atom.cpp

list.o:list.cpp list.h
		g++ -std=c++11 -c list.cpp

utScanner: mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h
	g++ -o utScanner mainScanner.o atom.o list.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h
		g++ -std=c++11 -c mainScanner.cpp

clean:
	rm -f *.o utScanner
stat:
	wc *.h *.cpp
