#ifndef _NET_HELPER_H_
#define _NET_HELPER_H_

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MSG_BUF_LEN 80

#define MSG_T_CHAT        0
#define MSG_T_CLIENT_DATA 1

typedef struct
{
    char name[MSG_BUF_LEN];
} ClientInfo;

typedef union
{
    char message[MSG_BUF_LEN];
    ClientInfo clientInfo;
} Payload;

typedef struct
{
    char type;
    Payload data;
} Message;

int make_tcp_server_socket(short port);
int make_tcp_client_socket(char* remoteName, long remoteAddr, short remotePort, short localPort);
struct sockaddr make_sockaddr(char* hostName, long hostAddr, short hostPort);
int read_file(int socket, void* bufferPointer, int bytesToRead);

#endif
