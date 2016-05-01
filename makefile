
p2 : fileaccess.o scanner.o parserrpal.o rdp.o stack.o token.o node.o cse.o stdast.o
	g++ -o p2 fileaccess.o scanner.o parserrpal.o rdp.o stack.o token.o node.o cse.o stdast.o
cse.o: cse.cpp cse.h token.h node.h
	g++ -c cse.cpp
stdast.o: stdast.cpp stdast.h node.h
	g++ -c stdast.cpp
fileaccess.o : fileaccess.cpp fileaccess.h
	 g++  -c fileaccess.cpp
scanner.o : scanner.cpp scanner.h token.h
	g++  -c scanner.cpp
parserrpal.o : parserrpal.cpp fileaccess.h scanner.h rdp.h cse.h stdast.h
	g++ -c parserrpal.cpp

rdp.o : rdp.cpp rdp.h token.h
	g++ -c rdp.cpp

stack.o : stack.cpp stack.h
	g++ -c stack.cpp

token.o : token.cpp token.h
	g++ -c token.cpp

node.o : node.cpp node.h
	g++ -c node.cpp

run :
	./p2

test :
	perl testDir/difftest.pl -1 "testDir/rpal -ast -noout FILE" -2 "./p1 -ast -noout FILE" -t testDir/tests/

cl :
	rm *.o p2
