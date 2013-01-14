#ifndef _COMMON_H
#define _COMMON_H

#include <exception>

using namespace std;

namespace HungerGames
{

    // General use functions

    char toLowerCase(char ch);

    // Exceptions

    class IOError: public exception
    {
    public:
        IOError(const char* msg = "");
    };

    class EndOfFile: public exception
    {
    public:
        EndOfFile(const char* msg = "");
    };

}

#endif