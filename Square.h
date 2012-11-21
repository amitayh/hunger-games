#ifndef _SQUARE_H
#define _SQUARE_H

#include "List.h"
#include "Console.h"

const double PI = 3.141592653589793;

// Pseudo declarations to allow compilation
class Player;
class DroppingObject;
class Wall;
enum Direction;

class Square
{
    int row, col;
    List players;
    DroppingObject* pDroppingObject;
    Wall* pWall;

public:
    Square();

    void stepIn(const Player& player);
    void stepOut(const Player& player);
    void initPosition(int row, int col);
    void setDroppingObject(DroppingObject& droppingObject);
    void unsetDroppingObject();
    void setWall(Wall& wall);

    void clear() const;
    void draw(char ch, Color color = SILVER) const;
    double getDistance(const Square& otherSquare) const;
    Direction getDirection(const Square& otherSquare) const;
    DroppingObject& getDroppingObject() const;
    const List& getPlayers() const;
    bool hasDroppingObject() const;
    bool hasWall() const;
    bool isEmpty() const;
    int getRow() const;
    int getCol() const;
};

#endif