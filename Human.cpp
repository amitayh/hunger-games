#include "Human.h"
#include "Common.h"
#include "Game.h"
#include <exception>

using namespace HungerGames;

int HumanPlayer::numInstances = 0;

HumanPlayer::HumanPlayer(char name, Console::Color color): BasePlayer(name, color) {
    if (numInstances > 0) {
        // Don't allow more than one human player
        throw logic_error("Trying to instantiate more than one human player");
    }
    numInstances++;
}

void HumanPlayer::update() {
    nextArrowType = ArrowsBag::NONE;
    // Get next action from user input (keyboard)
    char key = pGame->getKey();
    doAction(toLowerCase(key));
    // Call overridden method
    BasePlayer::update();
}