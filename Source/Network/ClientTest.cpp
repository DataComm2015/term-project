#include <stdio.h>

#include "Client.h"
#include "NetworkEntityMultiplexer.h"
using namespace Networking;

class mux : public NetworkEntityMultiplexer
{
public:
    mux() {};
    virtual ~mux() {};
}; 


int main(void)
{

    NetworkEntityMultiplexer::setInstance(new mux());

    Client* clnt = new Client();

    clnt->connect("192.168.0.21",7000);
    printf("client connected\n");
    getchar();

    delete clnt;
    printf("client deleted\n");
    getchar();

    return 0;
}
