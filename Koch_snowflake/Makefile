koch: main.o snowflake.o
	g++ -o koch main.o snowflake.o -lsfml-window -lsfml-system -lsfml-graphics -std=c++14

main.o: main.cpp
	g++ -c main.cpp -lsfml-window -lsfml-system -lsfml-graphics -std=c++14

snowflake.o: snowflake.cpp
	g++ -c snowflake.cpp -lsfml-window -lsfml-system -lsfml-graphics -std=c++14

clean:
	rm -rf koch
	rm -rf *.o
