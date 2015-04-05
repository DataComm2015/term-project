#include "semaphores.h"

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
    -- RETURNS: id of the semaphore, -0 on failure
    --
    -- NOTES: allows process to gain access to a semaphore object.  blocking.
    -----------------------------------------------------------------------------------------------*/
    int createSem(int key)
    {
        int sid, result;

        if( (sid = semget(key, 1, IPC_CREAT|0660)) < 0)
        {
            perror("error creating semaphore");
            return 0;
        }

        if( (result = semctl(sid, 0, SETVAL, 0) ) == -1)
        {
            perror("error initializing semaphore");
            return 0;
        }
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
    bool deleteSem(int sid)
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
    bool accessSem(int sid)
    {
        struct sembuf *sembuf_ptr;
        sembuf_ptr = (struct sembuf*) malloc (sizeof(struct sembuf));
        sembuf_ptr->sem_num = 0;
        sembuf_ptr->sem_op = -1;
        sembuf_ptr->sem_flg = SEM_UNDO;

        if( (semop(sid, sembuf_ptr, 1)) == -1)
        {
            //perror("accessSem");
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
    bool releaseSem(int sid)
    {
        struct sembuf *sembuf_ptr;
        sembuf_ptr= (struct sembuf *) malloc (sizeof (struct sembuf *) );
        sembuf_ptr->sem_num = 0;
            sembuf_ptr->sem_op = 1;
            sembuf_ptr->sem_flg = SEM_UNDO;

            if ((semop(sid,sembuf_ptr,1)) == -1)
        {
            //printf("semop error\n");
            return false;
        }
        free(sembuf_ptr);
        return true;
    }

    int initSessionSem(int key)
    {
        int x = createSem(key);
        if(x == 0)
        {
            printf("Semaphore error SESSIONS sem, throwing\n");
            throw;
        }

        releaseSem(x);
        return x;
    }

