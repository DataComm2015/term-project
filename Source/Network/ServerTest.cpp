#include <stdio.h>

#include "Server.h"

int main(void)
{
    using Networking::Server;

    Server* svr = new Server();

    svr->startServer(7000);
    printf("server started\n");
    getchar();

    svr->stopServer();
    printf("server stopped\n");
    getchar();

    delete svr;
    printf("server deleted\n");
    getchar();

    return 0;
}
