#include "Utility.h"
#include <cassert>
#include <algorithm>
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
	assert(num >= 0); // no negative
	if (num == 0) return "0";

	string res = {};
	while (num) {
		int d = num % 10;
		res.push_back((d + '0'));
	}
	reverse(res.begin(), res.end());
	return res;
}

int Utility::toInt(string str) {
	
	int res = 0;
	int n = str.size();
	for (int i = 0; i < n; i++) {
		res = res * pow(10, i) + (str[i] - '0');
	}
	return res;
}

// converts 'hi im mohamed' to {hi, im, mohamed}
vector<string> Utility::getKeyWords(string key) {
	vector<string> result;
	string s;
	for (auto c : key) {
		if (isalpha(c)) { // if it is an alphabet char
			s.push_back(c);
		}
		else {
			if(!s.empty())result.push_back(s);
			s.clear();
		}
	}
	if (!s.empty()) result.push_back(s);
	return result;
}

string Utility::toLower(string word) { // converts HEllO to hello
	string res;
	for (auto c : word) res.push_back(tolower(c));
	return res;
}
