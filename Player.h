#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

class Game;

class Player
{
    enum {
        INITIAL_POWER                   = 1000,
        INITIAL_NUM_ARROWS              = 20,
        MIN_TICKS_BETWEEN_ARROWS        = 3,
        SHOOT_ARROW_PROBABILITY         = 5,
        CHANGE_DIRECTION_PROBABILITY    = 5,
        MOVE_INTERVAL                   = 2
    };

    Square *square;
    Direction direction;
    char name;
    int power;
    int remainingArrows;
    unsigned int lastArrowTick;

    void Fight(Player *oponent);
    void SetRandomDirection();
    void ShootArrow(Game *game);
    void StepOut();

public:
    Player(char name, int power = INITIAL_POWER, Direction direction = RIGHT);
    ~Player();

    void SetSquare(Square *square);
    void Update(Game *game);
    void IncreasePower(int amount);
    void DecreasePower(int amount);
    void AddArrows(int amount);

    char GetName() const;
    int GetPower() const;
    int GetRemainingArrows() const;
    Direction GetDirection() const;
    const Square *GetSquare() const;
    void Draw() const;
};

#endif