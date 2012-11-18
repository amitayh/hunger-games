#ifndef _SQUARE_H
#define _SQUARE_H

#include "List.h"

class Player;
class DroppingObject;
class Wall;

class Square
{
    int row, col;
    List players;
    DroppingObject* droppingObject;
    Wall* wall;

public:
    Square();

    void StepIn(Player* player);
    void StepOut(Player* player);
    void SetPosition(int row, int col);
    void SetDroppingObject(DroppingObject* droppingObject);
    void SetWall(Wall* wall);
    int GetRow();
    int GetCol();
    List* GetPlayers();
    DroppingObject* GetDroppingObject();
    Wall* GetWall();
    double GetDistance(Square* otherSquare);
    bool IsEmpty();
};

#endif