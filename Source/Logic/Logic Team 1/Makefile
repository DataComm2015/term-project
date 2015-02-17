# Map Generation Test Makefile

CC=g++ -ggdb -W -pedantic 

mapgen: Cell.o Main.o GameMap.o
	$(CC) -o mapgen Cell.o Main.o GameMap.o

clean:
	rm -f *.o core.* mapgen*

Main.o:
	$(CC) -c Main.cpp 

GameMap.o:
	$(CC) -c GameMap.cpp 

Cell.o:
	$(CC) -c Cell.cpp 