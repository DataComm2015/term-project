#ifndef CLICK_LISTENER_H_
#define CLICK_LISTENER_H_

class ClickListener
{
    friend class GameScene;
protected:
    virtual void onMouseClick(int key, int srcid, float xpos, float ypos) = 0;
};

#endif
