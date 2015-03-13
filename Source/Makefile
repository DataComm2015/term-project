CXX      = g++
CPPFLAGS = -std=c++11
EXE_SVR  = server
EXE_CLNT = client

## FILES

FILES_ENGINE       = AppWindow.o Engine/Scene.o Engine/Cell.o Engine/Controller.o Engine/Map.o Engine/TextureManager.o Engine/TileManager.o

FILES_MULTIMEDIA   = Multimedia/graphics/object/BGO.o Multimedia/graphics/object/SGO.o Multimedia/graphics/object/TGO.o Multimedia/graphics/Renderer.o Multimedia/manager/ResourceManager.o

FILES_LOGIC        = Logic/Environment/Block.o Logic/Environment/GameMap.o Logic/GameScene.o

FILES_NETWORK_SVR  = Network/Client.o Network/Session.o Network/select_helper.o Network/net_helper.o Network/NetworkEntityMultiplexer.o Network/NetworkEntity.o

FILES_NETWORK_CLNT = Network/Server.o Network/Session.o Network/select_helper.o Network/net_helper.o Network/NetworkEntityMultiplexer.o Network/NetworkEntity.o

FILE_MAIN          = Usage.cpp

##

server: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK_SVR) $(FILE_MAIN)
	$(CXX) $(CPPFLAGS) \
	-o $(EXE_SVR) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK_SVR) $(FILE_MAIN)

client: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK_CLNT) $(FILE_MAIN)
	$(CXX) $(CPPFLAGS) \
	-o $(EXE_CLNT) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK_CLNT) $(FILE_MAIN)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(EXE_SVR) $(EXE_CLNT)
