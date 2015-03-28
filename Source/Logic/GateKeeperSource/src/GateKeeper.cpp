#include "GateKeeper.h"
#include "../../Event.h"

GateKeeper::~GateKeeper()
{

}

void GateKeeper::update(const sf::Time& t)
{
  std::vector< Marx::Event > eventQueue = controller->getEvents();

  for( std::vector< Marx::Event >::iterator it = eventQueue.begin()
     ; it != eventQueue.end()
     ; ++it )
  {
      // switch on type
      switch(it->type)
      {
      case ::Marx::MOVE:
          MoveEvent* ev = (MoveEvent*) (&*it);
          printf( "move: x:%f y:%f force:%d\n",
              ev->getX(), ev->getY(), ev->forced() );
          move( ev->getX(), ev->getY(), ev->forced() );
          MoveEvent me(ev->getX(),ev->getY(),ev->forced());
          controller->addEvent(me);
          break;
      }
  }

  eventQueue.clear();
}

void GateKeeper::detectPlayers()
{

}

void GateKeeper::enterCombat()
{

}

void GateKeeper::leaveCombat()
{

}

bool GateKeeper::inCombatRange()
{
  return true;
}

void GateKeeper::setRange(int r)
{

}

void GateKeeper::setHealth(int h)
{

}

void GateKeeper::setAttack(int as)
{

}

void GateKeeper::setAttackSpeed(int as)
{

}

void GateKeeper::setMovementSPed(int ms)
{

}

void GateKeeper::setTarget(/*Player*/)
{

}

void GateKeeper::setCooldown(/*Timer*/)
{

}

int GateKeeper::getRange()
{
  return _range;
}

int GateKeeper::getHealth()
{
  return _health;
}

int GateKeeper::getAttack()
{
  return _attack;
}

int GateKeeper::getAttackSpeed()
{
  return _attackSpeed;
}

int GateKeeper::getMovementSpeed()
{
  return _movementSpeed;
}
//virtual Vessel getTarget();
time_t GateKeeper::getCooldown()
{
  return _cooldown;
}

void GateKeeper::turn()
{

}

void GateKeeper::onCreate()
{

}

void GateKeeper::onDestroy()
{

}

void GateKeeper::onUpdate()
{

}

bool GateKeeper::operator==(const VEntity&)
{
  return true;
}
