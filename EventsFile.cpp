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
        return &lastEvent;
    }
    return NULL;
}

void EventsFile::readEvent() {
    file >> lastEvent.tick;
    lastEvent.actions.clear();
    bool read = true;
    while (read && !file.eof()) {
        char action = toLowerCase(file.get());
        if (action >= 'a' && action <= 'z') {
            // Valid action, add to actions array
            lastEvent.actions.push_back(action);
        }
        if (action == SEPARATOR) {
            read = false;
        }
    }
}

EventsFile::Event::Event() {
    tick = 0;
}

list<char>& EventsFile::Event::getActions() {
    return actions;
}