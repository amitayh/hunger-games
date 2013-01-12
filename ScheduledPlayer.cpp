#include "ScheduledPlayer.h"
#include "Game.h"

using namespace HungerGames;

ScheduledPlayer::ScheduledPlayer(char name, Console::Color color, const std::string& eventsFilename):
    BasePlayer(name, color), events(eventsFilename) {
}

void ScheduledPlayer::update() {
    if (power > 0) {
        EventsFile::Event* event = events.getEvent(pGame->getTick());
        if (event) {
            for (int i = 0; i < event->getNumActions(); i++) {
                doAction((Action) event->getAction(i));
            }
        }
    }
}