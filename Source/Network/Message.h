#ifndef MESSAGE_H
#define MESSAGE_H

namespace Networking
{
    struct Message
    {
        int type;
        void* data;
        int len;
    };
}

#endif
