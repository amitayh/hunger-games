#ifndef _DROPPING_OBJECT_H
#define _DROPPING_OBJECT_H

#include "Object.h"

class DroppingObject : public Object
{
	double dropProbability;
public:
	DroppingObject();
};

#endif