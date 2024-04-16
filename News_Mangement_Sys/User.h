#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User
{
private:
	string Username, Password;
public:
	static vector <User> users;
	static string currentUsername, currentPassword;
	User(string username, string password);
	string getPassword();
	string getUsername();
	static int Register();
	static void displayAllUsers();
	static User searchUserByUsername(string username);
	static int LogIn();
};

