# Makefile for engine

$CC=g++


# Not sure why but on some computers -lstdc++ is requred to compile this.
test: Scene.o AppWindow.o EG_Scene.o
	$(CC) AppWindow.o Scene.o EG_Scene.o -o app -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o *.bak app 

Scene.o:
	$(CC) -c Engine/Scene.cpp -std=c++11 


AppWindow.o:
	$(CC) -c AppWindow.cpp -std=c++11
	
EG_Scene.o: Scene.o
	$(CC) -c Engine/EG_Scene.cpp -std=c++11