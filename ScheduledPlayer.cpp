#include "ScheduledPlayer.h"
#include "Game.h"

using namespace HungerGames;

ScheduledPlayer::ScheduledPlayer(char name, Console::Color color, const char* eventsFilename):
    BasePlayer(name, color), events(eventsFilename) {
}

void ScheduledPlayer::update() {
    nextArrowType = ArrowsBag::NONE;
    EventsFile::Event* ev = events.getEvent(pGame->getTick());
    if (ev) {
        ActionsList& actions = ev->getActions();
        ActionsIterator it = actions.begin();
        while (it != actions.end()) {
            doAction(*it);
            it++;
        }
    }
    BasePlayer::update();
}