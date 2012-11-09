#ifndef _BOMB_H
#define _BOMB_H

#include "DroppingObject.h"

class Bomb : public DroppingObject
{
public:
    void Affect(Player* player);
    void Draw();
};

#endif