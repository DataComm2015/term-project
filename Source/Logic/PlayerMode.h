#ifndef _PLAYER_MODE_H_
#define _PLAYER_MODE_H_

enum class PLAYER_MODE
{
    VESSEL,
    GHOST,
    DEITY
};

enum class PLAYER_TYPE
{
    WARRIOR,
    SHAMAN,
    LIFE,
    DEATH
};

struct PLAYER_INFO
{
  PLAYER_MODE mode;
  PLAYER_TYPE type;
};

#endif
