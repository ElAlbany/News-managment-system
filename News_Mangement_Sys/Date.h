#pragma once
#include <iostream>
#include "Utility.h"
using namespace std;



class Date {
private:
	string fullDate;
	void constructDate(string str_date);

public:
	// constructor
	Date(string date_str);

	// getters
	int getDay();
	int getMonth();
	int getYear();

	// setters
	void setDay(int _d);
	void setMonth(int _m);
	void setYear(int _y);

	// others
};

