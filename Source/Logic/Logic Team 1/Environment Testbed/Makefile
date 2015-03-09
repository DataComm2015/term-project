# Map Generation Test Makefile

CC=g++ -std=c++11 -ggdb -W -pedantic 

mapgen: Cell.o Main.o GameMap.o Block.o
	$(CC) -o mapgen Cell.o Main.o GameMap.o Block.o

clean:
	rm -f *.o core.* mapgen*

Main.o:
	$(CC) -c Main.cpp 

GameMap.o:
	$(CC) -c GameMap.cpp 

Cell.o:
	$(CC) -c Cell.cpp 

Block.o:
	$(CC) -c Block.cpp