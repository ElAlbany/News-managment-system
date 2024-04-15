#pragma once
#include <iostream>
#include <string>
#include <map>
#include< vector>
#include "News.h"

using namespace std;
class UserRepository
{
	string username;
	string password;
	vector<string> bookMarking; // push news title (for users )
public:

	static vector<UserRepository> users; // main data structure to store all users
	static vector<UserRepository> admins; // main data structure to store all admins




};

