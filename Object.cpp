#include "Object.h"
#include "Square.h"
#include "Game.h"

Object::Object() {
	square = NULL;
}

void Object::GotoPosition() {
	gotoxy(square->GetCol(), square->GetRow());
}

void Object::SetType(ObjectType type) {
    this->type = type;
}

void Object::SetGame(Game* game) {
    this->game = game;
}

bool Object::SetSquare(Square* square) {
    this->square = square;
    return true;
}

ObjectType Object::GetType() {
    return type;
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