#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Arrow: public MovingObject
{
public:
    ~Arrow();

    virtual void setSquare(Grid::Square& square);
    virtual void update();

    bool getHit() const;

protected:
    static const int MOVE_INTERVAL;

    Arrow(); // Make the class abstract

    bool hit;

    virtual bool checkHit();
};

#endif