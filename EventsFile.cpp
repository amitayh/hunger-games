#include "EventsFile.h"
#include "Common.h"
#include <exception>

using namespace HungerGames;

const char EventsFile::NEW_LINE = '\n';

EventsFile::EventsFile(const string& filename) {
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
        if (tick > event.tick) {
            // Read next event from file
            readEvent();
        }
        if (tick == event.tick) {
            return &event;
        }
    }
    return NULL;
}

void EventsFile::readEvent() {
    file >> event.tick;
    int numActions = 0;
    bool read = true;
    while (read && numActions < Event::MAX_ACTIONS) {
        char action = toLowerCase(file.get());
        if (action >= 'a' && action <= 'z') {
            // Valid action, add to actions array
            event.actions[numActions] = action;
            numActions++;
        }
        read = (action != NEW_LINE);
    }
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