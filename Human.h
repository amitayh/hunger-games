#ifndef _HUMAN_H
#define _HUMAN_H

#include "Player.h"

class Human : public Player
{
    enum {
        CHAR_LEFT   = 'A',
        CHAR_RIGHT  = 'D',
        CHAR_UP     = 'W',
        CHAR_DOWN   = 'S'
    };

public:
    Human(char name);

    void update();
};

#endif