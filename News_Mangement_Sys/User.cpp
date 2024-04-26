#include "User.h"
#include "News.h"
#include<unordered_set>
#include<unordered_map>

vector<User> User::users;
string User::currentUsername, User::currentPassword;
unordered_map<string, unordered_set<string>> User::bookmarks;

User::User(string username, string password) {
    this->Username = username;
    this->Password = password;
}

User::User() {
    this->Username = "";
    this->Password = "";
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
    if (username == "admin")
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
    User us;
    for (int i = 0; i < User::users.size(); i++) {
        if (username == User::users[i].Username) {
            return User::users[i];
        }
    }
    return us;
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
    bool LoggedIn = false;
    cout << endl << "Log In" << endl;
    cout << endl << "Enter Username" << endl;
    cin >> username;
    cout << endl << "Enter Password" << endl;
    cin >> password;
    for (int i = 0; i < User::users.size(); i++) {
        if (username == User::users[i].Username && password == User::users[i].Password) {
            LoggedIn = true;
        }
    }
    if (username == "admin" && password == "admin") {
        return 1;
    } else if (LoggedIn) {
        currentUsername = username;
        currentPassword = password;
        cout << "Logged in successfully";
        return 0;
    } else {
        return -1;
    }
    return -1;


}

void User::adminMenu() {
    cout << "\twelcome to admin menu\n";
    cout << "Here is all admin operations \n";
    cout << "please select one of the operations below\n\n\n";
    cout << "[1] add new category \n";
    cout << "[2] post news \n";
    cout << "[3] remove news \n";
    cout << "[4] update news \n";
    cout << "[5] display an article rate\n";
    cout << "[6] display all news\n";
    cout << "[7] log out\n";
}

void User::userMenu() {
    cout << "\twelcome to user menu\n";
    cout << "Here is all user operations \n";
    cout << "please select one of the operations below\n\n\n";
    cout << "[1] search  \n";
    cout << "[2] display latest news \n";
    cout << "[3] search by category \n";
    cout << "[4] rate news \n";
    cout << "[5] bookmarking\n";
    cout << "[6] trending news\n";
    cout << "[7] Spam News\n";
    cout << "[8] log out\n";
}

