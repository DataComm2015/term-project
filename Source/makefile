######################################################################
# This file is set up to compile object files to the team directories
# hopefully this will prevent conflicts.
#
# If you have a better way to set up this file, and I know there are
# probably many, please feel free to rewrite it.
######################################################################

CC=g++
CFLAGS=-std=c++11

Game:               AppWindow.o Engine/Scene.o Engine/EG_Scene.o Engine/Cell.o Engine/Controller.o
	$(CC) $(CFLAGS) AppWindow.o Engine/Scene.o Engine/EG_Scene.o Engine/Cell.o Engine/Controller.o \
	-o app -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f -r *.o *.bak app */*.o

#Engine Files

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Engine/%.o: Engine/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
