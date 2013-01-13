#ifndef _EVENTS_FILE_H
#define _EVENTS_FILE_H

#include <fstream>

using namespace std;

namespace HungerGames
{

    class EventsFile
    {
    public:
        class Event
        {
            static const int MAX_ACTIONS = 3;
            unsigned int tick;
            char actions[MAX_ACTIONS];
            int numActions;
        public:
            Event();
            int getNumActions();
            char getAction(int index);
            friend class EventsFile;
        };

        EventsFile(const char* filename);
        ~EventsFile();
        
        Event* getEvent(unsigned int tick);

    private:
        static const char NEW_LINE;

        ifstream file;
        Event event;

        void readEvent();
    };

}

#endif