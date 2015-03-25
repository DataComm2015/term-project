#ifndef PROPER_ENTITY_H
#define PROPER_ENTITY_H

#include "../Engine/Entity.h"

class ProperEntity : public Marx::Entity
{
public:
    ProperEntity(Marx::Map*,float,float,Marx::Controller*,float,float);
    virtual void onUpdate();
private:
     Controller* controller;
};

#endif
