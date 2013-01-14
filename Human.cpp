#include "Human.h"
#include "Common.h"
#include "Game.h"
#include <exception>

using namespace HungerGames;

int HumanPlayer::numInstances = 0;

HumanPlayer::HumanPlayer(char name, Console::Color color): BasePlayer(name, color) {
    if (numInstances > 0) {
        throw logic_error("Trying to instantiate more than one human player");
    }
    numInstances++;
}

void HumanPlayer::update() {
    if (power > 0) {
        if (pGame->getTick() % MOVE_INTERVAL == 0) {
            setSquare(getNextSquare());
        }

        char action = toLowerCase(pGame->getKey()); 
        doAction(action);
    }
}