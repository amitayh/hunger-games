#include "Object.h"
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
    if (GetSquare()) {
        GotoPosition();
        cout << ' ';
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