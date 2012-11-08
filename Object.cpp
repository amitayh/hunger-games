#include "Object.h"
#include "Square.h"
#include "Game.h"

Object::Object() {
	square = NULL;
}

void Object::GotoPosition() {
	gotoxy(square->GetCol(), square->GetRow());
}

void Object::SetGame(Game* game) {
    this->game = game;
}

bool Object::Update() {
    return true;
};

bool Object::SetSquare(Square* square) {
    this->square = square;
    return true;
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