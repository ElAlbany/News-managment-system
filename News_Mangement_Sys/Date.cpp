#include "Date.h"
#include <cassert>

void Date::constructDate(string date_str) {
	if (Utility::checkDateFormat(date_str) == 0) { // if not a valid date format
		throw exception("Exception: The specified Date have wrong formate!\n");
		return;
	}
	this->fullDate = date_str;
}

Date::Date(string date_str) {
	try {
		this->constructDate(date_str);
	}
	catch(exception ex){
		cout << date_str << ' ' << ex.what() << endl;
	}
}

void Date::setDay(int _d) {
	assert(_d >= 1 and _d <= 31);

	string sub = Utility::toString(_d); // convert the num to a string
	string s = this->fullDate;
	int n = s.size();
	int  r = 0;
	for (int i = 0; i < n; i++) {
		if (Utility::isDigitChar(s[i]) == false) break;
		r = i;
	}
	s.replace(0, r + 1, sub); // replace the day substring with the wanted day string.

	this->fullDate = s; // update the whole date.
	
}

void Date::setMonth(int _m) {
	assert(_m >= 1 and _m <= 12);

	string s = this->fullDate;
	string sub = Utility::toString(_m); 

	int n = s.size();
	int l = 0, r = n - 1;
	
	for (int i = 0; i < n; i++) {
		if (Utility::isDigitChar(s[i]) == false) { // if / or any separator .. 12/3/2023 -> l = 2, r = 4
			l = i;
			break;
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		if (Utility::isDigitChar(s[i]) == false) { // if / or any separator
			r = i;
			break;
		}
	}

	s.replace(l + 1, r, sub);
	this->fullDate = s;
}

void Date::setYear(int _y) {
	assert(_y >= 1000);
	string s = this->fullDate;

	string sub = Utility::toString(_y);
	
	int n = s.size();
	int l = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (Utility::isDigitChar(s[i])) {
			l = i;
			break;
		}
	}

	s.replace(l + 1, n, sub);
	this->fullDate = s;

}

int Date::getDay() {
	int i = 0;
	while (Utility::isDigitChar(fullDate[i])) {
		i++;
	}
	string sub = fullDate.substr(0, i);
	int res = Utility::toInt(sub);
	return res;

}
//int Date::getYear() { return this->year; }
//int Date::getMonth() { return this->month; }



