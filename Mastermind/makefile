all:	main

main: main.o peg.o board.o display.o 
	g++ main.o peg.o board.o display.o -lSDL2 -lSDL2_image -o main

main.o:	main.cpp
	g++ -c main.cpp

peg.o:	peg.cpp
	g++ -c peg.cpp

board.o:	board.cpp
	g++ -c board.cpp

display.o:	display.cpp
	g++ -c display.cpp

clean:	
	rm -f *.o main

