#ifndef _SQUARE_H
#define _SQUARE_H

#include <list>

class Object;

typedef std::list<Object*> ObjectsList;

class Square
{
    int row, col;
    ObjectsList objects;
public:
    void Enter(Object* object);
    void Leave(Object* object);
    void Set(int row, int col);
    void SetRow(int row);
    void SetCol(int col);
    int GetRow();
    int GetCol();
    ObjectsList* GetObjects();
    bool IsOccupied();
    bool IsWall();
};

#endif