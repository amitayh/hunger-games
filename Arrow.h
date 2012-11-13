#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"
#include "Player.h"

class Arrow : public MovingObject
{
    bool hit;

    bool CheckHit();

public:
    Arrow(Player* shooter);

    void Update();
    void Draw();
    void SetSquare(Square* square);
    bool GetHit();
};

#endif