#ifndef _BOT_H
#define _BOT_H

#include "Player.h"

class Bot : public Player
{
    void setRandomDirection();
    Grid::Square& getNextMove();

    DroppingObject* findClosestObject() const;
    bool isClearPath(const Grid::Square& target) const;
    bool hasPlayersInRange() const;
    bool playerInRange(const Player& opponent) const;

public:
    Bot(char name);

    void update();
};

#endif