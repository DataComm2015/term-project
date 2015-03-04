#include "Client.h"



Client::Client()
{
    readProcess = new ReceiveProcess();
    sendProcess = new SendProcess();
    entityMux   = new NetworkEntityMultiplexer();
    session     = null;
}

Client::~Client()
{
    delete readProcess;
    delete sendProcess;
    delete entityMux;
    delete session;
}

int Client::connect( unsigned long address, unsigned short port )
{
    socket s;
    if( ( s = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
        perror( "Can't create socket\n" );
        return 1;
    }
    
    struct sockaddr_in server;
    memset( &server, 0, sizeof( struct sockaddr_in ) );
    server.sin_family      = AF_INET;
    server.sin_port        = htons( port );
    server.sin_addr.s_addr = htonl( address );
    
    if( connect( s, (struct sockaddr *)&server, sizeof( server ) ) == -1 )
    {
        perror( "Can't connect to server\n" );
        return 1;
    }
    
    session = new Session( s
                         , readProcess
                         , sendProcess
                         , entityMux );
    
    readProcess->addSession( session );
    sendProcess->addSession( session );
    
    onConnect( session );
    return 0;
}