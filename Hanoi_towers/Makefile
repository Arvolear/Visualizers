hanoi: main.o hanoi.o
	g++ -o hanoi main.o hanoi.o -std=c++14 -lsfml-window -lsfml-system -lsfml-graphics

main.o: main.cpp
	g++ -c main.cpp -std=c++14 -lsfml-window -lsfml-system -lsfml-graphics

hanoi.o: hanoi.cpp
	g++ -c hanoi.cpp -std=c++14 -lsfml-window -lsfml-system -lsfml-graphics

clean:
	rm -rf *.o
	rm -rf hanoi
