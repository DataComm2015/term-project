#ifndef SKILLS_H
#define SKILLS_H

enum class SKILLTYPE
{
    HEAL,
    DMG,
    BUFF,
    DEBUFF
    
};

struct skill{
  float curX;
  float curY;
  int radius;
  int val;
  SKILLTYPE st;
};

#endif
