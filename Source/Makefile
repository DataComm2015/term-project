CXX=g++
CPPFLAGS=-std=c++11 -g
CLIENT_EXE=Soujourn
SERVER_EXE=SoujournServer

## FILES

FILES_ENGINE=	AppWindow.o \
				Engine/Scene.o \
				Engine/Cell.o \
				Engine/Controller.o \
				Engine/Map.o \
				Engine/TextureManager.o \
				Engine/TileManager.o \
				Engine/Entity.o \
				Engine/ProjectileManager.o \
				Engine/Projectile.o \
				Engine/VEntity.o \
				Engine/EGTheSpinner.o \
				Engine/AttackAction.o

FILES_MULTIMEDIA=	Multimedia/graphics/object/BGO.o \
					Multimedia/graphics/object/SGO.o \
					Multimedia/graphics/object/TGO.o \
					Multimedia/graphics/Renderer.o \
					Multimedia/manager/ResourceManager.o \
					Multimedia/graphics/Animation.o \
					Multimedia/gui/Label.o \
					Multimedia/gui/Button.o \
					Multimedia/gui/Container.o \
					Multimedia/gui/TextBox.o \
					Multimedia/gui/HealthBar.o \
					Multimedia/manager/ResourceManager.o \
					Multimedia/manager/MusicManager.o \
					Multimedia/manager/SoundManager.o

FILES_LOGIC=	Logic/Environment/Block.o \
				Logic/Environment/GameMap.o \
				Logic/GameScene.o \
				Logic/Entities/Vessel.o \
				Logic/Environment/EnemyHierarchy.o \
				Logic/Event.o \
				Logic/ServerGameScene.o \
				Logic/ServerLobbyScene.o \
				Logic/ClientScoreboardScene.o \
				Logic/Entities/CommandEntity.o \
				Logic/Entities/ClientMux.o \
				Logic/Entities/ClientNetworkController.o \
				Logic/Entities/ProperEntity.o \
				Logic/Entities/PlayerEntity.o \
				Logic/Entities/ServerNetworkController.o \
				Logic/ServerCommand.o \
				Logic/ClientLobbyScene.o \
				Logic/MainMenuScene.o \
				Logic/Entities/ClientGameState.o \
				Logic/GateKeeperSource/src/GateKeeper.o \
				Logic/GateKeeperSource/src/Minion.o \
				Logic/GateKeeperSource/src/MiniBoss.o \
				Logic/GateKeeperSource/src/MiniBee.o \
				Logic/Entities/Structure.o \
				Logic/Entities/ServerGameState.o \
				Logic/CreditScene.o \
				Logic/Creature.o \
				Logic/EntityFactory.o \
				Logic/Entities/ServerEnemyController.o

FILES_NETWORK=	Network/Client.o \
				Network/Server.o \
				Network/semaphores.o \
				Network/Session.o \
				Network/select_helper.o \
				Network/net_helper.o \
				Network/NetworkEntityMultiplexer.o \
				Network/NetworkEntity.o

FILE_CLIENT=	Client.cpp
FILE_SERVER=	Server.cpp

## Targets

all: client server

client: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_CLIENT)
	$(CXX) $(CPPFLAGS) \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_CLIENT) \
	-o $(CLIENT_EXE) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lsfml-audio


server: $(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_SERVER)
	$(CXX) $(CPPFLAGS) \
	$(FILES_ENGINE) $(FILES_MULTIMEDIA) $(FILES_LOGIC) $(FILES_NETWORK) $(FILE_SERVER) \
	-o $(SERVER_EXE) -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lsfml-audio

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(CLIENT_EXE) $(SERVER_EXE)
