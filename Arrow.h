#ifndef _ARROW_H
#define _ARROW_H

#include "MovingObject.h"

class Arrow : public MovingObject
{
public:
    Arrow(Player& shooter);
    ~Arrow();

    void setSquare(Grid::Square& square);
    void update();

    void draw() const;
    bool getHit() const;

protected:
    enum {
        MOVE_INTERVAL = 1
    };

    Color color;
    bool hit;

    virtual bool checkHit();
};

#endif