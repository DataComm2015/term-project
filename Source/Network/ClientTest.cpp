#include <stdio.h>

#include "Client.h"

using namespace Networking;

int main(void)
{
    Client* clnt = new Client();

    clnt->connect("localhost",7000);
    printf("client connected\n");
    getchar();

    delete clnt;
    printf("client deleted\n");
    getchar();

    return 0;
}