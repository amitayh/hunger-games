#ifndef _DIMENSIONS_H
#define _DIMENSIONS_H

class Dimensions
{
	int width, height;
public:
	Dimensions();

    void Set(int width, int height);
    void SetWidth(int width);
    void SetHeight(int height);
    int GetWidth();
    int GetHeight();
};

#endif