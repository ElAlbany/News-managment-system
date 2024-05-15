#include "Style.h"
#include <string>
#include <iostream>
#include "Database.h"

using namespace std;

enum Color {
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
    int spaces = (80 - str.length() / 2) / 1.5;

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
    HWND consoleWindow = GetConsoleWindow();  // Get a handle to the console window

    // Set the console window size
    SMALL_RECT windowSize = { 90, 90, 0, 0 };  // Change the numbers to adjust the size
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    // Set the console buffer size to be the same as the window size
    COORD bufferSize = { 10, 10 };  // Change the numbers to adjust the size
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    // Get the current console window style
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

    // Remove the sizing border (WS_SIZEBOX), the maximize button (WS_MAXIMIZEBOX), and the vertical scroll bar (WS_VSCROLL)
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_VSCROLL);

    // Apply the new style
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    system("color f0");

    Database::read();
}