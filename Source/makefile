######################################################################
# This file is set up to compile object files to the team directories
# hopefully this will prevent conflicts.
#
# If you have a better way to set up this file, and I know there are
# probably many, please feel free to rewrite it.
######################################################################

$CC=g++
$FLAGS=-std=c++11




Game: AppWindow.o Engine/Scene.o Engine/EG_Scene.o Engine/Entity.o Engine/Cell.o Engine/Controller.o Logic/Environment/Block.o Logic/Environment/GameMap.o
	$(CC) AppWindow.o Engine/Scene.o Engine/EG_Scene.o Engine/Cell.o \
	Engine/Controller.o Logic/Environment/Block.o Logic/Environment/GameMap.o \
	-o app -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system $(FLAGS)

clean:
	rm -f -r *.o *.bak app */*.o


#Engine Files
AppWindow.o:
	$(CC) -c -std=c++11 -o AppWindow.o  AppWindow.cpp 
	
Engine/EG_Scene.o:
	$(CC) -c -std=c++11 -o Engine/EG_Scene.o Engine/EG_Scene.cpp
	
Engine/Cell.o:
	$(CC) -c Engine/Cell.cpp -o Engine/Cell.o $(FLAGS)
	
	
Engine/Controller.o:
	$(CC) -c Engine/Controller.cpp -o Engine/Controller.o $(FLAGS)
	
Engine/Entity.o:
	$(CC) -c -std=c++11 -o Engine/Entity.o Engine/Entity.cpp

Engine/EntityManager.o:
	$(CC) -c Engine/EntityManager.cpp -o Engine/EntityManager.o $(FLAGS)
	
Engine/Lobby.o:
	$(CC) -c Engine/Lobby.cpp -o Engine/Lobby.o $(FLAGS)
	
Engine/Map.o:
	$(CC) -c Engine/Map.cpp -o Engine/Map.o $(FLAGS)
	
Engine/Scene.o:
	$(CC) -c Engine/Scene.cpp -o Engine/Scene.o $(FLAGS)
	
Engine/TextureManager.o:
	$(CC) -c TextureManager.cpp -o TextureManager.o $(FLAGS)
	
Engine/TileManager.o:
	$(CC) -c TileManager.cpp -o TileManager.o $(FLAGS)
	
Engine/World.o:
	$(CC) -c World.cpp -o Engine/World.o -o World.o $(FLAGS)


# Logic Files

Logic/Environment/Block.o:
	$(CC) -c Logic/Environment/Block.cpp -o Logic/Environment/Block.o $(FLAGS)

Logic/Environment/GameMap.o:
	$(CC) -c Logic/Environment/GameMap.cpp -o Logic/Environment/GameMap.o $(FLAGS)