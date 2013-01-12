#include "Human.h"
#include "Common.h"
#include "Game.h"

using namespace HungerGames;

int HumanPlayer::numInstances = 0;

HumanPlayer::HumanPlayer(char name, Console::Color color): BasePlayer(name, color) {
    if (numInstances > 0) {
        throw logic_error("Unable to instantiate more than one human player");
    }
    numInstances++;
}

void HumanPlayer::update() {
    if (power > 0) {
        char key = toLowerCase(pGame->getKey()); 
        doAction((Action) key);
    }
}