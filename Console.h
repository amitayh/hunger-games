#ifndef _CONSOLE_H
#define _CONSOLE_H

namespace Console {

    enum Color {
        BLACK,
        NAVY,
        GREEN,
        TEAL,
        MAROON,
        PURPLE,
        OLIVE,
        SILVER,
        GREY,
        BLUE,
        LIME,
        CYAN,
        RED,
        MAGENTA,
        YELLOW,
        WHITE
    };

    void changeColor(Color color);

    void gotoPosition(int row, int col);

    void clear();

}

#endif