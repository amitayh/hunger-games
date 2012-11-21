#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Game;

class Arrow
{
    enum {
        MOVE_INTERVAL = 1
    };

    Square *square;
    Direction direction;
    bool hit;

    void SetSquare(Square &square);
    bool CheckHit();

public:
    Arrow(Player &shooter, Square &square);
    ~Arrow();

    void Update(Game &game);
    void Draw() const;
    bool GetHit() const;
};

#endif