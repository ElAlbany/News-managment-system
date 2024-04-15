#pragma once
#include <iostream>
#include <string>
#include <map>
#include< vector>
#include "UserRepository.h"
using namespace std;
class News
{
	string title;
	string description;
	string date;
	string category;
	float rate; // this is the actual rate comes from summing rates and divied on their size
	map<string, int > allRate; // username and his rate // rates can be edited so we need the username ,so map is convenient for that

public:

	static vector<News> news; // main data structure to store all news


};

