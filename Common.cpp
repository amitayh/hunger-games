#include "Common.h"
#include <stdlib.h>

using namespace HungerGames;

char HungerGames::toLowerCase(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch -= ('A' - 'a');
    }
    return ch;
}

bool HungerGames::checkProbability(int probability) {
    int random = rand() % 100;
    return (random < probability);
}