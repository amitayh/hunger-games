#ifndef _BOT_H
#define _BOT_H

#include "BasePlayer.h"

class Bot: public BasePlayer
{
    void setRandomDirection();
    Grid::Square& getNextMove();

    DroppingObject* findClosestObject() const;
    bool isClearPath(const Grid::Square& target) const;
    bool hasPlayersInRange() const;
    bool playerInRange(const BasePlayer& opponent) const;

public:
    Bot(char name);

    virtual void update();
};

#endif