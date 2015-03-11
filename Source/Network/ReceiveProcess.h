#ifndef _RECEIVE_PROCESS_H_
#define _RECEIVE_PROCESS_H_

#include <map>


#define NETWORK_MESSAGE_SIZE 512
//wasn't compiling because this was not defined.
#define BUFLEN 512


namespace Networking
{


	struct Message;
	class Session;

	enum ReceiveMessageType
	{
		ADD_SOCKET = 0,
		REMOVE_SOCKET = 1,
		MESSAGE_AVAILABLE = 2,
		SHUTDOWN = 3
	};

	struct ReceiveMessage
	{
		ReceiveMessageType type;
		int socket_id;
		char data[NETWORK_MESSAGE_SIZE];
	};

	class ReceiveProcess
	{
		public:
			ReceiveProcess();
			~ReceiveProcess();
			void addSession(Session *session);
			void removeSession(Session *session);
			void onMessageReceived(int socket, Message *message);
			void runProcess();
			void closeProcess();

		private:
			static void sig_handler(int signum);
			int pid;
			int p[2]; // game -> process pipe
			static int p2[2]; //process -> game pipe
			std::map<int, int> sockets;
			std::map<int, Session*> sessions;
			int ipcsock[2];
	};
}

#endif
