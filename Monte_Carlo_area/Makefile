area: frontend.o backend.o main.o meter.o
	g++ -o area frontend.o meter.o backend.o main.o -lsfml-graphics -lsfml-window -lsfml-system -std=c++14

backend.o: backend.cpp
	g++ -c backend.cpp -std=c++14

meter.o: meter.cpp
	g++ -c meter.cpp -std=c++14

frontend.o: frontend.cpp
	g++ -c frontend.cpp -std=c++14

main.o: main.cpp
	g++ -c main.cpp -std=c++14

clean:
	rm -f area 
	rm -f *.o

