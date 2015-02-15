# Makefile for engine

$CC=g++


test: GameLoop.o
	g++ GameLoop.o -o sfml-app -L ../SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o *.bak test

GameLoop.o:
	$(CC) -c GameLoop.cpp -I ../SFML/include

