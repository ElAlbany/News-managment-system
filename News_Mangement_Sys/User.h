#pragma once

#include <iostream>
#include <string>
#include <vector>
#include<unordered_set>
#include<unordered_map>


using namespace std;

class User {
private:
    string Username, Password;
public:
    static vector<User> users;
    static string currentUsername, currentPassword;
    static unordered_map<string, unordered_set<string>> bookmarks;

    User(string username, string password);

    User();

    static void adminMenu();

    static void userMenu();

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

    static void bookmarkingMenu() {
        cout << "[1] add article to your favourite \n";
        cout << "[2] delete marked article \n";
        cout << "[3] display all marked articles \n";

        cout << "press -1 to skip\n";
        cout << "\n";
        cout << "enter your choice : ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            AddToBookmarks();
        } else if (choice == 2) {
            RemoveFromBookmarks();
        } else if (choice == 3) {
            PrintBookmarks();
        } else if (choice == -1)
            return;
        else {
            cout << "please select one of the shown operations above \n";
            bookmarkingMenu();
        }


    }

    static void AddToBookmarks() {
        int num;
        News::displayAllNews();
        cout << "enter number : ";
        cin >> num;
        if (num < 1 || num > News::news.size()) {
            cout << "you have entered wrong number \n";
            return;
        }
        bool flag = User::IsInBookmarks(News::news[num - 1].getTitle());
        if (flag) {
            cout << "already exists\n";
            return;
        }
        User::bookmarks[User::currentUsername].insert(News::news[num - 1].getTitle());
        cout << "added successfully\n";
    }

    static bool IsInBookmarks(string title) {
        return (User::bookmarks[User::currentUsername].find(title) != User::bookmarks[User::currentUsername].end());
    }

    static void RemoveFromBookmarks() {
        User::PrintBookmarks();
        int num;
        cout << "enter number to remove : ";
        cin >> num;
        if (num < 1 || num > User::bookmarks[User::currentUsername].size()) {
            cout << "you have entered wrong one \n";
            return;
        }
        auto it = User::bookmarks[User::currentUsername].begin();
        std::advance(it, num - 1);
        User::bookmarks[User::currentUsername].erase(it);
        cout << "removed successfully\n";

    }

    static void PrintBookmarks() {
        auto &it = User::bookmarks[User::currentUsername];
        if (it.empty())
            return void(cout << "You don't have bookmarks.\n");

        cout << "Your Bookmarks :\n";
        int i = 1;
        for (auto &it2: it) {
            cout << "[" << i++ << "]" << it2 << "\n";
            cout << "~~~~~~";
        }
        cout << "~~~~~~~~~~~~~~~~~~~~\n";
    }
//khaled
////////////////////////////////////////////////////////////
};

