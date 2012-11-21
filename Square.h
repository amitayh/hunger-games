#ifndef _SQUARE_H
#define _SQUARE_H

#include "List.h"
#include "Console.h"

const double PI = 3.141592653589793;

class Player;
class DroppingObject;
class Wall;
enum Direction;

class Square
{
    int row, col;
    List players;
    DroppingObject *droppingObject;
    Wall *wall;

public:
    Square();

    void StepIn(Player &player);
    void StepOut(Player &player);
    void InitPosition(int row, int col);
    void SetDroppingObject(DroppingObject &droppingObject);
    void UnsetDroppingObject();
    bool HasDroppingObject();
    void SetWall(Wall &wall);
    List &GetPlayers();
    DroppingObject &GetDroppingObject();
    bool HasWall();

    void Clear() const;
    void Draw(char ch, Color color = SILVER) const;
    double GetDistance(const Square &otherSquare) const;
    Direction GetDirection(const Square &otherSquare) const;
    bool IsEmpty() const;
    int GetRow() const;
    int GetCol() const;
};

#endif