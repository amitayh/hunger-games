#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Arrow: public MovingObject
{
public:
    ~Arrow();

    void setSquare(Grid::Square& square);
    void update();

    bool getHit() const;

protected:
    enum {
        MOVE_INTERVAL = 1
    };

    Arrow(); // Make the class abstract

    bool hit;

    virtual bool checkHit();
};

#endif