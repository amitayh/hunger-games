#include "EventsFile.h"
#include "Common.h"
#include <exception>

using namespace HungerGames;

const char EventsFile::SEPARATOR = '\n';

EventsFile::EventsFile(const char* filename) {
    file.open(filename);
    if (!file.good()) {
        throw IOError("Unable to open events file");
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
        // Last read event matches current tick - return it
        return &lastEvent;
    }
    return NULL;
}

void EventsFile::readEvent() {
    file >> lastEvent.tick; // Read tick
    lastEvent.actions.clear(); // Clear actions list
    bool read = true;
    while (read && !file.eof()) {
        char action = toLowerCase(file.get());
        if (action >= 'a' && action <= 'z') {
            // Valid action, add to actions list
            lastEvent.actions.push_back(action);
        }
        if (action == SEPARATOR) {
            // End of line, break out of the loop
            read = false;
        }
    }
}

EventsFile::Event::Event() {
    tick = 0;
}

ActionsList& EventsFile::Event::getActions() {
    return actions;
}