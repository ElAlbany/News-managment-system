#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // for the ctime warning
#endif

#include <iostream>
#include "Date.h"
#include "Utility.h"
#include <cassert>
using namespace std;

void Date::constructDate(string date_str) {
	if (Utility::checkDateFormat(date_str) == 0) { // if not a valid date format
		throw exception("Exception: The specified Date have wrong formate!\n");
		return;
	}

	vector<int> dmy = getDayMonthYear(date_str);	
	this->mday = dmy[0];
	this->month = dmy[1];
	this->year = dmy[2];
}

vector<int> Date::getDayMonthYear(string date) {
	int n = date.size();
	int ind = 0;
	
	vector<string> dmy(3, string());
	for (int i = 0; i < n; i++) {
		if (Utility::isDigitChar(date[i])) {
			dmy[ind].push_back(date[i]);
		}
		else ind++;
	}
	int _d = Utility::toInt(dmy[0]);
	int _m = Utility::toInt(dmy[1]);
	int _y = Utility::toInt(dmy[2]);
	return { _d, _m, _y };
	

}

Date::Date(string date_str) {
	try {
		this->constructDate(date_str);
	}
	catch (exception ex) {
		cout << date_str << ' ' << ex.what() << endl;
	}
}

string Date::getCurrentDate(char sep) {
	tm* d;
	time_t now = time(0);
	string n = ctime(&now);
	d = localtime(&now);

	string _d = Utility::toString(d->tm_mday);
	string _m = Utility::toString(d->tm_mon+1);
	string _y = Utility::toString(d->tm_year+1900);
	return _d + sep + _m + sep + _y;
	
}

string Date::fullDate(char sep) {
	return Utility::toString(this->getDay()) + sep + Utility::toString(this->getMonth()) + sep + Utility::toString(this->getYear());
}

Date::Date() {
	string date = getCurrentDate('/');
	constructDate(date);
}


void Date::setDay(int _d) {
	assert(_d >= 1 and _d <= 31);
	this->mday = _d;
	
}

void Date::setMonth(int _m) {
	assert(_m >= 1 and _m <= 12);
	this->month = _m;
}

void Date::setYear(int _y) {
	assert(_y >= 1000);
	this->year = _y;
}

int Date::getDay() {
	return this->mday;
}

int Date::getMonth() {
	return this->month;
}

int Date::getYear() {
	return this->year;
}
