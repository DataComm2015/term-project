#include "net_helper.h"

#define LISTENQ 5

static void fatal_error(const char* errstr);

/**
 * creates a new server socket, and returns the new server socket's file
 *   descriptor.
 *
 * @function   make_tcp_server_socket
 *
 * @date       2015-03-05
 *
 * @revision   none
 *
 * @designer   Eric Tsang
 *
 * @programmer Eric Tsang
 *
 * @note       none
 *
 * @signature  int make_tcp_server_socket(short port)
 *
 * @param      port port number on local host to bind the new server socket to.
 *
 * @return     socket file descriptor to the new server socket
 */
int make_tcp_server_socket(short port)
{
    // local address that server socket is bound to
    struct sockaddr localAddr;
    // socket file descriptor to the new server socket
    int svrSock;

    // create TCP socket
    if((svrSock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fatal_error("failed to create TCP socket");
    }

    // set sock opt to reuse address
    int arg = 1;
    if(setsockopt(svrSock,SOL_SOCKET,SO_REUSEADDR,&arg,sizeof(arg)) == -1)
    {
        fatal_error("failed to set sock opt to reuse address");
    }

    // bind server socket to local host
    localAddr = make_sockaddr(0, INADDR_ANY, port);
    if(bind(svrSock, (struct sockaddr*) &localAddr, sizeof(localAddr)) == -1)
    {
        fatal_error("failed to bind server socket to address structure");
    }

    // put server socket into listening mode
    listen(svrSock, LISTENQ);

    // return...
    return svrSock;
}

/**
 * craetes a new socket that is connected to the specified remote host.
 *
 * @function   make_tcp_client_socket
 *
 * @date       2015-03-05
 *
 * @revision   none
 *
 * @designer   Eric Tsang
 *
 * @programmer Eric Tsang
 *
 * @note       none
 *
 * @signature  int make_tcp_client_socket(char* remoteName, long remoteAddr,
 *   short remotePort, short localPort)
 *
 * @param      remoteName name of the remote host. either this, or {remoteAddr}
 *   needs to be specified; one of them can be 0, but not both.
 * @param      remoteAddr address in host byte ordering of the remote host.
 *   either this, or {remoteName} needs to be specified; one of them can be 0,
 *   but not both.
 * @param      remotePort the remote host's port.
 * @param      localPort the local port. can be 0 if you don't care.
 *
 * @return     socket file descriptor to the new connected client socket
 */
int make_tcp_client_socket(char* remoteName, long remoteAddr, short remotePort, short localPort)
{
    // local address that client socket is bound to
    struct sockaddr local;
    // remote address that client socket should connect to
    struct sockaddr remote;
    // socket file descriptor to the new client socket
    int clntSock;

    // create TCP socket
    if((clntSock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("failed to create TCP socket");
        return -1;
    }

    // bind socket to local host if a local port is specified
    if(localPort)
    {
        local = make_sockaddr(0, INADDR_ANY, localPort);
        if(bind(clntSock, (struct sockaddr*) &local, sizeof(local)) == -1)
        {
            printf("failed to bind socket to local host");
            return -1;
        }
    }

    // connect socket to remote host
    remote = make_sockaddr(remoteName, remoteAddr, remotePort);
    if(connect(clntSock, (struct sockaddr*) &remote, sizeof(remote)) == -1)
    {
        printf("failed to connect to remote host");
        return -1;
    }

    // return...
    return clntSock;
}

/**
 * makes a address structure. the hostPort must be provided. if {hostName} is
 *   specified, the function will perform a query to find the remote IP. if
 *   {hostName} is not provided, then the IP address used will be {hostAddr}.
 *
 * @function   make_sockaddr
 *
 * @date       2015-03-05
 *
 * @revision   none
 *
 * @designer   Eric Tsang
 *
 * @programmer Eric Tsang
 *
 * @note       none
 *
 * @signature  struct sockaddr make_sockaddr(char* hostName, long hostAddr, short hostPort)
 *
 * @param      hostName optional. name of the remote host. either this, or
 *   {hostAddr} must be specified.
 * @param      hostAddr optional. IP address of host. either this or {hostName}
 *   must be specified.
 * @param      hostPort the host's port number.
 *
 * @return     sockaddr structure with the provided {hostPort}, and appropriate
 *   IP address.
 */
struct sockaddr make_sockaddr(char* hostName, long hostAddr, short hostPort)
{
    // address that client socket should connect to
    struct sockaddr_in addr;

    // set up port and protocol of address structure
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(hostPort);

    if(hostName == 0)
    {
        /*
         * hostName is not provided; just use {hostAddr} as address...
         */

        // set address structure's address
        addr.sin_addr.s_addr = htonl(hostAddr);
    }
    else
    {
        /*
         * hostName is provided; do query for host then result as address...
         */

        // resolve host (if needed)
        struct hostent* host;
        if((host = gethostbyname(hostName)) == 0)
        {
            printf("failed to resolve host");
        }

        // set address structure's address from query results
        memcpy(&addr.sin_addr, host->h_addr, host->h_length);
    }

    // return...
    {
        struct sockaddr ret;
        memcpy(&ret, &addr, sizeof(ret));
        return ret;
    }
}

/**
 * reads from a socket, and returns when the read finishes, EOF occurs, or an
 *   error is thrown.
 *
 * @function   read_file
 *
 * @date       2015-03-05
 *
 * @revision   none
 *
 * @designer   Eric Tsang
 *
 * @programmer Eric Tsang
 *
 * @note       none
 *
 * @signature  int read_file(int socket, void* buffer, int bytesToRead)
 *
 * @param      socket socket file descriptor.
 * @param      buffer pointer to a buffer to read data from the socket into.
 * @param      bytesToRead number of bytes to read from socket into buffer.
 *
 * @return     non-zero if the read was successful, 0 on when the socket closes,
 *   and -1 on error.
 */
int read_file(int socket, void* bufferPointer, int bytesToRead)
{
    int bytesRead;
    int result = 0;
    char* bufPtr = (char*) bufferPointer;

    // read message from socket
    while(bytesToRead > 0
        && (bytesRead = read(socket,bufPtr,bytesToRead)) > 0)
    {
        bufPtr += bytesRead;
        bytesToRead -= bytesRead;
        result += bytesRead;
    }

    return result;
}

static void fatal_error(const char* errstr)
{
    perror(errstr);
    exit(errno);
}
