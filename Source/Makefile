CXX=g++
CPPFLAGS=-std=c++11
EXE=app

## FILES

FILES_ENGINE=		AppWindow.o Engine/Scene.o Engine/Cell.o Engine/Controller.o Engine/Map.o \
					Engine/TextureManager.o Engine/TileManager.o

FILES_MULTIMEDIA=	Multimedia/graphics/object/BGO.o Multimedia/graphics/object/SGO.o Multimedia/graphics/object/TGO.o \
					Multimedia/graphics/Renderer.o Multimedia/manager/ResourceManager.o

FILES_LOGIC=		Logic/Environment/Block.o Logic/Environment/GameMap.o Logic/GameScene.o Logic/Champion/Vessel.o

FILES_NETWORK=		

FILE_MAIN=			ClientDriver.cpp

##

all: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_MAIN)
	$(CXX) $(CPPFLAGS) \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_MAIN) \
	-o $(EXE) -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(EXE)