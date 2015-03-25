#ifndef KEY_LISTENER_H_
#define KEY_LISTENER_H_

class KeyListener
{
    friend class GameScene;
protected:
    virtual void onKeyPressed(int key) = 0;
    virtual void onKeyReleased(int key) = 0;
};

#endif
