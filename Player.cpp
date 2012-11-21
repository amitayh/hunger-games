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
    // Clear square before deletion
    StepOut();
}

void Player::SetSquare(Square &square) {
    if (square.HasDroppingObject()) {
        // Pick up dropping object
        DroppingObject &droppingObject = square.GetDroppingObject();
        droppingObject.Affect(*this);
    }

    const List &players = square.GetPlayers();
    if (!players.IsEmpty()) {
        // Fight other players on square
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

void Player::StepOut() const {
    if (pSquare) {
        // Notify square that player is leaving
        pSquare->Clear();
        pSquare->StepOut(*this);
    }
}

void Player::Update(Game &game) {
    if (power > 0) {
        unsigned int tick = game.GetTick();

        if (tick % MOVE_INTERVAL == 0) {
            // Move to next square
            SetSquare(GetNextMove(game));
        }

        if (
            remainingArrows &&                                  // Player still has arrows
            game.CheckProbability(SHOOT_ARROW_PROBABILITY) &&   // Check probability, don't shoot on every chance
            tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS &&  // Check minimum ticks between arrows
            HasPlayersInRange(game.GetPlayers())                // Shoot only if there is a reasonable chance of hitting an opponent
        ) {
            // Shoot an arrow if conditions are met
            ShootArrow(game);
        }
    }
}

Square &Player::GetNextMove(Game &game) {
    const Grid &grid = game.GetGrid();

    // Find closest food / quiver
    DroppingObject *closest = FindClosestObject(game.GetDroppingObjects());
    if (closest && CheckWallsInPath(grid, closest->GetSquare())) {
        // Move towards the closest if it exists and the path is clear (no walls)
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

DroppingObject *Player::FindClosestObject(const List &objects) const {
    DroppingObject *closest = NULL;
    if (!objects.IsEmpty()) {
        double closestDistance = 0;
        ListIterator it(objects);
        while (!it.Done()) {
            // Iterate over the objects list
            ListNode *node = it.Current();
            DroppingObject *current = (DroppingObject *) node->GetData();
            if (current->GetType() != DroppingObject::Type::BOMB) {
                // Don't go for the bombs!
                double distance = pSquare->GetDistance(current->GetSquare());
                if (!closest || distance < closestDistance) {
                    // Found a closer food / quiver - update result
                    closestDistance = distance;
                    closest = current;
                }
            }
        }
    }
    return closest;
}

bool Player::CheckWallsInPath(const Grid &grid, const Square &target) const {
    Square *current = pSquare;
    while (current != &target) {
        // Simulate the actual movement and check for walls in the path
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
    // Set a direction randomly (player will only turn right or left)
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
        // Don't shoot directly at a wall
        Arrow *arrow = new Arrow(*this, arrowSquare);
        game.AddArrow(*arrow); // Update game
        lastArrowTick = game.GetTick();
        remainingArrows--;
    }
}

bool Player::HasPlayersInRange(const List &players) const {
    ListIterator it(players);
    bool inRange = false;
    while (!inRange && !it.Done()) {
        // Iterate over the players list
        ListNode *node = it.Current();
        Player *player = (Player *) node->GetData();
        if (player != this) {
            // Check if opponent may be hit if an arrow will be shot
            inRange = PlayerInRange(*player);
        }
    }
    return inRange;
}

bool Player::PlayerInRange(const Player &opponent) const {
    // Basic algorithm: check opponent's square and direction.
    // Compare with player's square and direction and decide whether or not to shoot
    const Square &opponentSquare = opponent.GetSquare();
    Direction opponentDirection = opponent.GetDirection();

    // Yuck, I know...
    if (
        (direction == RIGHT && pSquare->GetCol() < opponentSquare.GetCol()) ||
        (direction == LEFT && pSquare->GetCol() > opponentSquare.GetCol())
    ) {
        if (opponentDirection == DOWN) {
            return (pSquare->GetRow() > opponentSquare.GetRow());
        } else if (opponentDirection == UP) {
            return (pSquare->GetRow() < opponentSquare.GetRow());
        } else {
            return (pSquare->GetRow() == opponentSquare.GetRow());
        }      
    } else if (
        (direction == DOWN && pSquare->GetRow() < opponentSquare.GetRow()) ||
        (direction == UP && pSquare->GetRow() > opponentSquare.GetRow())
    ) {
        if (opponentDirection == RIGHT) {
            return (pSquare->GetCol() > opponentSquare.GetCol());
        } else if (opponentDirection == LEFT) {
            return (pSquare->GetCol() < opponentSquare.GetCol());
        } else {
            return (pSquare->GetCol() == opponentSquare.GetCol());
        }
    }

    return false;
}

void Player::Fight(Player &opponent) {
    if (power > opponent.GetPower()) {
        // Player is stronger than opponent
        opponent.DecreasePower(200);
        DecreasePower(10);
    } else if (power < opponent.GetPower()) {
        // Player is weaker than opponent
        opponent.DecreasePower(10);
        DecreasePower(200);
    } else {
        // Player and opponent are equal
        opponent.DecreasePower(50);
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