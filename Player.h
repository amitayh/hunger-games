#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

const int INITIAL_NUM_ARROWS = 3;
const int MIN_TICKS_BETWEEN_ARROWS = 3;
const int SHOOT_ARROW_PROBABILITY = 10;
const int CHANGE_DIRECTION_PROBABILITY = 10;

class Player : public MovingObject
{
    char name;
    int power;
    int remainingArrows;
    int lastArrowTick;

    void SetRandomDirection();
    bool ShootArrow();

public:
    Player(char name, int power = 1000);

    bool Update();
    void Draw();
    void SetSquare(Square* square);
    void IncreasePower(int amount);
    void DecreasePower(int amount);
    void AddArrows(int amount);
    char GetName();
    int GetPower();
    int GetRemainingArrows();
};

#endif