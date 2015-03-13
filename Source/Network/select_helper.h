#ifndef _SELECT_HELPER_H_
#define _SELECT_HELPER_H_

#include <stdio.h>
#include <sys/select.h>
#include <set>

typedef struct
{
    std::set<int> fdSet;    // set of all file descriptors
    fd_set _selectFds;      // set of all file descriptors for internal uses
    fd_set selectFds;       // set of selected file descriptors
    int maxFd;              // integer corresponding to biggest file descriptor
} Files;

void files_init(Files* files);
int files_select(Files* files);
void files_add_file(Files* files, int newFd);
void files_rm_file(Files* files, int fd);

#endif
