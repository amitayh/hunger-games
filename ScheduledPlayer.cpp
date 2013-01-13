#include "ScheduledPlayer.h"
#include "Game.h"

using namespace HungerGames;

ScheduledPlayer::ScheduledPlayer(char name, Console::Color color, const char* eventsFilename):
    BasePlayer(name, color), events(eventsFilename) {
}

void ScheduledPlayer::update() {
    if (power > 0) {
        if (pGame->getTick() % MOVE_INTERVAL == 0) {
            setSquare(getNextSquare());
        }
        EventsFile::Event* event = events.getEvent(pGame->getTick());
        if (event) {
            for (int i = 0; i < event->getNumActions(); i++) {
                doAction((Action) event->getAction(i));
            }
        }
    }
}