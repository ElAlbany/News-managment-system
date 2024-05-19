#include <windows.h>
#include <string>

using namespace std;

class Style {

public:
	static void setupConsole(); // setup at the start of the program
	static void styleText(string text); // style any text by adding a background color and center align it
};