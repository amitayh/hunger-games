#ifndef _MENU_H
#define _MENU_H

enum MenuOption {QUIT, RESUME};

class Menu
{
public:
    MenuOption Choose();
};

#endif