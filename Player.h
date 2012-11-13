#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

class Player : public MovingObject
{
    enum {
        INITIAL_POWER                   = 1000,
        INITIAL_NUM_ARROWS              = 20,
        MIN_TICKS_BETWEEN_ARROWS        = 3,
        SHOOT_ARROW_PROBABILITY         = 5,
        CHANGE_DIRECTION_PROBABILITY    = 5
    };

    char name;
    int power;
    int remainingArrows;
    unsigned int lastArrowTick;

    void Fight(Player* oponent);
    void SetRandomDirection();
    bool ShootArrow();
    void StepOut();

public:
    Player(char name, int power = INITIAL_POWER);
    ~Player();

    void Update();
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