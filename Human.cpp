#include "Human.h"
#include "Game.h"
#include <conio.h>

Human::Human(char name): Player(name) {}

void Human::update() {
    if (power > 0) {
        unsigned int tick = pGame->getTick();

        if (kbhit()) {
            int key = getch();
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
            }
        }

        if (tick % MOVE_INTERVAL == 0) {
            // Move to next square
            setSquare(getNextSquare());
        }

        /*
        if (
            !arrowsBag.isEmpty() &&                             // Player still has arrows
            pGame->checkProbability(SHOOT_ARROW_PROBABILITY) && // Check probability, don't shoot on every chance
            tick > lastArrowTick + MIN_TICKS_BETWEEN_ARROWS &&  // Check minimum ticks between arrows
            hasPlayersInRange()                                 // Shoot only if there is a reasonable chance of hitting an opponent
        ) {
            // Shoot an arrow if conditions are met
            shootArrow();
        }
        */
    }
}