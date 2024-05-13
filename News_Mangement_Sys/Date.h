#pragma once
#include<iostream>
#include <vector>
#include "Utility.h"
#include <sstream>
#include <iomanip>
using namespace std;

class Date {
private:
	void constructDate(string str_date);
	vector<int> getDayMonthYear(string date);
	int mday, month, year;

public:
	

	// constructor
	Date(string date_str);
	Date();

	// getters
	int getDay();
	int getMonth();
	int getYear();
	string fullDate(char sep); // takes a separator
	static string getCurrentDate(char sep);

	// setters
	void setDay(int _d);
	void setMonth(int _m);
	void setYear(int _y);

	// others
	bool operator>(Date& date) {
		if (this->year > date.year) return 1;
		if (this->year < date.year) return 0;
		if (this->month > date.month) return 1;
		if (this->month < date.month) return 0;
		return this->mday > date.mday;
	}

	bool operator==(Date& date) {
		return this->year == date.year && this->month == date.month && this->mday == date.mday;
	}

	bool operator<(Date& date) {
		return !(this->operator>(date) || this->operator==(date));
	}

	friend std::ostream& operator << (std::ostream& os, const Date& d) {
		return (os << d.mday << '/' << d.month << '/' << d.year);
	}

	// Converts date to string
	std::string toString() const {
		std::ostringstream oss;
		oss << std::setw(4) << std::setfill('0') << year << "-"
			<< std::setw(2) << std::setfill('0') << month << "-"
			<< std::setw(2) << std::setfill('0') << mday;
		return oss.str();
	}

	// Static method to create Date from string
	static Date fromString(const std::string& dateStr) {
		std::istringstream iss(dateStr);
		Date date;
		char dash; // for skipping the dashes
		if (!(iss >> date.mday >> dash >> date.month >> dash >> date.year)) {
			throw std::runtime_error("Invalid date format");
		}
		return date;
	}
};

