#include "Dimensions.h"

Dimensions::Dimensions() {
	width = height = 1;
}

void Dimensions::Set(int width, int height) {
    SetWidth(width);
    SetHeight(height);
}

void Dimensions::SetWidth(int width) {
    this->width = width;
}

void Dimensions::SetHeight(int height) {
    this->height = height;
}

int Dimensions::GetWidth() {
    return width;
}

int Dimensions::GetHeight() {
    return height;
}