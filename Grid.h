#ifndef _GRID_H
#define _GRID_H

#include "Console.h"
#include <list>

using namespace std;

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
    static const int DEFAULT_NUM_ROWS;
    static const int DEFAULT_NUM_COLS;

    class Square
    {
        static const double PI;

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
        void draw(char ch, Console::Color color = Console::SILVER) const;
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