#ifndef _HUMAN_H
#define _HUMAN_H

#include "Player.h"

class Human : public Player
{
    enum {
        CHAR_LEFT                       = 'a',
        CHAR_RIGHT                      = 'd',
        CHAR_UP                         = 'w',
        CHAR_DOWN                       = 's',
        CHAR_SHOOT_REGULAR_ARROW        = 'p',
        CHAR_SHOOT_EXPLODING_ARROW      = 'i',
        CHAR_SHOOT_PENETRATING_ARROW    = 'o'
    };

public:
    Human(char name);

    void update();
};

#endif