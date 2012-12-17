#ifndef _FOOD_H
#define _FOOD_H

#include "DroppingObject.h"

class Food: public DroppingObject
{
public:
    Food();

    void affect(BasePlayer& player);

    void draw() const;
};

#endif