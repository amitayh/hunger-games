#include "Common.h"

using namespace HungerGames;

char HungerGames::toLowerCase(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch -= ('A' - 'a');
    }
    return ch;
}

IOError::IOError(const char* msg): exception(msg) {};

EndOfFile::EndOfFile(const char* msg): exception(msg) {};