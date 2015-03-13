CXX=g++
CPPFLAGS=-std=c++11
CLIENT_EXE=app
SERVER_EXE=serv

## FILES

FILES_ENGINE=		AppWindow.o Engine/Scene.o Engine/Cell.o Engine/Controller.o Engine/Map.o \
					Engine/TextureManager.o Engine/TileManager.o Engine/ServerGameScene.o

FILES_MULTIMEDIA=	Multimedia/graphics/object/BGO.o Multimedia/graphics/object/SGO.o Multimedia/graphics/object/TGO.o \
					Multimedia/graphics/Renderer.o Multimedia/manager/ResourceManager.o

FILES_LOGIC=		Logic/Environment/Block.o Logic/Environment/GameMap.o Logic/GameScene.o

FILES_NETWORK=		Network/Server.o Network/Session.o Network/select_helper.o Network/net_helper.o Network/NetworkEntityMultiplexer.o Network/NetworkEntity.o


FILE_CLIENT=			Client.cpp
FILE_SERVER=			Server.cpp

##

all: client server

client: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_CLIENT)
	$(CXX) $(CPPFLAGS) \
	-o $(CLIENT_EXE) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lpthread \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_CLIENT) 

server: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_SERVER)
	$(CXX) $(CPPFLAGS) \
	-o $(SERVER_EXE) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lpthread \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_SERVER)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(CLIENT_EXE) $(SERVER_EXE)
