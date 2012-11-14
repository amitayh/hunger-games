#include "MovingObject.h"
#include "Game.h"

MovingObject::MovingObject() {
    direction = RIGHT;
}

void MovingObject::Update() {
    Game* game = GetGame();
    if (game->GetTick() % moveInterval == 0) {
        Clear();
        SetSquare(GetNextSquare());
    }
}

MovingObject::Direction MovingObject::GetDirection() {
    return direction;
}

void MovingObject::SetDirection(Direction direction) {
    this->direction = direction;
}

void MovingObject::SetMoveInterval(int moveInterval) {
    this->moveInterval = moveInterval;
}

Square* MovingObject::GetNextSquare() {
    Square* square = GetSquare();
    int row = square->GetRow(),
        col = square->GetCol();

    switch (direction) {
        case UP:
            row--;
            break;
        case DOWN:
            row++;
            break;
        case LEFT:
            col--;
            break;
        case RIGHT:
            col++;
            break;
    }

    Game* game = GetGame();
    Grid* grid = game->GetGrid();
    return grid->GetSquare(row, col);
}