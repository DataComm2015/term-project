#include <stdio.h>

#include "Server.h"

int main(void)
{
    using Networking::Server;

    Server svr;

    svr.startServer(7000);

    getchar();

    svr.stopServer();

    getchar();

    return 0;
}
