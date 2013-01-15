#ifndef _COMMON_H
#define _COMMON_H

#include <exception>

using namespace std;

namespace HungerGames
{

    // General use functions

    char toLowerCase(char ch);

    bool checkProbability(int probability);

    // Exceptions

    class IOError: public exception
    {
    public:
        IOError(const char* msg = ""): exception(msg) {};
    };

    class EndOfFile: public exception
    {
    public:
        EndOfFile(const char* msg = ""): exception(msg) {};
    };

    class InvalidPosition: public exception
    {
    public:
        InvalidPosition(const char* msg = ""): exception(msg) {};
    };
}

#endif