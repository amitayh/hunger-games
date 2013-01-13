#include "Human.h"
#include "Common.h"
#include "Game.h"

using namespace HungerGames;

int HumanPlayer::numInstances = 0;

HumanPlayer::HumanPlayer(char name, Console::Color color): BasePlayer(name, color) {
    if (numInstances > 0) {
        throw SingletonError();
    }
    numInstances++;
}

void HumanPlayer::update() {
    if (power > 0) {
        if (pGame->getTick() % MOVE_INTERVAL == 0) {
            setSquare(getNextSquare());
        }

        char key = toLowerCase(pGame->getKey()); 
        doAction((Action) key);
    }
}