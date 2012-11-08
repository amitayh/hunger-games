#ifndef _FOOD_H
#define _FOOD_H

#include "DroppingObject.h"

const int DROP_FOOD_PROBABILITY = 1;

class Food : public DroppingObject
{
public:
    void Affect(Player* player);
	void Draw();
};

#endif