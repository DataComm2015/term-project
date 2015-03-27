#include "GateKeeper.h"

GateKeeper::~GateKeeper()
{

}

GateKeeper::update(const sf::Time& t) override;
GateKeeper::detectPlayers();
GateKeeper::enterCombat();
GateKeeper::leaveCombat();
GateKeeper::inCombatRange();
GateKeeper::setRange(int r);
GateKeeper::setHealth(int h);
GateKeeper::setAttackSpeed(int as);
GateKeeper::setMovementSPed(int ms);
GateKeeper::setTarget(/*Player*/);
GateKeeper::setCooldown(/*Timer*/);
GateKeeper::getRange();
GateKeeper::getHealth();
GateKeeper::getAttack();
GateKeeper::getAttackSpeed();
GateKeeper::getMovementSpeed();
//virtual Vessel getTarget();
GateKeeper::time_t getCooldown();
GateKeeper::turn();
GateKeeper::onCreate();
GateKeeper::onDestroy();
GateKeeper::onUpdate();
GateKeeper::operator==(const VEntity&);
