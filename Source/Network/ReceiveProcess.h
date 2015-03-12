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
    class Server;

    enum ReceiveMessageType
    {
        ADD_SOCKET = 0,
        REMOVE_SOCKET = 1
    };

    struct ReceiveMessage
    {
        ReceiveMessageType type;
        int socket_id;
        char data[NETWORK_MESSAGE_SIZE];
    };

    /**
     * this is a singleton class. the receive thread is started the first time
     *   getInstance is invoked. any subsequent calls will return the first one.
     *   the thread is terminated when this object is deleted.
     */
    class ReceiveProcess
    {
    public:
        ReceiveProcess(void* params, void (*handleSocket)(void* params, int socket));
        ~ReceiveProcess();
        void addSocket(int socket);
        void removeSocket(int socket);

    private:
        static void* receiveRoutine(void* params);

        void* params;

        void (*handleSocket)(void* params, int socket);

        /**
         * handle to thread that does the receiving.
         */
        pthread_t receiveThread;

        /**
         * IPC pipe used to control what to select.
         */
        int ctrlPipe[2];
    };
}

#endif
