#ifndef _WALL_H
#define _WALL_H

#include "Object.h"

class Wall : public Object
{
public:
    Wall();

	void Draw();
    bool SetSquare(Square* square);
};

#endif