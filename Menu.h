#ifndef _MENU_H
#define _MENU_H

#include <vector>

using namespace std;

class Menu
{
    vector<const char*> options;

public:
    int addOption(const char* option);

    void show() const;
    int choose() const;
};

#endif