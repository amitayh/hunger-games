#include "EventsFile.h"

using namespace HungerGames;

EventsFile::EventsFile(const string& filename) {
    file.open(filename);
    if (!file.good()) {
        throw runtime_error("Unable to open events file");
    }
}

EventsFile::~EventsFile() {
    file.close();
}

bool EventsFile::readActions(unsigned int tick, char* actions) {
    if (!file.eof()) {
        
    }
    return false;
}