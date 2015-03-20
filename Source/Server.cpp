//> In the main file
#include "AppWindow.h"
#include "Usage.cpp"
#include "Engine/ServerGameScene.h"
#include "Network/Server.h"
#include "Network/Session.h"
#include "Network/NetworkEntityMultiplexer.h"

#define DEFAULT_PORT 7000
#define DEBUG

bool isRunning;
sf::Time m_elapsedTime, m_timePerFrame, m_timeSinceLastUpdate;
Scene *scene;

void run();

class mux : public Networking::NetworkEntityMultiplexer
{
public:
	mux() {};
	virtual ~mux() {};
};

class MyServer : public Networking::Server
{
public:
	MyServer()
	{
	}
	virtual void onConnect(Networking::Session* session)
	{
		printf("new connection\n");
	}
	virtual void onMessage(Networking::Session* session, char* data, int len)
	{
		printf("message\n");
	}
	virtual void onDisconnect(Networking::Session* session, int remote)
	{
		printf("disconnection\n");
	}
private:
};

int main( int argc, char ** argv )
{
	Networking::NetworkEntityMultiplexer::setInstance(new mux());
	MyServer server;
	server.startServer(atoi(argv[1]));
	scene = new ServerGameScene();
	run();
	delete scene;
	return 0;
}

void run()
{
	if (!isRunning)
	{
		isRunning = true;

		sf::Clock clock;
		sf::Event event;

		// LOOP
		while (isRunning)
		{
			// TIME UPDATES
			m_elapsedTime = clock.restart();
			m_timeSinceLastUpdate += m_elapsedTime;

			// TIME PER FRAME CONTROLLED LOOP
			while (m_timeSinceLastUpdate > m_timePerFrame)
			{
				m_timeSinceLastUpdate -= m_timePerFrame;

				scene->update(m_timePerFrame);
			}
		}

		isRunning = false;
	}
}
