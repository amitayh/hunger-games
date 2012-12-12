#include "Human.h"
#include "Game.h"

Human::Human(): Player(DISPLAY_NAME) {}

void Human::update() {
    if (power > 0) {
        char key = pGame->getKey();
        ArrowsBag::Type arrowType;
        bool shoot = false;

        if (key >= 'a' && key <= 'z') {
            // Convert to uppercase
            key += ('A' - 'a');
        }

        // Check keyboard input
        switch (key) {
            case KEY_LEFT:
                direction = LEFT;
                break;
            case KEY_RIGHT:
                direction = RIGHT;
                break;
            case KEY_UP:
                direction = UP;
                break;
            case KEY_DOWN:
                direction = DOWN;
                break;
            case KEY_SHOOT_REGULAR_ARROW:
                arrowType = ArrowsBag::REGULAR;
                shoot = true;
                break;
            case KEY_SHOOT_EXPLODING_ARROW:
                arrowType = ArrowsBag::EXPLODING;
                shoot = true;
                break;
            case KEY_SHOOT_PENETRATING_ARROW:
                arrowType = ArrowsBag::PENETRATING;
                shoot = true;
                break;
        }

        Grid::Square& square = getNextSquare();
        if (pGame->getTick() % MOVE_INTERVAL == 0 && !square.hasWall()) {
            // Move to next square
            setSquare(square);
        }

        if (shoot) {
            shootArrow(arrowType);
        }
    }
}

void Human::draw() const {
    pSquare->draw(name, Console::MAGENTA);
}