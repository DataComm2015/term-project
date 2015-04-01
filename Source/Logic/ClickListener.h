#ifndef CLICK_LISTENER_H_
#define CLICK_LISTENER_H_

#include "../Engine/Event.h"

class ClickListener
{
    friend class GameScene;
protected:
    virtual void onMouseClick(int key, int srcid, enum ActionType action, float xpos, float ypos) = 0;
};

#endif
