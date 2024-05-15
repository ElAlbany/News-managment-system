#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Utility {
private:

public:
	/// checks if char belongs to {'1','2',..,'9'}
	static bool isDigitChar(char c);

	/// returns true if the format is right else false
	static bool checkDateFormat(string date); // check if the date is like the format: dd/mm/yyyy 12/3/2023 

	static vector<string> getKeyWords(string key);
	static string toLower(string word);
	static string toString(int num);
	static int toInt(string str);
	static void dateHandler(string& date);

	static void DM(string source, string message) { // debug message output to the console
		cout << "[" << source << "] " << message << endl;
	}

	static void getDateOrder(string date, int& year, int& month, int& day);
};
