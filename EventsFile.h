#ifndef _EVENTS_FILE_H
#define _EVENTS_FILE_H

#include <string>
#include <fstream>

using namespace std;

namespace HungerGames
{

    class EventsFile
    {
        ifstream file;

    public:
        EventsFile(const string& filename);
        ~EventsFile();

        bool readActions(unsigned int tick, char* actions);
    };

}

#endif