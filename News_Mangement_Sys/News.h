#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>
#include "User.h"
#include "Date.h"

using namespace std;

/////////////////////////////////////// Comment Class ///////////////////////////////////////
class Comment {
private:
    string commentUserName;
    string commentBody;
public:
    Comment(const string& _user, const string& _body);

    void setCommentBody(const string& new_body);
    void setUserName(const string& new_user_name);
    void display();

    string getUserName() const;
    string getBody() const;
};
/////////////////////////////////////// Comment Class ///////////////////////////////////////




/////////////////////////////////////// News Class ///////////////////////////////////////
class News {


private:
    string title;
    string description;
    Date date;
    string category;
    float rate; // this is the actual rate which comes from the average of all users' rates
public:


    vector<Comment> comments;
    multimap<string, int> allRate; // username and his rate, rates can be edited so we need the username; so map is convenient for that
    static vector<News> news; // main data structure to store all news
    static vector<string> categories;
    static vector<News> valid; // used to store the news the current user can see ((unrated or above rating of 2) and not spam)


    // Constructors
    News(string title, string description, string category, float rate, Date date);
    News(string title, string description, string category, float rate);
    News(string title, string description, string category);
    News(string title, string description);

    // Functions
    static void rateNews(string userName);
    static void updateMenu();
    void updateNewsTitle(string new_title);
    void updateNewsDescription(string new_description);
    void updateNewsDate(Date new_date);
    void updateNewsCategory();

    static void displayNewsByCategoryName(string);
    void displayPost();
    static void displayCategories();

    void calculateAverageRate();


    static vector<News> serachNews(string title_key);

    // Getters
    float getRate() const;
    string getTitle() const;
    string getDescription() const;
    string getCategory() const;
    Date getDate() const;

    // Display News sorted by rating
    static bool sortNewsByRating(News& news1, News& news2) {
        return news1.getRate() > news2.getRate();
    }

    // Display News sorted by date
    static bool sortNewsByDate(News& news1, News& news2) {

        string date1 = news1.getDate().fullDate('/'), 
               date2 = news2.getDate().fullDate('/');

        int year1, year2, month1, month2, day1, day2;

        Utility::getDateOrder(date1, year1, month1, day1);
        Utility::getDateOrder(date2, year2, month2, day2);

        if (year1 > year2) return true;
        if (year1 < year2) return false;
        if (month1 > month2) return true;
        if (month1 < month2) return false;
        if (day1 > day2) return true;

        return false;
    }

    // Used by both admin and user by passing [Sorted by, admin(1) | user(0), details or without]
    static void displayAllNews(string,int,string);

    // Comments' Functions
    static void commentMenu();
    static void displayComments();
    static void addComment();
    static void removeComment(int index);
};
/////////////////////////////////////// News Class ///////////////////////////////////////
