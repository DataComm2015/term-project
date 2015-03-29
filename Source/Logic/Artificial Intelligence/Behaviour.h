#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_

class Behaviour
{
    public:
        virtual void init();
        virtual void update(float deltaTime);
};

#endif
