#ifndef MESSAGE_H
#define MESSAGE_H

namespace Networking
{

    typedef struct
    {
        int type;
        void * data;
        int len;
    }
    Message;
}

#endif
