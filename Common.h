#ifndef _COMMON_H
#define _COMMON_H

namespace HungerGames
{

    // General use functions
    char toLowerCase(char ch);

    // Exceptions
    class SingletonError {};
    class IOError {};
    class OutOfRangeError {};
    class InvalidArgumentError {};
    class EndOfFileError {};

}

#endif