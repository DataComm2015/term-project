#include "NetworkEntityMultiplexer.h"

Mux::Mux()
{
}

Mux::~Mux()
{
}

NetworkEntity* Mux::onRegister(int id,
                               int entityType,
                               Session* session,
                               Message msg)
{
    NetworkEntity* ret;

    switch(entityType)
    {
        case NET_ENT_PAIR_PLAYER_COMMAND:
            ret = new Command(id);
            break;

        // later, should parse the message to figure out what kind of game
        // entity to create that is being controlled by the NetworkController.
        case NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER:
            ret = new NetworkController(id);
            Marx::Map* cMap = ((GameScene*)scene)->getcMap();
            new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ret,1.0,1.0);
            break;
    }

    return ret;
};
