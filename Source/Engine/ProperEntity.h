#ifndef PROPER_ENTITY_H
#define PROPER_ENTITY_H

#include "Entity.h"

class ProperEntity : public Marx::Entity
{
public:
    ProperEntity(Map*,float,float,Controller*,float,float);
    virtual void onUpdate();
private:
     Controller* controller;
};

#endif
