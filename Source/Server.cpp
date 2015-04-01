//> In the main file
#include "AppWindow.h"
//#include "Usage.cpp"

#include "Engine/Scene.h"
#include "Logic/ServerCommand.h"
#include "Logic/Entities/ServerNetworkController.h"
#include "Network/NetworkEntityMultiplexer.h"

#include <string.h>
#include <stdio.h>

// namespace
using Networking::NetworkEntityMultiplexer;
using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;
using Networking::Server;

// globals
void run(ServerCommand *server);

//////////
// main //
//////////

int main( int argc, char ** argv )
{
    printf("USAGE: %s [LOCAL_PORT]\n",argv[0]);
    fflush(stdout);

    ServerCommand server;

    server.startServer(atoi(argv[1]));
    run(&server);

    return 0;
}

/**
 * the game loop.
 */
void run(ServerCommand *server)
{
    bool isRunning;
    sf::Time m_elapsedTime;
    sf::Time m_timePerFrame;
    sf::Time m_timeSinceLastUpdate;
    sf::Time m_sleepTime;

    //m_sleepTime = sf::seconds(1.0/60);
    m_timePerFrame = sf::seconds(1.0/60);

    if (!isRunning)
    {
        isRunning = true;

        sf::Clock clock;
        sf::Event event;

        // LOOP
        while (isRunning)
        {
            // process network messages
            Networking::handleSessionMessages();

            // TIME UPDATES
            m_elapsedTime = clock.restart();
            m_timeSinceLastUpdate += m_elapsedTime;

            // TIME PER FRAME CONTROLLED LOOP
            while (m_timeSinceLastUpdate > m_timePerFrame)
            {
                m_timeSinceLastUpdate -= m_timePerFrame;
                server->getActiveScene()->update(m_timePerFrame);

                //sf::sleep(m_sleepTime);
            }
        }


        isRunning = false;
    }
}
