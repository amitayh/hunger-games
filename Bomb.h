#ifndef _BOMB_H
#define _BOMB_H

#include "DroppingObject.h"

class Bomb: public DroppingObject
{
public:
    Bomb();

    void affect(Player& player);

    void draw() const;
};

#endif