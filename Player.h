#ifndef _PLAYER_H
#define _PLAYER_H

#include "MovingObject.h"

class Game;

class Player
{
    enum {
        INITIAL_POWER                   = 1000,
        INITIAL_NUM_ARROWS              = 4,
        MIN_TICKS_BETWEEN_ARROWS        = 3,
        SHOOT_ARROW_PROBABILITY         = 20,
        CHANGE_DIRECTION_PROBABILITY    = 10,
        MOVE_INTERVAL                   = 2
    };

    Square *pSquare;
    Direction direction;
    char name;
    int power;
    int remainingArrows;
    unsigned int lastArrowTick;

    void SetSquare(Square &square);
    void Fight(Player &opponent);
    void SetRandomDirection();
    void ShootArrow(Game &game);
    Square &GetNextMove(Game &game);

    DroppingObject *FindClosestObject(const List &objects) const;
    bool CheckWallsInPath(const Grid &grid, const Square &target) const;
    bool HasPlayersInRange(const List &players) const;
    bool PlayerInRange(const Player &opponent) const;
    void StepOut() const;

public:
    Player(char name, Square &square, int power = INITIAL_POWER, Direction direction = RIGHT);
    ~Player();

    void Update(Game &game);
    void IncreasePower(int amount);
    void DecreasePower(int amount);
    void AddArrows(int amount);

    char GetName() const;
    int GetPower() const;
    int GetRemainingArrows() const;
    Direction GetDirection() const;
    const Square &GetSquare() const;
    void Draw() const;
};

#endif