CXX=g++
CPPFLAGS=-std=c++11
EXE=app

## FILES

FILES_ENGINE=		AppWindow.o Engine/Scene.o Engine/Cell.o Engine/Controller.o Engine/Map.o \
					Engine/TextureManager.o Engine/TileManager.o

FILES_MULTIMEDIA=	Multimedia/graphics/object/BGO.o Multimedia/graphics/object/SGO.o Multimedia/graphics/object/TGO.o \
					Multimedia/graphics/Renderer.o Multimedia/manager/ResourceManager.o

FILES_LOGIC=		Logic/Environment/Block.o Logic/Environment/GameMap.o Logic/GameScene.o

FILES_NETWORK=		

##

all: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK)
	$(CXX) $(CPPFLAGS) \
	-o $(EXE) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(EXE)