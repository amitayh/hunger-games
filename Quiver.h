#ifndef _QUIVER_H
#define _QUIVER_H

#include "DroppingObject.h"

const int DROP_QUIVER_PROBABILITY = 1;

class Quiver : public DroppingObject
{
public:
    void Affect(Player* player);
	void Draw();
};

#endif