#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"
#include "Player.h"

class Arrow : public MovingObject
{
    Player* shooter;
    //bool hit;
public:
    Arrow(Player* shooter);

    //bool SetSquare(Square* square);
    //void Update();
    void Draw();
    //bool GetHit();
};

#endif