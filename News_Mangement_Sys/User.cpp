#include "User.h"
vector <User> User::users;
User::User(string username, string password) {
	this->Username = username;
	this->Password = password; 
	users.push_back(*this);
}

string User::getUsername() {
	return this->Username;
}

string User::getPassword() {
	return this->Password;
}

void User::Register(User user) {
	for (int i = 0; i < User::users.size(); i++) {
		if (user.Username == User::users[i].Username) {
			cout << "username already exists" << endl;
			return;
		}
	}
	User::users.push_back(user);
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
		cout << "[" << i << "]" << endl;
		cout << "username: " + User::users[i].Username << endl;
		cout << "password: " + User::users[i].Password << endl;
	}
}