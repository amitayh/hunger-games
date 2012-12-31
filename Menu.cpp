#include "Menu.h"
#include "Console.h"
#include <conio.h>
#include <iostream>

using namespace std;
using namespace HungerGames;

int Menu::addOption(const string& option) {
    options.push_back(option);
    return options.size();
}

void Menu::show() const {
    Console::clear();
    Console::gotoPosition(0, 0);
    Console::changeColor(Console::SILVER);

    cout << "Choose an option" << endl;
    cout << "----------------" << endl;
    
    // Print options
    int numOptions = options.size();
    for (int i = 0; i < numOptions; i++) {
        cout << (i + 1) << ". " << options[i] << endl;
    }
}

int Menu::choose() const {
    show();

    int numOptions = options.size(), option;
    do {
        // Get a valid input from user
        option = getch() - '0';
    } while (option < 1 || option > numOptions);

    return option;
}