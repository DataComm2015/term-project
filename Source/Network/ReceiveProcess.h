#ifndef _RECEIVE_PROCESS_H_
#define _RECEIVE_PROCESS_H_

#include <map.h>

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
	}

	class ReceiveProcess
	{
		public:
			ReceiveProcess();
			~ReceiveProcess();
			void addSession(int socket);
			void removeSession(int socket);
			void onMessageReceived(int socket, Message *message);
			void closeProcess();
		
		private:
			int pid;
			int p[2];
			std::map<int, int> sockets;
			std::map<int, Session*> sessions;
			int ipcsock[2];
	};
}

#endif
