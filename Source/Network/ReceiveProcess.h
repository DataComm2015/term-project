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
        static ReceiveProcess* getInstance();
        void addSession(Session *session);
        void removeSession(Session *session);
        // void onMessageReceived(int socket, Message *message);
        // void closeProcess();

    private:
        ReceiveProcess();
        ~ReceiveProcess();
        void receiveRoutine();
        // static void sig_handler(int signum);

        /**
         * pointer to the singleton receive process.
         */
        static ReceiveProcess* instance;

        /**
         * IPC pipe used to send data to the receive process.
         */
        int recvPipe[2];

        /**
         * IPC pipe used to send data to the main process.
         */
        int mainPipe[2];

        /**
         * used to send sockets across processes; used to send sockets from the
         *   main process to the receive process when adding new sockets to the
         *   receive process to select from.
         */
        int ipcsock[2];

        /**
         * used only on the receive process.
         *
         * maps sockets on the main process to sockets on the receive process.
         *   although sockets may be physically the same, they have different
         *   descriptor numbers on different processes.
         */
        std::map<int, int> sockets;

        /**
         * used only on the main process.
         *
         * maps sockets to their corresponding sessions.
         */
        std::map<int, Session*> sessions;
    };
}

#endif
