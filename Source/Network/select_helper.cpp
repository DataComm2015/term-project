#include "select_helper.h"

void files_init(Files* files)
{
#ifdef DEBUG
    printf("files_init(%p)\n",files);
#endif
    FD_ZERO(&files->_selectFds);
    files->maxFd = 0;
}

int files_select(Files* files)
{
#ifdef DEBUG
    printf("files_select(%p)\n",files);
#endif
    files->selectFds = files->_selectFds;
    return select(files->maxFd+1 , &files->selectFds, 0, 0, 0);
}

void files_add_file(Files* files, int newFd)
{
#ifdef DEBUG
    printf("files_add_file(%p,%d)\n",files,newFd);
#endif
    // add the file to our sets
    FD_SET(newFd, &files->_selectFds);
    files->fdSet.insert(newFd);

    // update maxFd if needed
    if(newFd > files->maxFd)
    {
        files->maxFd = newFd;
    }
}

void files_rm_file(Files* files, int fd)
{
#ifdef DEBUG
    printf("files_rm_file(%p,%d)\n",files,fd);
#endif
    // remove the file from our sets
    FD_CLR(fd, &files->_selectFds);
    files->fdSet.erase(fd);

    // update maxFd if needed
    if(fd == files->maxFd)
    {
        files->maxFd = 0;
        for(auto fd = files->fdSet.begin(); fd != files->fdSet.end(); ++fd)
        {
            if(*fd > files->maxFd)
            {
                files->maxFd = *fd;
            }
        }
    }
}
