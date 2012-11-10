#include "Wall.h"
#include "Square.h"

void Wall::Draw() {
    GotoPosition();
    ChangeColor(Color::GREY);
    cout << '#';
}

void Wall::SetSquare(Square* square) {
    square->SetWall(this);
    Object::SetSquare(square);
}