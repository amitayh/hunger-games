#include "Common.h"

using namespace HungerGames;

char HungerGames::toLowerCase(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch -= ('A' - 'a');
    }
    return ch;
}