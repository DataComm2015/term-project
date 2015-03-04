######################################################################
# This file is set up to compile object files to the team directories
# hopefully this will prevent conflicts.
#
# If you have a better way to set up this file, and I know there are
# probably many, please feel free to rewrite it.
######################################################################

CC=g++
CFLAGS=-std=c++11

## FILES

FILES_ENGINE=		AppWindow.o Engine/Scene.o Engine/EG_Scene.o Engine/Cell.o Engine/Controller.o Engine/Map.o \
					Engine/TextureManager.o Engine/TileManager.o

FILES_MULTIMEDIA=	Multimedia/graphics/object/BGO.o Multimedia/graphics/object/SGO.o Multimedia/graphics/object/TGO.o \
					Multimedia/graphics/Renderer.o Multimedia/manager/ResourceManager.o

FILES_LOGIC=		Logic/Environment/Block.o Logic/Environment/GameMap.o Logic/GameScene.o

FILES_NETWORK=	

##

Game: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK)
	$(CC) $(CFLAGS) \
	-o app -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f -r *.o *.bak app */*.o */*/*.o