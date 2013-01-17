#ifndef _EVENTS_FILE_H
#define _EVENTS_FILE_H

#include <fstream>
#include <list>

using namespace std;

namespace HungerGames
{

    typedef char Action;
    typedef list<Action> ActionsList;

    class EventsFile
    {
    public:
        class Event
        {
            unsigned int tick;
            ActionsList actions;
        public:
            Event();
            ActionsList& getActions();
            friend class EventsFile;
        };

        EventsFile(const char* filename);
        ~EventsFile();
        
        Event* getEvent(unsigned int tick);

    private:
        static const char SEPARATOR;

        ifstream file;
        Event lastEvent;

        void readEvent();
    };

}

#endif