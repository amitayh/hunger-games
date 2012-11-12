#include "Wall.h"
#include "Square.h"

Wall::~Wall() {
    Square* square = GetSquare();
    if (square) {
        square->SetWall(NULL);
    }
}

void Wall::Draw() {
    GotoPosition();
    ChangeColor(GREY);
    cout << '#';
}

void Wall::SetSquare(Square* square) {
    square->SetWall(this);
    Object::SetSquare(square);
}