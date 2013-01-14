#include "Console.h"
#include <windows.h>
#include <process.h>
#include <iostream>

using namespace std;
using namespace HungerGames;

void Console::changeColor(Color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Console::gotoPosition(int row, int col) {
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = col;
    dwCursorPosition.Y = row;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void Console::clear() {
    system("cls");
}