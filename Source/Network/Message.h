#ifndef MESSAGE_H
#define MESSAGE_H

namespace Networking
{

    enum NetworkMessageType
    {
        EVENT
    };

    struct Message
    {
        int type;
        void * data;
        int len;
    };
}

#endif
