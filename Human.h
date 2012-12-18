#ifndef _HUMAN_H
#define _HUMAN_H

#include "BasePlayer.h"

class Human: public BasePlayer
{
    static const char DISPLAY_NAME;
    static const char KEY_LEFT;
    static const char KEY_RIGHT;
    static const char KEY_UP;
    static const char KEY_DOWN;
    static const char KEY_SHOOT_REGULAR_ARROW;
    static const char KEY_SHOOT_EXPLODING_ARROW;
    static const char KEY_SHOOT_PENETRATING_ARROW;
    static int numInstances;

public:
    Human();

    virtual void update();
};

#endif