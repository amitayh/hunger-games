#include "Square.h"
#include "Object.h"

void Square::Enter(Object* object) {
    objects.push_back(object);
}

void Square::Leave(Object* object) {
    objects.remove(object);
}

void Square::Set(int row, int col) {
    SetRow(row);
    SetCol(col);
}

void Square::SetRow(int row) {
    this->row = row;
}

void Square::SetCol(int col) {
    this->col = col;
}

int Square::GetRow() {
    return row;
}

int Square::GetCol() {
    return col;
}

ObjectsList* Square::GetObjects() {
    return &objects;
}

bool Square::IsOccupied() {
    return (objects.size() > 0);
}

bool Square::IsWall() {
    if (IsOccupied()) {
        Object* object = objects.front();
        return (object->GetType() == WALL);
    }
    return false;
}