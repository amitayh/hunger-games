#include "Common.h"

char HungerGames::toLowerCase(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch -= ('A' - 'a');
    }
    return ch;
}