#ifndef PROPER_ENTITY_H
#define PROPER_ENTITY_H

#include "../../Engine/Entity.h"
#include "../../Engine/Controller.h"

class ProperEntity : public Marx::Entity
{
public:
    ProperEntity(Marx::Map*,float,float,Marx::Controller*,float,float);
    virtual void onUpdate();
private:
     Marx::Controller* controller;
};

#endif
