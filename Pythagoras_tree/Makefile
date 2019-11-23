flags = -std=c++11 -Wall -lsfml-graphics -lsfml-window -lsfml-system

all: main.o PTree.o
	g++ -o main main.o PTree.o $(flags)

main.o: main.cpp
	g++ -c main.cpp $(flags)

PTree.o: PTree.cpp PTree.hpp
	g++ -c PTree.cpp $(flags)

clean:
	rm -rf *.o
	rm -rf main
