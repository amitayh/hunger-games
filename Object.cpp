#include "Object.h"
#include "DroppingObject.h"
#include "Square.h"
#include "Game.h"

Object::Object() {
    square = NULL;
}

Object::~Object() {
    Clear();
}

void Object::GotoPosition() {
    gotoxy(square->GetCol(), square->GetRow());
}

void Object::SetGame(Game* game) {
    this->game = game;
}

void Object::SetSquare(Square* square) {
    this->square = square;
}

void Object::Clear() {
    if (square) {
        DroppingObject* droppingObject = square->GetDroppingObject();
        if (droppingObject) {
            // Redraw dropping object
            droppingObject->Draw();
        } else {
            // Clear square
            GotoPosition();
            cout << ' ';
        }
    }
}

Dimensions* Object::GetSize() {
    return &size;
}

Game* Object::GetGame() {
    return game;
}

Square* Object::GetSquare() {
    return square;
}

bool Object::InArea(Square* square) {
    int row = square->GetRow(),
        col = square->GetCol(),
        rowMin = this->square->GetRow(),
        rowMax = rowMin + size.GetHeight(),
        colMin = this->square->GetCol(),
        colMax = colMin + size.GetWidth();

    return (row >= rowMin && row <= rowMax && col >= colMin && col <= colMax);
}