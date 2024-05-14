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
    Date commentDate;
public:
    Comment(const string& _user, const string& _body, const Date& _date);

    void setCommentBody(const string& new_body);
    void setUserName(const string& new_user_name);
    //void setDate(const Date& new_date);
    void display();

    string getUserName() const;
    string getBody() const;
    Date getDate() const;
};

class News {


private:
    std::string title;
    std::string description;
    Date date;
    std::string category; // should be replaced by enum later.
    float rate;                  // this is the actual rate comes from summing rates and divied on their size

protected:
    static map<int, vector<Comment>> saveComments; // for displaying the comments in organized way
public:


    multimap<string, int> allRate; // username and his rate // rates can be edited so we need the username ,so map is convenient for that
    vector<Comment> comments;
    static vector<News> news; // main data structure to store all news
    static vector<string> categories;
    static set<int> valid;


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
        return (news1.getDate().fullDate('/') > news2.getDate().fullDate('/'));
    }

    //static void displayLatestNews(int);
    static void displayTrendingNews();
    static bool displayAllNews(string,int,string);
    //static void displayNewsForUser();
    static bool validChoice(int choice);

    static void displayCommentsOnUserChoice();

    void displayNewsPost() const;
    
    void addComment();
};
