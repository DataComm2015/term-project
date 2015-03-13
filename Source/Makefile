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
FILE_CLIENT=			Client.cpp
FILE_SERVER=			Server.cpp

##

all: client server

client: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_CLIENT)
	$(CXX) $(CPPFLAGS) \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_CLIENT) \
	-o $(CLIENT_EXE) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lpthread

server: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_SERVER)
	$(CXX) $(CPPFLAGS) \
	-o $(SERVER_EXE) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lpthread \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_SERVER)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(EXE)