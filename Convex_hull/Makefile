flags = -std=c++11 -Wall
libs = -lsfml-system -lsfml-window -lsfml-graphics

convexhull: main.o interface.o convexhull.o poisson.o
	g++ -o convexhull main.o interface.o convexhull.o poisson.o $(flags) $(libs)

main.o: main.cpp
	g++ -c main.cpp $(flags)

interface.o: interface.cpp interface.hpp
	g++ -c interface.cpp $(flags)

convexhull.o: convexhull.cpp convexhull.hpp
	g++ -c convexhull.cpp $(flags)

poisson.o: poisson.cpp poisson.hpp
	g++ -c poisson.cpp $(flags)

clean:
	rm -rf convexhull
	rm -rf *.o
