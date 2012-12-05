#ifndef _OBJECT_H
#define _OBJECT_H

#include "Grid.h"

class Game;

class Object
{
public:
    Object();

    void setGame(Game& game);
    virtual void setSquare(Grid::Square& square);
    
    virtual void draw() const = 0;
    Grid::Square& getSquare() const;

protected:
    Game* pGame;
    Grid::Square *pSquare;
};

#endif