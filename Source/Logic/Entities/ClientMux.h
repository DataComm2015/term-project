#ifndef _CLIENT_MUX_H_
#define _CLIENT_MUX_H_

#include "Network/NetworkEntityMultiplexer.h"

/**
 * the client's implementation of the {NetworkEntityMultiplexer}. this thing is
 *   going to need more work.
 *
 * when the server registers the {ServerController} and {Player} instances with
 *   the client, {Mux::onRegister} will be triggered which. it should create a
 *   {NetworkController} and {Command} instances respectively.
 */
class ClientMux : public NetworkEntityMultiplexer
{
    public:
        ClientMux();
        virtual ~ClientMux();
        virtual NetworkEntity* onRegister(int id,
                                          int entityType,
                                          Session* session,
                                          Message msg);
};

#endif
