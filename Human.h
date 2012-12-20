#ifndef _HUMAN_H
#define _HUMAN_H

#include "BasePlayer.h"

class Human: public BasePlayer
{
    static const char KEY_LEFT                      = 'A';
    static const char KEY_RIGHT                     = 'D';
    static const char KEY_UP                        = 'W';
    static const char KEY_DOWN                      = 'S';
    static const char KEY_SHOOT_REGULAR_ARROW       = 'P';
    static const char KEY_SHOOT_EXPLODING_ARROW     = 'I';
    static const char KEY_SHOOT_PENETRATING_ARROW   = 'O';
    static int numInstances;

public:
    Human(char name, Console::Color color);

    virtual void update();
};

#endif