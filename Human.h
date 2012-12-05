#ifndef _HUMAN_H
#define _HUMAN_H

#include "Player.h"

class Human: public Player
{
    enum {
        DISPLAY_NAME                = 'H',
        KEY_LEFT                    = 'A',
        KEY_RIGHT                   = 'D',
        KEY_UP                      = 'W',
        KEY_DOWN                    = 'S',
        KEY_SHOOT_REGULAR_ARROW     = 'P',
        KEY_SHOOT_EXPLODING_ARROW   = 'I',
        KEY_SHOOT_PENETRATING_ARROW = 'O'
    };

public:
    Human();

    void update();

    void draw() const;
};

#endif