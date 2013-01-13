#include "EventsFile.h"
#include "Common.h"
#include <exception>

using namespace HungerGames;

const char EventsFile::NEW_LINE = '\n';

EventsFile::EventsFile(const char* filename) {
    file.open(filename);
    if (!file.good()) {
        throw runtime_error("Unable to open events file");
    }
}

EventsFile::~EventsFile() {
    file.close();
}

EventsFile::Event* EventsFile::getEvent(unsigned int tick) {
    if (!file.eof()) {
        if (tick > lastEvent.tick) {
            // Read next event from file
            readEvent();
        }
        if (tick == lastEvent.tick) {
            return &lastEvent;
        }
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
        read = (action != NEW_LINE);
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
        throw out_of_range("Invalid action index");
    }
    return actions[index];
}