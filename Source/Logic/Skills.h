#ifndef SKILLS_H
#define SKILLS_H

#include "../Engine/VEntity.h"

enum class SKILLTYPE
{
    HEAL,
    DMG,
    BUFF,
    DEBUFF,
    BIGHEAL,
    SPAWN
};

struct skill{
  float curX;
  float curY;
  int radius;
  int val;
  SKILLTYPE st;
};

struct skill_notify{
  int timer;
  Marx::VEntity *entity;
};

#endif
