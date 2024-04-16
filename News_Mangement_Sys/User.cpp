#include "User.h"
vector <User> User::users;
string User::currentUsername, User::currentPassword;

User::User(string username, string password) {
	this->Username = username;
	this->Password = password;
}

string User::getUsername() {
	return this->Username;
}

string User::getPassword() {
	return this->Password;
}

int User::Register() {
	string username, password;
	cout << endl << "Sign In" << endl;
	cout << endl << "Enter your username" << endl;
	cin >> username;
	cout << endl << "Enter your password" << endl;
	cin >> password;
	if(username == "admin")
		return -1;
	for (int i = 0; i < User::users.size(); i++) {
		if (username == User::users[i].Username) {
			return -1;
		}
	}
	User usr(username, password);
	User::users.push_back(usr);
	return 0;
}

User User::searchUserByUsername(string username) {
	for (int i = 0; i < User::users.size(); i++) {
		if (username == User::users[i].Username) {
			return User::users[i];
		}
	}
}

void User::displayAllUsers() {
	for (int i = 0; i < User::users.size(); i++) {
		cout << endl << "[" << i << "]" << endl;
		cout << "username: " + User::users[i].Username << endl;
		cout << "password: " + User::users[i].Password << endl;
	}
}

int User::LogIn() {
	string username, password;
	bool LogedIn = false;
	cout << endl << "Log In" << endl;
	cout << endl << "Enter Username" << endl;
	cin >> username;
	cout << endl << "Enter Password" << endl;
	cin >> password;
	for (int i = 0; i < User::users.size(); i++) {
		if (username == User::users[i].Username && password == User::users[i].Password) {
			LogedIn = true;
		}
	}
	if (username == "admin" && password == "admin") {
		cout << endl << "welcome admin";
		return 1;
	}
	else if (LogedIn) {
		currentUsername = username;
		currentPassword = password;
		cout << "Loged in successfully";
		return 0;
	}
	else {
		return -1;
	}
	return -1;
}