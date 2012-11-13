#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

class Player : public MovingObject
{
    char name;
    int power;
    int remainingArrows;
    unsigned int lastArrowTick;

    void Fight(Player* oponent);
    void SetRandomDirection();
    bool ShootArrow();
    void StepOut();

public:
    static const int INITIAL_POWER;
    static const int INITIAL_NUM_ARROWS;
    static const int MIN_TICKS_BETWEEN_ARROWS;
    static const int SHOOT_ARROW_PROBABILITY;
    static const int CHANGE_DIRECTION_PROBABILITY;

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