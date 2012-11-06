#include "MovingObject.h"
#include "Game.h"

MovingObject::MovingObject() {
	direction = RIGHT;
    speed = 1;
}

void MovingObject::UpdatePosition(int& start, int end) {
    if (start < end) {
        start++;
    } else if (start > end) {
        start--;
    }
}

void MovingObject::Update() {
    Square* currentSquare = GetSquare();
	int currentRow = currentSquare->GetRow(),
		currentCol = currentSquare->GetCol(),
		newRow = currentRow,
		newCol = currentCol;

    switch (direction) {
        case UP:
			newRow -= speed;
            break;
        case DOWN:
            newRow += speed;
            break;
        case LEFT:
            newCol -= speed;
            break;
        case RIGHT:
            newCol += speed;
            break;
    }

    Game* game = GetGame();
    Grid* grid = game->GetGrid();
    while (currentRow != newRow || currentCol != newCol) {
        UpdatePosition(currentRow, newRow);
        UpdatePosition(currentCol, newCol);
        currentSquare = grid->GetSquare(currentRow, currentCol);
        if (!SetSquare(currentSquare)) {
            break;
        }
    }
}

Direction MovingObject::GetDirection() {
    return direction;
}

void MovingObject::SetDirection(Direction direction) {
    this->direction = direction;
}

void MovingObject::SetSpeed(int speed) {
    this->speed = speed;
}