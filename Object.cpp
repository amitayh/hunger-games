#include "Object.h"
#include "Square.h"
#include "Game.h"

Object::Object() {
	square = NULL;
}

Object::~Object() {
    if (square) {
        square->Leave(this);
    }
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
	if (this->square) {
		this->square->Leave(this);
	}
    this->square = square;
	square->Enter(this);
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