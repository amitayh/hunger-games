#include "Dimensions.h"

Dimensions::Dimensions(int width, int height) {
    this->width = width;
    this->height = height;
}

int Dimensions::GetWidth() const {
    return width;
}

int Dimensions::GetHeight() const {
    return height;
}