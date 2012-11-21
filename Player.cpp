#include "Player.h"
#include "Game.h"
#include "DroppingObject.h"

Player::Player(char name, Square &square, int power, Direction direction) {
    this->direction = direction;
    this->name = name;
    this->power = power;
    pSquare = &square;
    square.StepIn(*this);
    remainingArrows = INITIAL_NUM_ARROWS;
    lastArrowTick = 0;
}

Player::~Player() {
    StepOut();
}

void Player::SetSquare(Square &square) {
    if (square.HasDroppingObject()) {
        DroppingObject &droppingObject = square.GetDroppingObject();
        // Pick up dropping object
        droppingObject.Affect(*this);
    }

    List &players = square.GetPlayers();
    if (!players.IsEmpty()) {
        ListIterator it(players);
        while (power > 0 && !it.Done()) {
            ListNode *node = it.Current();
            Player *player = (Player *) node->GetData();
            Fight(*player);
        }
    }

    StepOut();
    square.StepIn(*this);
    pSquare = &square;
}

void Player::StepOut() {
    if (pSquare) {
        pSquare->Clear();
        pSquare->StepOut(*this);
    }
}

void Player::Update(Game &game) {
    if (power > 0) {
        unsigned int tick = game.GetTick();

        // Move
        if (tick % MOVE_INTERVAL == 0) {
            SetSquare(GetNextMove(game));
        }

        // Shoot arrows
        if (
            remainingArrows &&
            game.CheckProbability(SHOOT_ARROW_PROBABILITY) &&
            tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS &&
            HasPlayersInRange(game.GetPlayers())
        ) {
            ShootArrow(game);
        }
    }
}

Square &Player::GetNextMove(Game &game) {
    Grid &grid = game.GetGrid();

    // Find closest food / quiver
    DroppingObject *closest = FindClosestObject(game.GetDroppingObjects());
    if (closest && CheckWallsInPath(grid, closest->GetSquare())) {
        direction = pSquare->GetDirection(closest->GetSquare());
    } else if (game.CheckProbability(CHANGE_DIRECTION_PROBABILITY)) {
        // Randomly change direction
        SetRandomDirection();
    }

    Square *nextSquare = &GetNextSquare(grid, *pSquare, direction);
    while (nextSquare->HasWall()) {
        // Change direction to avoid the wall
        SetRandomDirection();
        nextSquare = &GetNextSquare(grid, *pSquare, direction);
    }

    return *nextSquare;
}

DroppingObject *Player::FindClosestObject(List &objects) const {
    DroppingObject *closest = NULL;
    if (!objects.IsEmpty()) {
        double closestDistance = 0, distance;
        DroppingObject *current;
        ListIterator it(objects);
        while (!it.Done()) {
            current = (DroppingObject *) it.Current()->GetData();
            if (current->GetType() != DroppingObject::Type::BOMB) {
                distance = pSquare->GetDistance(current->GetSquare());
                if (!closest || distance < closestDistance) {
                    // Found a closer food / quiver
                    closestDistance = distance;
                    closest = current;
                }
            }
        }
    }
    return closest;
}

bool Player::CheckWallsInPath(Grid &grid, const Square &target) const {
    Square *current = pSquare;
    while (current != &target) {
        Direction direction = current->GetDirection(target);
        current = &GetNextSquare(grid, *current, direction);
        if (current->HasWall()) {
            // Found a wall, no need to continue
            return false;
        }
    }
    // The path is clear!
    return true;
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

void Player::ShootArrow(Game &game) {
    Square &arrowSquare = GetNextSquare(game.GetGrid(), *pSquare, direction);
    if (!arrowSquare.HasWall()) {
        Arrow *arrow = new Arrow(*this, arrowSquare);
        game.AddArrow(*arrow);
        lastArrowTick = game.GetTick();
        remainingArrows--;
    }
}

bool Player::HasPlayersInRange(List &players) const {
    ListIterator it(players);
    bool inRange = false;
    while (!inRange && !it.Done()) {
        Player *player = (Player *) it.Current()->GetData();
        if (player != this) {
            inRange = PlayerInRange(*player);
        }
    }
    return inRange;
}

bool Player::PlayerInRange(Player &oponent) const {
    const Square &oponentSquare = oponent.GetSquare();
    Direction oponentDirection = oponent.GetDirection();

    // Yuck
    if (
        (direction == RIGHT && pSquare->GetCol() < oponentSquare.GetCol()) ||
        (direction == LEFT && pSquare->GetCol() > oponentSquare.GetCol())
    ) {
        if (oponentDirection == DOWN) {
            return (pSquare->GetRow() > oponentSquare.GetRow());
        } else if (oponentDirection == UP) {
            return (pSquare->GetRow() < oponentSquare.GetRow());
        } else {
            return (pSquare->GetRow() == oponentSquare.GetRow());
        }      
    } else if (
        (direction == DOWN && pSquare->GetRow() < oponentSquare.GetRow()) ||
        (direction == UP && pSquare->GetRow() > oponentSquare.GetRow())
    ) {
        if (oponentDirection == RIGHT) {
            return (pSquare->GetCol() > oponentSquare.GetCol());
        } else if (oponentDirection == LEFT) {
            return (pSquare->GetCol() < oponentSquare.GetCol());
        } else {
            return (pSquare->GetCol() == oponentSquare.GetCol());
        }
    }

    return false;
}

void Player::Fight(Player &oponent) {
    if (power > oponent.GetPower()) {
        // Player is stronger than oponent
        oponent.DecreasePower(200);
        DecreasePower(10);
    } else if (power < oponent.GetPower()) {
        // Player is weaker than oponent
        oponent.DecreasePower(10);
        DecreasePower(200);
    } else {
        // Player and oponent are equal
        oponent.DecreasePower(50);
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

const Square &Player::GetSquare() const {
    return *pSquare;
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

void Player::Draw() const {
    pSquare->Draw(name, CYAN);
}