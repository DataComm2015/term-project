#ifndef CLIENT_H_
#define CLIENT_H_

#include "Session.h"

namespace Networking
{
    class Client
    {
    public:
        /**
         * constructs a new {Client}.
         */
        Client();
        ~Client();
        /**
         * attempts to connect the client to a server using parameters
         *
         * @param  address IP address to connect to
		 * @param  port to connect to
         *
         * @return integer indicating the outcome of the operation
         */
        int connect(unsigned long address, short port);
		/**
         * function to be overriden by children
         *
         * @param  session
         */
		virtual void onConnect(Session* session) = 0;
		
	private:
        Session                  * session;
        ReceiveProcess           * readProcess;
        SendProcess              * sendProcess;
        NetworkEntityMultiplexer * entityMux;
    
    };
}

#endif