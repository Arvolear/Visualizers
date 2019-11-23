flags = -std=c++11 -Wall
libs = -lsfml-system -lsfml-window -lsfml-graphics

poissondisk: main.o interface.o poisson.o
	g++ -o poissondisk main.o interface.o poisson.o $(flags) $(libs)

main.o: main.cpp
	g++ -c main.cpp $(flags)

interface.o: interface.cpp interface.hpp
	g++ -c interface.cpp $(flags)

poisson.o: poisson.cpp poisson.hpp
	g++ -c poisson.cpp $(flags)

clean:
	rm -rf poissondisk
	rm -rf *.o
