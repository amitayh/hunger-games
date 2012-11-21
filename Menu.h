#ifndef _MENU_H
#define _MENU_H

const int MAX_OPTIONS = 5;

class Menu
{
    char* options[MAX_OPTIONS];
    int numOptions;

public:
    Menu();
    ~Menu();

    bool addOption(const char* option);

    int choose() const;
};

#endif