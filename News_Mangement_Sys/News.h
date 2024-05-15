#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include "User.h"
#include "Date.h"
#include  <set>

using namespace std;
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

class News {


private:
    std::string title;
    std::string description;
    Date date;
    std::string category; // should be replaced by enum later.
    float rate;                  // this is the actual rate comes from summing rates and divied on their size
public:

    vector<Comment> comments;
    multimap<string, int> allRate; // username and his rate // rates can be edited so we need the username ,so map is convenient for that
    static vector<News> news; // main data structure to store all news
    static vector<string> categories;
    static map<int,bool> valid;


    // Constructors
    News(string title, string description, string category, float rate, Date date);

    News(string title, string description, string category, float rate);

    News(string title, string description, string category);

    News(string title, string description);

    static void rateNews(vector<News>& newsRef, string userName);
    static void updateMenu();
    void updateNewsTitle(string new_title);
    void updateNewsDescription(string new_description);
    void updateNewsDate(Date new_date);
    void updateNewsCategory();

    static void displayNewsByCategoryName(string);
    void displayPost();
    static void displayCategories();



    void calculateAverageRate();
    //float getAverageRateByTitle(string);


    static vector<News> serachNews(string title_key);
    // Getters
    float getRate() const;
    string getTitle() const;
    string getDescription() const;
    string getCategory() const;
    Date getDate() const;

    // Display News sorted by [rating, date]
    static bool sortNewsByRating(News& news1, News& news2) {
        return news1.getRate() > news2.getRate();
    }
    static bool sortNewsByDate(News& news1, News& news2) {

        string date1 = news1.getDate().fullDate('/'), date2 = news2.getDate().fullDate('/');

        int year1 = std::stoi(date1.substr(0, 4));
        int year2 = std::stoi(date2.substr(0, 4));
        int month1, month2, day1, day2;

        if (date1[6] == '/') {
             month1 = std::stoi(date1.substr(5, 1));
             if (date1.size() == 9) {
                 day1 = std::stoi(date1.substr(7, 2));
             }
             else {
                 day1 = std::stoi(date1.substr(7, 1));
             } 
        }
        else {
             month1 = std::stoi(date1.substr(5, 2));
             if (date1.size() == 10) {
                 day1 = std::stoi(date1.substr(8, 2));
             }
             else {
                 day1 = std::stoi(date1.substr(8, 1));
             }
             
        }

        if (date2[6] == '/') {
            month2 = std::stoi(date2.substr(5, 1));
            if (date2.size() == 9) {
                day2 = std::stoi(date2.substr(7, 2));
            }
            else {
                day2 = std::stoi(date2.substr(7, 1));
            }
        }
        else {
            month2 = std::stoi(date2.substr(5, 2));
            if (date2.size() == 10) {
                day2 = std::stoi(date2.substr(8, 2));
            }
            else {
                day2 = std::stoi(date2.substr(8, 1));
            }

        }
        // Compare the dates
        if (year1 > year2) return true;
        if (year1 < year2) return false;
        if (month1 > month2) return true;
        if (month1 < month2) return false;
        if (day1 > day2) return true;

        return false;
    }

    //static void displayLatestNews(int);
    static void displayTrendingNews();
    static bool displayAllNews(string,int,string);
    //static void displayNewsForUser();
    void displayNewsPost() const;

    static void commentMenu();
    static void displayComments();
    static void addComment();
    static void removeComment(int index);
};
