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
    DroppingObject *pDroppingObject;
    Wall *pWall;

public:
    Square();

    void StepIn(const Player &player);
    void StepOut(const Player &player);
    void InitPosition(int row, int col);
    void SetDroppingObject(DroppingObject &droppingObject);
    void UnsetDroppingObject();
    void SetWall(Wall &wall);

    void Clear() const;
    void Draw(char ch, Color color = SILVER) const;
    double GetDistance(const Square &otherSquare) const;
    Direction GetDirection(const Square &otherSquare) const;
    DroppingObject &GetDroppingObject() const;
    const List &GetPlayers() const;
    bool HasDroppingObject() const;
    bool HasWall() const;
    bool IsEmpty() const;
    int GetRow() const;
    int GetCol() const;
};

#endif