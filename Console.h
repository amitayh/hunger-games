#ifndef _CONSOLE_H
#define _CONSOLE_H

enum Color {
    BLACK   = 0x0,
    NAVY    = 0x1,
    GREEN   = 0x2,
    TEAL    = 0x3,
    MAROON  = 0x4,
    PURPLE  = 0x5,
    OLIVE   = 0x6,
    SILVER  = 0x7,
    GREY    = 0x8,
    BLUE    = 0x9,
    LIME    = 0xA,
    CYAN    = 0xB,
    RED     = 0xC,
    MAGENTA = 0xD,
    YELLOW  = 0xE,
    WHITE   = 0xF
};

void ChangeColor(Color color);

#endif