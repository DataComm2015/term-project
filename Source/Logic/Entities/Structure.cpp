#include "Structure.h"
#include <typeinfo>

Structure::Structure(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
VEntity(sprite, map, x, y, ctrl, h, w)
{

}


Structure::~Structure()
{

}


void Structure::onUpdate()
{
  
}


void Structure::turn()
{

}


void Structure::onCreate()
{

}


void Structure::onDestroy()
{

}


bool Structure::operator==(const VEntity&)
{
  return true;
}


Entity *Structure::getEntity()
{
    return this;
}
