#ifndef SERVER_H_
#define SERVER_H_

#include <vector.h>

namespace Networking
{
	class Session;
	class SendProcess;
	class ReceiveProcess;

    class Server
    {
    public:
        /**
         * constructs a new {Server}.
         */
        Server();

		/**
		 * Clean up the Server on destruction.
		 */
		~Server();

        /**
         * initializes the server to listen for incoming connections on the given port
         *
         * @param  port to connect to
         *
         * @return integer indicating the outcome of the operation
         */

        int startServer(short port);
        /**
         * stops server
         *
         * @param  port server is currently listening to
         * @return integer indicating the outcome of the operation
         */
        int stopServer(short port);

        /**
         * function to be overridden by children
         *
         * @param  session
         */
        virtual void onConnect(Session* session) = 0;

    private:
		static void *listeningThread(void *server);
		unsigned int listeningSocket;
		std::vector<Session*> sessions;
		SendProcess *sendProcess;
		ReceiveProcess *receiveProcess;
    };
}

#endif
