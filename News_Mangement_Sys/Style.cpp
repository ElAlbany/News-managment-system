#include "Style.h"
#include <string>
#include <iostream>
#include "Database.h"


using namespace std;

enum Color { // Background Colors in hexadecimal
    defualt = 0x000f,
    GREENb_WHITEf = 0x002f,
    CYANb_WHITEf = 0x003f,
    WHITEb_BLACKf = 0x00f0,
    WHITEb_REDf = 0x00f4,
    REDb_WHITEf = 0x004f,
    PURPLEb_WHITEf = 0x005f,
    DARKYELLOWb_WHITEf = 0x006f,
    PINKb_WHITEf = 0x00cf,
};

void Style::styleText(string str) {
    int spaces = (85 - str.length() / 2) / 1.5;

    for (int i = 0; i < spaces; i++) {
        cout << " ";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::CYANb_WHITEf);
    cout << string(str.length(), ' ') << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::WHITEb_BLACKf);
    for (int i = 0; i < spaces; i++) {
        cout << " ";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::CYANb_WHITEf);
    cout << str << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::WHITEb_BLACKf);
    for (int i = 0; i < spaces; i++) {
        cout << " ";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::CYANb_WHITEf);
    cout << string(str.length(), ' ') << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::WHITEb_BLACKf);
}

void Style::setupConsole() {

    HWND consoleWindow = GetConsoleWindow();  // get console window handle

    SMALL_RECT windowSize = { 100, 100, 0, 0 };  // set console window size
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    LONG style = GetWindowLong(consoleWindow, GWL_STYLE); // gets the console window style from the handle

    style &= ~(WS_MAXIMIZEBOX | WS_VSCROLL); // disable maxmize button 

    SetWindowLong(consoleWindow, GWL_STYLE, style); // set the new style to the console window

    system("color f0");

    Database::read();
}