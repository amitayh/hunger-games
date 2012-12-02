#ifndef _BOT_H
#define _BOT_H

#include "Player.h"

class Bot : public Player
{
public:
    Bot(char name);

    void update();
};

#endif