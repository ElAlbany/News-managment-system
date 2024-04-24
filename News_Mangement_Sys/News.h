#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include"User.h"

using namespace std;

class News {

    string title;
    string description;
    tm *date;
    string category;
    float rate;                 // this is the actual rate comes from summing rates and divied on their size
    multimap<string, int> allRate;
public:
    static vector<News> news; // main data structure to store all news
    static vector<string> categories;

    // Constructors

    News(string title, string description);

    //functions
    static void rateNews(vector<News> &newsRef, string userName);

    void calculateAverageRate();

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

    static void displayLatestNews() {
        sort(News::news.begin(), News::news.end(), News::sortNewsByDate);
        for (int i = 0; i < (int) News::news.size(); i++) {
            cout << "[" << i+1 << "] " << News::news[i].getTitle() << " : " << News::news[i].getDescription()
                 << " \n\tDate : " << News::news[i].getDate() << " \n\tRating : " << News::news[i].getRate()
                 << " \n\tCategory : " << News::news[i].getCategory() << endl;
        }
    }

    static void displayTrendingNews() {
        sort(News::news.begin(), News::news.end(), News::sortNewsByRating);
        for (int i = 0; i < (int) News::news.size(); i++) {
            cout << "[" << i+1 << "] " << News::news[i].getTitle() << " : " << News::news[i].getDescription()
                 << " \n\tDate : " << News::news[i].getDate() << " \n\tRating : " << News::news[i].getRate()
                 << " \n\tCategory : " << News::news[i].getCategory() << endl;
        }
    }

    static bool displayAllNews() {
        if (news.size() == 0) {
            cout << "there is no news right now \n";
            return false;
        } 
        cout << "here is all the news\n";
        cout << "\n";
        for(int i = 0; i < news.size(); i++) {
          if(find(User::spamNews.begin(),User::spamNews.end(),news[i].getTitle())==User::spamNews.end())
            cout<<"["<<i+1<< "] " << news[i].getTitle() <<"\n";
        }
        return true;
    }

};
