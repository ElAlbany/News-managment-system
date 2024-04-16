#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User
{
private:
	string Username, Password;
	static vector <User> users;
public:
	User(string username, string password);
	string getUsername();
	string getPassword();
	static void Register();
	static void displayAllUsers();
	static User searchUserByUsername(string username);
};

