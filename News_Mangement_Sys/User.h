#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<unordered_set>
#include<unordered_map>
#include"News.h"
#include<set>
using namespace std;
class User {
private:
    string Username, Password;
public:
    static vector<User> users;
    static string currentUsername, currentPassword;
    static unordered_map<string, unordered_set<string>> bookmarks;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    set<string> spamNews;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
    //----------------
    void spamNewsFunc();
    //---------------
    static void addCategory();
    static void postNews();
    static void removeNews();
    static void getAverageRateByTitle();
    static void bookmarkingMenu();
    static void AddToBookmarks();
    static bool IsInBookmarks(string title);
    static void RemoveFromBookmarks();
    static void PrintBookmarks();
};