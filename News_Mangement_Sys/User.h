#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
private:
    string Username, Password;
public:
    static vector<User> users;
    static string currentUsername, currentPassword;

    User(string username, string password);

    User();

    string getPassword();

    string getUsername();

    static int Register();

    static void displayAllUsers();

    static User searchUserByUsername(string username);

    static int LogIn();

    static void addCategory() {
        cout << "enter name of category you want to add it : ";
        string cat;
        cin >> cat;
        for (int i = 0; i < News::categories.size(); i++) {
            if (cat == News::categories[i]) {
                cout << "this category already exists \n";
                return;
            }
        }
        News::categories.push_back(cat);
        cout << "added successfully\n";
    }

    static void postNews() {
        string title, description, date;
        cout << "fulfill required information to add the article into system \n";
        cout << "\n";
        cout << "Enter title : ";
        cin >> title;
        cout << "enter description : ";
        cin >> description;
        News(title, description);
    }

    static void removeNews() {
        if (News::news.size() == 0) {
            cout << "there is no news right now \n";
            return;
        }
        News::displayAllNews();
        cout << "\n please selecet one of the shown above to remove  or enter -1 to skip\n";
        int num;
        cin >> num;
        if (num == -1)
            return;
        if (num < 1 || num > News::news.size()) {
            cout << "you have entered an invalid number , please try again \n";
            removeNews();
        }
        News::news.erase(News::news.begin() + num - 1);
        cout << "has beed removes successfully\n";

    }

    static void getAverageRateByTitle() {
        News::displayAllNews();
        cout << "enter  number of article you want to see its rate or -1 to skip\n";
        int num;
        cin >> num;
        if (num == -1)
            return;
        if (num > 1 || num > News::news.size()) {
            cout << "enter only numbers shown above ,please try again \n";
            getAverageRateByTitle();
        }
        cout << "rate : " << News::news[num - 1].getRate() << "\n";
    }

};

