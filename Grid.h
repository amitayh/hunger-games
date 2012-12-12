#ifndef _GRID_H
#define _GRID_H

#include "Console.h"
#include <list>

using namespace std;

const double PI = 3.141592653589793;

// Pseudo declarations to enable compilation
class Object;
class Player;
class DroppingObject;
class Wall;
enum Direction;
typedef list<Object*> ObjectsList;
typedef ObjectsList::iterator ObjectsIterator;

class Grid
{
public:
    enum {
        DEFAULT_NUM_ROWS = 24,
        DEFAULT_NUM_COLS = 79
    };

    class Square
    {
        int row, col;
        ObjectsList players;
        DroppingObject* pDroppingObject;
        Wall* pWall;

    public:
        Square();

        void stepIn(Player& player);
        void stepOut(Player& player);
        void initPosition(int row, int col);
        void setDroppingObject(DroppingObject& droppingObject);
        void unsetDroppingObject();
        void setWall(Wall& wall);
        void unsetWall();
        ObjectsList& getPlayers();

        void clear() const;
        void draw(char ch, Color color = SILVER) const;
        double getDistance(const Square& otherSquare) const;
        Direction getDirection(const Square& otherSquare) const;
        DroppingObject& getDroppingObject() const;
        Wall& getWall() const;
        bool hasDroppingObject() const;
        bool hasWall() const;
        bool isEmpty() const;
        int getRow() const;
        int getCol() const;
    };

    Grid(int rows = DEFAULT_NUM_ROWS, int cols = DEFAULT_NUM_COLS);
    ~Grid();
    
    Grid::Square& getSquare(int row, int col) const;
    Grid::Square& getRandomSquare() const;
    int getRows() const;
    int getCols() const;

private:
    int rows, cols;
    Grid::Square** squares;
};

#endif