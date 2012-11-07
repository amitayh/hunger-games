#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "Object.h"
#include "Player.h"

class DroppingObject : public Object
{
	int dropProbability;
public:
	DroppingObject();

    virtual void Affect(Player* player);
};

#endif