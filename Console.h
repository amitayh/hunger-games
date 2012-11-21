#ifndef _CONSOLE_H
#define _CONSOLE_H

enum Color {
    BLACK   = 0,
    NAVY    = 1,
    GREEN   = 2,
    TEAL    = 3,
    MAROON  = 4,
    PURPLE  = 5,
    OLIVE   = 6,
    SILVER  = 7,
    GREY    = 8,
    BLUE    = 9,
    LIME    = 10,
    CYAN    = 11,
    RED     = 12,
    MAGENTA = 13,
    YELLOW  = 14,
    WHITE   = 15
};

void changeColor(Color color);

#endif