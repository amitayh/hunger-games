#ifndef _WALL_H
#define _WALL_H

#include "Object.h"

class Wall : public Object
{
public:
    void Draw();
    void SetSquare(Square* square);
};

#endif