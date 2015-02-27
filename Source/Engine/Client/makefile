# Makefile for engine

$CC=g++



test: Scene.o AppWindow.o
	$(CC) AppWindow.o -o app -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o *.bak app 

Scene.o:
	$(CC) -c Scene.cpp -std=c++11 


AppWindow.o:
	$(CC) -c AppWindow.cpp -std=c++11
	
