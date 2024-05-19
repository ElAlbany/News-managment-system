#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "News.h"
#include <set>

using namespace std;


/////////////////////////////////////// User Class ///////////////////////////////////////
class User {

    string Username, Password, Email;

public:
   
    int LoginAttempts;
    static map<string, User> users;
    static string currentUsername, currentPassword;
    static unordered_map<string, unordered_set<string>> bookmarks;
    static unordered_map<string, unordered_set<string>> interestedCategories;
    static unordered_map<string, unordered_set<string>> spamNews;



    // Constructors
    User(string username, string password, string email);
    User();

    //Getters
    string getPassword();
    string getUsername();
    string getEmail();

    //Setters
    void setPassword(string usern);
    void setUsername(string passw);
    void setEmail(string em);


    // Menu
    static void adminMenu();
    static void userMenu();

    // Forget Password Functionality
    static bool is_password_valid(string& password);
    static bool is_email_valid(string& email);
    int ForgetPassword(string username);
    static string GenRandomPassword();

    // Spam Functionality
    void spamNewsFunc();
    void spamNewsMenu();
    void removeSpamNews();
    bool printSpam();

    // News
    static void postNews();
    static void removeNews();

    // Bookmarking
    static void bookmarkingMenu();
    static void AddToBookmarks();
    static bool IsInBookmarks(string title);
    static void RemoveFromBookmarks();
    static void PrintBookmarks();

    // Users' Interested (Followed) Categories 
    static void InterestedCategoriesMenu();
    static void AddCategoryToInterested();
    static void RemoveCategoryFromInterested();
    static void displayInterestedCategories();
    static void emailInterestedUsers(string category);

    // Others
    static void getAverageRateByTitle();
    static void search();
    static void addCategory();
    static void addCategoryAuto(string category);
    static int Register();
    static int LogIn();

};
/////////////////////////////////////// User Class ///////////////////////////////////////

