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

    
public:
    string Username, Password, Email;
    int LoginAtempts;
    static map<string,User> users;
    static string currentUsername, currentPassword;
    static unordered_map<string, unordered_set<string>> bookmarks;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int spamCount;
    set<string> spamNews;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    User(string username, string password, string email);
    User();
    static bool is_email_valid(string email);
    static void adminMenu();
    static void userMenu();
    string getPassword();
    string getUsername();
    void ForgetPassword(string username);
    static int Register();
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
