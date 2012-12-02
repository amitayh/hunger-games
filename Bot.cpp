#include "Bot.h"
#include "Game.h"

Bot::Bot(char name): Player(name) {}

void Bot::update() {
    if (power > 0) {
        if (pGame->getTick() % MOVE_INTERVAL == 0) {
            // Move to next square
            setSquare(getNextMove());
        }

        if (
            !arrowsBag.isEmpty() &&                             // Player still has arrows
            pGame->checkProbability(SHOOT_ARROW_PROBABILITY) && // Check probability, don't shoot on every chance
            hasPlayersInRange()                                 // Shoot only if there is a reasonable chance of hitting an opponent
        ) {
            // Shoot an arrow if conditions are met
            shootArrow();
        }
    }
}