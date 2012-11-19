#include "Player.h"
#include "Game.h"
#include "DroppingObject.h"

Player::Player(char name, int power, Direction direction) {
    this->direction = direction;
    this->name = name;
    this->power = power;
    square = NULL;
    remainingArrows = INITIAL_NUM_ARROWS;
    lastArrowTick = 0;
}

Player::~Player() {
    StepOut();
}

void Player::SetSquare(Square* square) {
    DroppingObject* droppingObject = square->GetDroppingObject();
    if (droppingObject) {
        // Pick up dropping object
        droppingObject->Affect(this);
    }

    List* players = square->GetPlayers();
    if (!players->IsEmpty()) {
        ListIterator it(players);
        while (power > 0 && !it.Done()) {
            ListNode* node = it.Current();
            Player* player = (Player*) node->GetData();
            Fight(player);
        }
    }

    StepOut();
    square->StepIn(this);
    this->square = square;
}

void Player::StepOut() {
    if (square) {
        square->Clear();
        square->StepOut(this);
    }
}

void Player::Update(Game* game) {
    if (power > 0) {
        unsigned int tick = game->GetTick();
        Grid* grid = game->GetGrid();

        // Move
        if (tick % MOVE_INTERVAL == 0) {
            Square* nextSquare = GetNextSquare(grid, square, direction);
            while (nextSquare->GetWall()) {
                // Change direction to avoid the wall
                SetRandomDirection();
                nextSquare = GetNextSquare(grid, square, direction);
            }
            square->Clear();
            SetSquare(nextSquare);
        }

        // Randomly change direction
        if (game->CheckProbability(CHANGE_DIRECTION_PROBABILITY)) {
            SetRandomDirection();
        }

        // Randomly shoot arrows
        if (remainingArrows && game->CheckProbability(SHOOT_ARROW_PROBABILITY) && tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS) {
            ShootArrow(game);
        }
    }
}

void Player::ShootArrow(Game* game) {
    Grid* grid = game->GetGrid();
    Square* arrowSquare = GetNextSquare(grid, square, direction);
    if (!arrowSquare->GetWall()) {
        Arrow* arrow = new Arrow(this);
        game->AddArrow(arrow, arrowSquare);
        lastArrowTick = game->GetTick();
        remainingArrows--;
    }
}

void Player::Fight(Player* oponent) {
    if (power > oponent->GetPower()) {
        // Player is stronger than oponent
        oponent->DecreasePower(200);
        DecreasePower(10);
    } else if (power < oponent->GetPower()) {
        // Player is weaker than oponent
        oponent->DecreasePower(10);
        DecreasePower(200);
    } else {
        // Player and oponent are equal
        oponent->DecreasePower(50);
        DecreasePower(50);
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

const Square* Player::GetSquare() const {
    return square;
}

char Player::GetName() const {
    return name;
}

int Player::GetPower() const {
    return power;
}

int Player::GetRemainingArrows() const {
    return remainingArrows;
}

Direction Player::GetDirection() const {
    return direction;
}

void Player::SetRandomDirection() {
    Direction directions[2];
    switch (direction) {
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
}

void Player::Draw() const {
    square->Draw(name, CYAN);
}