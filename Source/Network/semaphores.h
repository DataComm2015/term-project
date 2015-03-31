#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

bool releaseSem(int sid);
bool accessSem(int sid);
bool deleteSem(int sid);
int createSem(int key);
int initSessionSem(int key);


#endif // SEMAPHORES_H

