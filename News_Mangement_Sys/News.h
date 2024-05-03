#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include "User.h"
#include "Date.h"

using namespace std;
class Comment
{
public:
    string UserName;
    string comment;
    Comment(string user_name, string coment)
    {
        UserName = user_name;
        comment = coment;
    }
};

class News {


private:
public:
    std::string title;
    std::string description;
    Date date;
    std::string category; // should be replaced by enum later.


    float rate;                  // this is the actual rate comes from summing rates and divied on their size
    multimap<string, int> allRate; // username and his rate // rates can be edited so we need the username ,so map is convenient for that
    vector<Comment> comments;
    int nextCommentIdx;
    static vector<News> news; // main data structure to store all news
    static vector<string> categories;



    // Constructors
    News(string title, string description, string category, float rate, Date date);

    News(string title, string description, string category, float rate);

    News(string title, string description, string category);

    News(string title, string description);

    static void rateNews(vector<News> &newsRef, string userName);
    void updateNewsTitle(string new_title);
    void updateNewsDescription(string new_description);
    void updateNewsDate(Date new_date);
    void updateNewsCategory(string new_category);

    static void displayNewsByCategoryName(string);
    void displayPost();



    void calculateAverageRate();
    float getAverageRateByTitle(string);


    static vector<News> serachNews(string title_key);
    // Getters
    float getRate();
    string getTitle();
    string getDescription();
    string getCategory();
    Date getDate();

    // Display News sorted by [rating, date]
    static bool sortNewsByRating(News& news1, News& news2) {
        return news1.getRate() > news2.getRate();
    }
    static bool sortNewsByDate(News &news1, News &news2) {
        Date d1 = news1.getDate();
        Date d2 = news2.getDate();
        return (d1 > d2);

    }

    static void displayLatestNews();
    static void displayTrendingNews();
    static bool displayAllNews();

    void addComment(string user);
    void displayComments();
};
