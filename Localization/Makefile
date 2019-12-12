flags = -std=c++11 -Wall
libs = -lsfml-window -lsfml-system -lsfml-graphics

localize: main.o interface.o localizer.o generator.o 
	g++ -o localize main.o interface.o localizer.o generator.o $(libs) $(flags)

main.o: main.cpp
	g++ -c main.cpp $(flags)

interface.o: interface.cpp interface.hpp
	g++ -c interface.cpp $(flags)

localizer.o: localizer.cpp localizer.hpp
	g++ -c localizer.cpp $(flags)

generator.o: generator.cpp generator.hpp
	g++ -c generator.cpp $(flags)

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o
	rm -rf localize
