#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Arrow : public MovingObject
{
public:
    ~Arrow();

    void setSquare(Grid::Square& square);
    void update();

    void draw() const;
    bool getHit() const;

protected:
    enum {
        MOVE_INTERVAL = 1
    };

    Arrow(); // Make the class abstract

    Color color;
    bool hit;

    virtual bool checkHit();
};

#endif