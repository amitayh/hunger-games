#ifndef _DIMENSIONS_H
#define _DIMENSIONS_H

class Dimensions
{
    int width, height;

public:
    Dimensions(int width = 1, int height = 1);

    void SetWidth(int width);
    void SetHeight(int height);
    int GetWidth();
    int GetHeight();
};

#endif