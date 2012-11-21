#ifndef _DIMENSIONS_H
#define _DIMENSIONS_H

class Dimensions
{
    int width, height;

public:
    Dimensions(int width, int height);

    int getWidth() const;
    int getHeight() const;
};

#endif