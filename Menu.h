#ifndef _MENU_H
#define _MENU_H

#include <vector>
#include <string>

using namespace std;

namespace HungerGames
{

    class Menu
    {
        vector<string> options;

    public:
        int addOption(const string& option);

        void show() const;
        int choose() const;
    };

}

#endif