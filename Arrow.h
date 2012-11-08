#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"
#include "Player.h"

class Arrow : public MovingObject
{
    bool hit;
public:
    Arrow();

    void SetSquare(Square* square);
    bool Update();
    void Draw();
};

#endif