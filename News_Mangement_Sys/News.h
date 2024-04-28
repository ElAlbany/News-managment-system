#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include "User.h"
using namespace std;
class Comment
{
    public:
    string UserName;
    string Comment;
    Comment(string user_name, string comment)
    {
        UserName = user_name;
        Comment = comment;
    }
}
class News {
    string title;
    string description;
    tm *date;
    string category;
    float rate;                  // this is the actual rate comes from summing rates and divied on their size
    multimap<string, int> allRate; // username and his rate // rates can be edited so we need the username ,so map is convenient for that
    vector<Comment> comments;
    int nextCommentIdx;
public:
    static vector<News> news; // main data structure to store all news
    static vector<string> categories;
    // Constructors
    News(string title, string description);
    News(string title, string description, string category, float rate);
    News(string title, string description, string category); // functions
    static void rateNews(vector<News> &newsRef, string userName);
    void calculateAverageRate();
    float getAverageRateByTitle(string);
    static void displayNewsByCategoryName(string);
    // Getters
    float getRate();
    string getTitle();
    string getDescription();
    string getCategory();
    string getDate();
    // Display News sorted by [rating, date]
    static bool sortNewsByRating(News &news1, News &news2) {
        return news1.getRate() > news2.getRate();
    }
    static bool sortNewsByDate(News &news1, News &news2) {
        return news1.getDate() > news2.getDate();
    }
    static void displayLatestNews();
    static void displayTrendingNews();
    static bool displayAllNews();
    void addComment();
    void displayComments();
};
