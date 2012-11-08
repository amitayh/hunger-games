#include "Player.h"
#include "Arrow.h"
#include "Game.h"
#include "DroppingObject.h"

Player::Player(char name, int power) {
	this->name = name;
    this->power = power;
    remainingArrows = INITIAL_NUM_ARROWS;
    lastArrowTick = 0;
	SetMoveInterval(2);
}

void Player::SetSquare(Square* square) {
    if (square->GetWall()) {
        SetRandomDirection();
		Update();
    } else {
		DroppingObject* droppingObject = square->GetDroppingObject();
        if (droppingObject) {
            droppingObject->Affect(this);
        }

		Square* previousSquare = GetSquare();
		if (previousSquare) {
			previousSquare->StepOut(this);
		}
		square->StepIn(this);
		MovingObject::SetSquare(square);
    }
}

void Player::AddArrows(int amount) {
	remainingArrows += amount;
}

void Player::IncreasePower(int amount) {
    power = __max(power + amount, 0);
}

void Player::DecreasePower(int amount) {
    IncreasePower(-amount);
}

int Player::GetPower() {
    return power;
}

bool Player::Update() {
	MovingObject::Update();

	// Randomly change direction
    int random = rand() % 100;
    if (random < CHANGE_DIRECTION_PROBABILITY) {
        SetRandomDirection();
    }

	// Randomly shoot arrows
    Game* game = GetGame();
    int tick = game->GetTick();
	random = rand() % 100;
    if (random < SHOOT_ARROW_PROBABILITY && tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS) {
        ShootArrow();
    }

    return (power > 0);
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

bool Player::ShootArrow() {
	if (remainingArrows) {
        Square* square = GetNextSquare();
		if (!square->GetWall()) {
			Game* game = GetGame();
			Arrow* arrow = new Arrow;
			arrow->SetDirection(GetDirection());
            game->AddObject(arrow, square);
            lastArrowTick = game->GetTick();
		    remainingArrows--;
			return true;
        }
	}
	return false;
}

void Player::Draw() {
	GotoPosition();
	
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hConsole, 10);

	cout << name;

	//SetConsoleTextAttribute(hConsole, 7);
}