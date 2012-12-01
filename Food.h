#ifndef _FOOD_H
#define _FOOD_H

#include "DroppingObject.h"

class Food : public DroppingObject
{
public:
    void affect(Player& player);

    void draw() const;
};

#endif