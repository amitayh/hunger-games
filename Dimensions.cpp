#include "Dimensions.h"

Dimensions::Dimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

int Dimensions::getWidth() const {
    return width;
}

int Dimensions::getHeight() const {
    return height;
}