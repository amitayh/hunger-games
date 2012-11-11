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

Player::~Player() {
    Square* square = GetSquare();
    if (square) {
        square->StepOut(this);
    }
}

void Player::SetSquare(Square* square) {
    if (square->GetWall()) {
        SetRandomDirection();
        Update();
    } else {
        DroppingObject* droppingObject = square->GetDroppingObject();
        if (droppingObject) {
            // Pick up dropping object
            droppingObject->Affect(this);
        }

        Square* prevSquare = GetSquare();
        if (prevSquare) {
            prevSquare->StepOut(this);
        }
        square->StepIn(this);

        MovingObject::SetSquare(square);
    }
}

void Player::Update() {
    MovingObject::Update();

    Game* game = GetGame();

    // Randomly change direction
    if (game->CheckProbability(CHANGE_DIRECTION_PROBABILITY)) {
        SetRandomDirection();
    }

    // Randomly shoot arrows
    unsigned int tick = game->GetTick();
    if (game->CheckProbability(SHOOT_ARROW_PROBABILITY) && tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS) {
        ShootArrow();
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

char Player::GetName() {
    return name;
}

int Player::GetPower() {
    return power;
}

int Player::GetRemainingArrows() {
    return remainingArrows;
}

void Player::SetRandomDirection() {
    Direction directions[2], direction;
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
    direction = directions[rand() % 2];
    SetDirection(direction);
}

bool Player::ShootArrow() {
    if (remainingArrows) {
        Square* square = GetNextSquare();
        if (!square->GetWall()) {
            Game* game = GetGame();
            Arrow* arrow = new Arrow;
            arrow->SetDirection(GetDirection());
            game->AddArrow(arrow, square);
            lastArrowTick = game->GetTick();
            remainingArrows--;
            return true;
        }
    }
    return false;
}

void Player::Draw() {
    GotoPosition();
    ChangeColor(Color::CYAN);
    cout << name;
}