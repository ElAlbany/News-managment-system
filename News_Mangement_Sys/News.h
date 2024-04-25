#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Date.h"

using namespace std;

class News {

private:
    std::string title;
    std::string description;
    Date date;
    std::string category; // should be replaced by enum later.

    float rate;                  // this is the actual rate comes from summing rates and divied on their size
    multimap<string, int> allRate; // username and his rate // rates can be edited so we need the username ,so map is convenient for that
public:
    static vector<News> news; // main data structure to store all news
    static vector<string> categories;


    

    // Constructors
    News(string title, string description, string category, float rate, Date date);

    News(string title, string description, string category, float rate);

    News(string title, string description, string category);

    News(string title, string description);

    //functions
    static void rateNews(vector<News> &newsRef, string userName);

    void updateNewsTitle(string new_title); // remaining
    void updateNewsDescription(string new_description);
    void updateNewsDate(Date new_date);
    void updateNewsCategory(string new_category);

    static void displayNewsByCategoryName(string);

    static vector<News> serachNews(string title_key);

    void calculateAverageRate();
    void displayPost();
    // Getters
    float getRate();

    string getTitle();

    string getDescription();

    string getCategory();

    Date getDate();

    // Display News sorted by [rating, date]
    static bool sortNewsByRating(News &news1, News &news2) {
        return news1.getRate() > news2.getRate();
    }

    static bool sortNewsByDate(News &news1, News &news2) {
        Date d1 = news1.getDate();
        Date d2 = news2.getDate();
        return (d1 > d2);
    }

    static void displayLatestNews() {
        sort(News::news.begin(), News::news.end(), News::sortNewsByDate);
        for (int i = 0; i < (int) News::news.size(); i++) {
            cout << "[" << i << "] " << News::news[i].getTitle() << " : " << News::news[i].getDescription()
                 << " \n\tDate : " << News::news[i].getDate().fullDate('/') << " \n\tRating : " << News::news[i].getRate()
                 << " \n\tCategory : " << News::news[i].getCategory() << endl;
        }
    }

    static void displayTrendingNews() {
        sort(News::news.begin(), News::news.end(), News::sortNewsByRating);
        for (int i = 0; i < (int) News::news.size(); i++) {
            cout << "[" << i << "] " << News::news[i].getTitle() << " : " << News::news[i].getDescription()
                 << " \n\tDate : " << News::news[i].getDate().fullDate('/') << " \n\tRating : " << News::news[i].getRate()
                 << " \n\tCategory : " << News::news[i].getCategory() << endl;
        }
    }

    static void displayAllNews() {
        if (news.size() == 0) {
            cout << "there is no news right now \n";
            return;
        } 

        // displaying news
        cout << "here is all the news\n";
        cout << "\n";

        int i = 1;
        for (auto n: news) {
            cout << "[" << i++ << "]" << " " << n.getTitle() << "\n";
        }
    }

};
