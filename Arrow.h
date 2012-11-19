#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Game;

class Arrow
{
    enum {
        MOVE_INTERVAL = 1
    };

    Square* square;
    Direction direction;
    bool hit;

    bool CheckHit();

public:
    Arrow(Player* shooter);
    ~Arrow();

    void SetSquare(Square* square);
    void Update(Game* game);
    void Draw() const;
    bool GetHit() const;
};

#endif