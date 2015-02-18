#ifndef SERVER_H_
#define SERVER_H_

#include "Session.h"

namespace Networking
{
    class Server
    {
    public:
        /**
         * constructs a new {Server}.
         */
        Server();
        /**
         * initializes the server to listen for incoming connections on the given port
         *
		 * @param  port to connect to
         *
         * @return integer indicating the outcome of the operation
         */
        int startServer(short port);
		/**
         * stops server listening on given port
         *
		 * @param  port server is currently listening to
         *
         * @return integer indicating the outcome of the operation
         */
        int stopServer(short port);
		/**
         * function to be overridden by children
         *
         * @param  session
         */
		abstract void onConnect(Session* session);
		
	private:
		
    
    };
}

#endif