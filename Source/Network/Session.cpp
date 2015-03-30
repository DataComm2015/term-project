#include "Session.h"
#include "Message.h"
#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

// #define DEBUG

using namespace Networking;

Session::Session(int socket)
{
    #ifdef DEBUG
    printf("session %p connected\n",this);
    #endif
    // initialize instance variables
    this->socket    = socket;
    this->entityMux = NetworkEntityMultiplexer::getInstance();
    this->sem = createSem(SEM_KEY);
}

Session::~Session()
{
    Message* m;
    while(!messages.empty())
    {
         auto it = messages.front();
        m = it;
        free( m );
        messages.pop_front();
    }
    disconnect();
}

void Session::send(Message* msg)
{
    int packetlen = msg->len+sizeof(msg->len)+sizeof(msg->type);
    write(socket,&packetlen,sizeof(packetlen));
    write(socket,&msg->type,sizeof(msg->type));
    write(socket,&msg->len,sizeof(msg->len));
    write(socket,msg->data,msg->len);
}

void Session::disconnect()
{
    close(socket);
}
/**
 * @brief Session::onMessage
 *          takes a message from the network and adds it to the
 *          queue for later use.
 * @param msg
 *          pointer to the message received
 *
 * @designer Network Teams
 *
 * @author Jeff Bayntun, Eric Tsang
 */
void Session::onMessage(Message* msg)
{
    #ifdef DEBUG
    printf("session %p: %d:",this,msg->type);
    for(int i = 0; i < msg->len; ++i)
    {
        printf("%c",*(((char*)msg->data)+i));
    }
    printf("\n");
    #endif

    Message* message = new Message;
    message->type = msg->type;
    message->len = msg->len;
    message->data = malloc(message->len);
    memcpy(message->data, msg->data, message->len);

    accessSem(sem);
    messages.push_back(message);
    releaseSem(sem);
}

void Session::onDisconnect(int remote)
{
    #ifdef DEBUG
    printf("session %p disconnected by %s host\n",this,remote?"remote":"local");
    #endif
    for(auto entity = registeredEntities.begin();
        entity != registeredEntities.end(); ++entity)
    {
        printf("WARNING: Session@%p was disconnected before "
            "NetworkEntity@%p was unregistered\n",this,*entity);
        (*entity)->silentUnregister(this);
    }
}
/**
 * @brief Session::handleMessages
 *              passes all queued messages to the mux
 *              should messages be deleted after mux pass??
 *
 * @designer Jeff Baytun
 * @author   Jeff Bayntun
 *
 */
void Session::handleMessages()
{
    accessSem(sem);
    Message* m;

    for(auto it = messages.begin(); it != messages.end(); it++)
    {
        m = *it;
        entityMux->onMessage(this, *m);
        free(*it);
        it = messages.erase(it);
    }

    releaseSem(sem);
}


/*----------------------------------------------------------------------------------------------
-- FUNCTION: createSem
--
-- DATE: February 10, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jeff Bayntun
--
-- PROGRAMMER: Jeff Bayntun
--
-- INTERFACE: int createSem(int sid)
-- key: key for the semaphore to create
--
-- RETURNS: id of the semaphore, -1 on failure
--
-- NOTES: allows process to gain access to a semaphore object.  blocking.
-----------------------------------------------------------------------------------------------*/
int Session::createSem(int key)
{
    int sid, result;

    if( (sid = semget(key, 1, IPC_CREAT)) < 0)
    {
        perror("error creating semaphore");
        return 0;
    }
    printf("semid after semget %d", sid);
    if( (result = semctl(sid, 0, SETVAL, 0) ) == -1)
    {
        perror("error initializing semaphore");
        return 0;
    }
    printf("semid after semctl %d", sid);
    return sid;
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION: deleteSem
--
-- DATE: February 10, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jeff Bayntun
--
-- PROGRAMMER: Jeff Bayntun
--
-- INTERFACE: bool deleteSem(int sid)
-- sid: id to the semaphore to delete
--
-- RETURNS: false on error
--
-- NOTES: removes a semaphore object
-----------------------------------------------------------------------------------------------*/
bool Session::deleteSem(int sid)
{
    if(semctl(sid, 0, IPC_RMID, 0) == -1)
    {
        perror("error removing semaphore");
        return false;
    }
    return true;
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION: accessSem
--
-- DATE: February 10, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jeff Bayntun
--
-- PROGRAMMER: Jeff Bayntun
--
-- INTERFACE: bool accessSem(int sid)
-- sid: id to the semaphore to access
--
-- RETURNS: false on error
--
-- NOTES: allows process to gain access to a semaphore object.  blocking.
-----------------------------------------------------------------------------------------------*/
bool Session::accessSem(int sid)
{
    struct sembuf *sembuf_ptr;
    sembuf_ptr = (struct sembuf*) malloc (sizeof(struct sembuf));
    sembuf_ptr->sem_num = 0;
    sembuf_ptr->sem_op = -1;
    sembuf_ptr->sem_flg = SEM_UNDO;

    if( (semop(sid, sembuf_ptr, 1)) == -1)
    {
        perror("accessSem");
        return false;
    }
    free(sembuf_ptr);
    return true;
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION: releaseSem
--
-- DATE: February 10, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Jeff Bayntun
--
-- PROGRAMMER: Jeff Bayntun
--
-- INTERFACE: bool releaseSem(int sid)
-- sid: id to the semaphore to release
--
-- RETURNS: false on error
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
bool Session::releaseSem(int sid)
{
    struct sembuf *sembuf_ptr;
    sembuf_ptr= (struct sembuf *) malloc (sizeof (struct sembuf *) );
    sembuf_ptr->sem_num = 0;
        sembuf_ptr->sem_op = 1;
        sembuf_ptr->sem_flg = SEM_UNDO;

        if ((semop(sid,sembuf_ptr,1)) == -1)
    {
        printf("semop error\n");
        return false;
    }
    free(sembuf_ptr);
    return true;
}
