all:	main

main:	main.o
	g++ main.o -o main

main.o:	main.cpp board.h peg.h
	g++ -c main.cpp

clean:	
	rm -f *.o main
