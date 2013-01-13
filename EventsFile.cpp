#include "EventsFile.h"
#include "Common.h"
#include <exception>

using namespace HungerGames;

const char EventsFile::SEPARATOR = '\n';

EventsFile::EventsFile(const char* filename) {
    file.open(filename);
    if (!file.good()) {
        throw IOError();
    }
}

EventsFile::~EventsFile() {
    file.close();
}

EventsFile::Event* EventsFile::getEvent(unsigned int tick) {
    if (tick > lastEvent.tick && !file.eof()) {
        // Read next event from file
        readEvent();
    }
    if (tick == lastEvent.tick) {
        return &lastEvent;
    }
    return NULL;
}

void EventsFile::readEvent() {
    file >> lastEvent.tick;
    lastEvent.numActions = 0;
    bool read = true;
    while (read && !file.eof() && lastEvent.numActions < Event::MAX_ACTIONS) {
        char action = toLowerCase(file.get());
        if (action >= 'a' && action <= 'z') {
            // Valid action, add to actions array
            lastEvent.actions[lastEvent.numActions] = action;
            lastEvent.numActions++;
        }
        if (action == SEPARATOR) {
            read = false;
        }
    }
}

EventsFile::Event::Event() {
    tick = 0;
    numActions = 0;
}

int EventsFile::Event::getNumActions() {
    return numActions;
}

char EventsFile::Event::getAction(int index) {
    if (index < 0 || index >= numActions) {
        throw OutOfRangeError();
    }
    return actions[index];
}