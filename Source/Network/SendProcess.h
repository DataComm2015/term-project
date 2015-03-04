#ifndef _SEND_PROCESS_H_
#define _SEND_PROCESS_H_

#include "map.h"

namespace Networking
{
	struct Message;
	class Session;

	enum SendMessageType
	{
		ADD_SOCKET = 0,
		REMOVE_SOCKET = 1,
		SEND_MESSAGE = 2,
		SHUTDOWN = 3
	};

	struct SendMessage
	{
		SendMessageType type;
		int socket;
		char data[NETWORK_MESSAGE_SIZE];
	};

	class SendProcess
	{
		public:
			SendProcess();
			~SendProcess();
			void send(Session *session, Message *message_s);
			void addSession(Session *session);
			void removeSession(Session *session);
		
		private:
			void awaitFurtherInstructions();
		
			int pid;
			int qid;
			std::map<int, int> sockets;
	};
}

#endif
