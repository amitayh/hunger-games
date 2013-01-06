#include "ScheduledPlayer.h"
#include "Game.h"

using namespace HungerGames;

ScheduledPlayer::ScheduledPlayer(char name, Console::Color color, const std::string& eventsFilename):
    BasePlayer(name, color), events(eventsFilename) {
}

void ScheduledPlayer::update() {
    if (power > 0) {
        char actions[3];
        if (events.readActions(pGame->getTick(), actions)) {
            for (int i = 0; actions[i] != '\0'; i++) {
                doAction((Action) actions[i]);
            }
        }
    }
}