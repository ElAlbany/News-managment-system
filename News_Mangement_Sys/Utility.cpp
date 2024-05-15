#include "Utility.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
// u don't have to trace this just use it as an abstract functions :)

bool Utility::isDigitChar(char c) {
	return (c >= '0' and c <= '9');
}

bool Utility::checkDateFormat(string date) {

	int n = date.size();
	int ind = 0;

	// this function counts how many separators in the date string
	int cnt = count_if(date.begin(), date.end(), [](char c) {return Utility::isDigitChar(c) == false; });
	if (cnt != 2) return 0;

	vector<vector<char>> dmy(3, vector<char>());
	for (int i = 0; i < n; i++) {
		if (isDigitChar(date[i])) {
			dmy[ind].push_back(date[i]);
		}
		else ind++;
	}
	if (dmy[0].size() > 2 or dmy[0].empty() or (dmy[0].size() == 2 and dmy[0][0] == '3' and dmy[0].back() > '1')) return 0; // day can be (1,2,3,..,31) only

	if (dmy[1].size() > 2 or dmy[1].empty() or (dmy[1].size() == 2 and dmy[1].back() > '2')) return 0; // month can be from 1 to 12 only

	if (dmy[2].size() != 4 or dmy[2].empty()) return 0; // year made only from 1000 to 9999 (can be customized)

	return 1; // its valid
}



string Utility::toString(int num) {
	if (num == 0) return "0";

	string res = {};
	while (num) {
		int d = num % 10;
		res.push_back((d + '0'));
		num /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

int Utility::toInt(string str) {
	int res = 0;
	int n = str.size();
	for (int i = 0; i < n; i++) {
		res = res * 10 + (str[i] - '0');
	}
	return res;
}

void Utility::dateHandler(string& date)
{
	// checks if the date is in the format (d1d2/m1m2/y1y2y3y4)
	if (date[1] == '/' || date[2] == '/') {
		reverse(date.begin(), date.end()); // the date becomes (y4y3y2y1/m2m1/d2d1) so we need to correct it
		char tmp;
		tmp = date[0];
		date[0] = date[3];
		date[3] = tmp;
		tmp = date[1];
		date[1] = date[2];
		date[2] = tmp;

		// the date becomes (y1y2y3y4/m2m1/d2d1)
		
		if (date.size() == 10) { // it means that the month and day are both of 2 digits
			tmp = date[5]; 
			date[5] = date[6];
			date[6] = tmp;
			tmp = date[8];
			date[8] = date[9];
			date[9] = tmp;
		}
		else if (date.size() == 9) { // it means only the month or the day is of 2 digits
			
			
			if (date[6] == '/') { // checks if the month is of 1 digit 
				tmp = date[7];
				date[7] = date[8];
				date[8] = tmp;
			}
			else { // true if the day is of 2 digits and month is of only 1 digit
				tmp = date[5];
				date[5] = date[6];
				date[6] = tmp;
			}
		}
	}
}

void Utility::getDateOrder(string date, int& year, int& month, int& day)
{
	year = stoi(date.substr(0, 4));
	if (date[6] == '/') {
		month = stoi(date.substr(5, 1));
		if (date.size() == 9) {
			day = stoi(date.substr(7, 2));
		}
		else {
			day = stoi(date.substr(7, 1));
		}
	}
	else {
		month = stoi(date.substr(5, 2));
		if (date.size() == 10) {
			day = stoi(date.substr(8, 2));
		}
		else {
			day = stoi(date.substr(8, 1));
		}

	}
}

// ex: converts 'hi im mohamed' to {hi, im, mohamed}
vector<string> Utility::getKeyWords(string key) {
	vector<string> result;
	string s;
	for (auto c : key) {
		if (isalpha(c)) { // if it is an alphabet char
			s.push_back(c);
		}
		else {
			if (!s.empty())result.push_back(s);
			s.clear();
		}
	}
	if (!s.empty()) result.push_back(s);
	return result;
}

// ex: converts HEllO to hello
string Utility::toLower(string word) { 
	string res;
	for (auto c : word) res.push_back(tolower(c));
	return res;
}
