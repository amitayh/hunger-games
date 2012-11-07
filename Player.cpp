#include "Player.h"
#include "Arrow.h"
#include "Game.h"
#include "DroppingObject.h"

Player::Player(char name, int power) {
    SetType(PLAYER);
	this->name = name;
    this->power = power;
    remainingArrows = INITIAL_NUM_ARROWS;
    lastArrowTick = 0;
}

bool Player::SetSquare(Square* square) {
    if (square->GetWall()) {
        SetRandomDirection();
        return false;
    } else {
        DroppingObject* droppingObject = square->GetDroppingObject();
        if (droppingObject) {
            Game* game = GetGame();
            droppingObject->Affect(this);
            square->SetDroppingObject(NULL);
            game->RemoveObject(droppingObject);
        }
        // TODO: check power

        PlayersList* players = square->GetPlayers();
        PlayersListIterator it = players->begin();
        while (it != players->end()) {
            Battle(*it);
            it++;
        }
    }
    return MovingObject::SetSquare(square);
}

void Player::Battle(Player* otherPlayer) {
    int otherPlayerPower = otherPlayer->GetPower();
    if (power > otherPlayerPower) {
        otherPlayer->DecreasePower(200);
        DecreasePower(10);
    } else if (power < otherPlayerPower) {
        otherPlayer->DecreasePower(10);
        DecreasePower(200);
    } else {
        otherPlayer->DecreasePower(50);
        DecreasePower(50);
    }
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

    if (!power) {
        game->RemoveObject(this);
    }
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
        Square* square = GetSquare();
        int row = square->GetRow(), col = square->GetCol();

        switch (GetDirection()) {
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
        game->AddObject(arrow, row, col);
		remainingArrows--;
	}
}

void Player::Draw() {
	GotoPosition();
	cout << name;
}