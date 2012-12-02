#include "Human.h"
#include "Game.h"

Human::Human(char name): Player(name) {}

void Human::update() {
    if (power > 0) {
        char key = pGame->getKey();
        ArrowsBag::Type arrowType;
        bool shoot = false;

        if (key >= 'A' && key <= 'Z') {
            // Convert to lowercase
            key -= ('A' - 'a');
        }

        // Check keyboard input
        switch (key) {
            case CHAR_LEFT:
                direction = LEFT;
                break;
            case CHAR_RIGHT:
                direction = RIGHT;
                break;
            case CHAR_UP:
                direction = UP;
                break;
            case CHAR_DOWN:
                direction = DOWN;
                break;
            case CHAR_SHOOT_REGULAR_ARROW:
                arrowType = ArrowsBag::REGULAR;
                shoot = true;
                break;
            case CHAR_SHOOT_EXPLODING_ARROW:
                arrowType = ArrowsBag::EXPLODING;
                shoot = true;
                break;
            case CHAR_SHOOT_PENETRATING_ARROW:
                arrowType = ArrowsBag::PENETRATING;
                shoot = true;
                break;
        }

        Grid::Square* square = &getNextSquare();
        if (pGame->getTick() % MOVE_INTERVAL == 0 && !square->hasWall()) {
            // Move to next square
            setSquare(*square);
        }

        if (shoot) {
            shootArrow(arrowType);
        }
    }
}