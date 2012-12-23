#ifndef _CONSOLE_H
#define _CONSOLE_H

namespace HungerGames
{

    class Console
    {
    public:
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

        static void changeColor(Color color);
        static void gotoPosition(int row, int col);
        static void clear();
    };

}

#endif