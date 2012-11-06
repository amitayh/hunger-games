#include "Player.h"
#include "Game.h"

Player::Player(char name, int power) {
    SetType(PLAYER);
	this->name = name;
    this->power = power;
    remainingArrows = INITIAL_NUM_ARROWS;
    lastArrowTick = 0;
}

bool Player::SetSquare(Square* square) {
	if (square->IsOccupied()) {
		ObjectsList* objects = square->GetObjects();
        ObjectsList::iterator iterator;
		Object* object;
		ObjectType type;
		for (iterator = objects->begin(); iterator != objects->end(); iterator++) {
			object = *iterator;
			type = object->GetType();
			if (type == BOMB || type == FOOD || type == QUIVER) {
			} else if (type == WALL) {
			}
        }
	}
	return MovingObject::SetSquare(square);

	/*
    if (square->IsWall()) {
		SetRandomDirection();
        return false;
    }
    return MovingObject::SetSquare(square);
	*/
}

void Player::Update() {
    int random = rand() % 100;
    if (random < CHANGE_DIRECTION_PROBABILITY) {
        // 10% chance of changing direction randomly
        SetRandomDirection();
    }

    Game* game = GetGame();
    int tick = game->GetTick();
    random = rand() % 100;
    if (random < ARROW_PROBABILITY && tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS) {
        ShootArrow();
    }

    MovingObject::Update();
}

void Player::SetRandomDirection() {
    Direction directions[2], newDirection;
    switch (GetDirection()) {
        case UP:
        case DOWN:
            directions[0] = LEFT;
            directions[1] = RIGHT;
            break;
        case LEFT:
        case RIGHT:
            directions[0] = UP;
            directions[1] = DOWN;
            break;
    }
    newDirection = directions[rand() % 2];
    SetDirection(newDirection);
}

void Player::ShootArrow() {
	if (remainingArrows) {
        Arrow* arrow = new Arrow(this);
        Game* game = GetGame();
        game->Add(arrow);
		remainingArrows--;
	}
}

void Player::Draw() {
	GotoPosition();
	cout << name;
}