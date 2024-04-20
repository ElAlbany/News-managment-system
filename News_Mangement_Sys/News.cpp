#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // for the ctime warning
#endif

#include <ctime>
#include <vector>
#include <set>
#include "News.h"
#include "Utility.h"
#include <unordered_map>
#include <algorithm>

// main data structure to store all news (static definition)
vector<News> News::news; 
vector<string> News::categories;


News::News(string title, string description, string category, float rate) {
    time_t now = time(0);
    this->date = localtime(&now);
    this->title = title;
    this->description = description;
    this->category = category;
    this->rate = rate;
    news.push_back(*this);
}

News::News(string title, string description, string category) {
    time_t now = time(0);
    this->date = localtime(&now);
    this->title = title;
    this->description = description;
    this->category = category;
    this->rate = 0.0f;
    news.push_back(*this);
}

News::News(string title, string description) {
    time_t now = time(0);
    this->date = localtime(&now);
    this->title = title;
    this->description = description;
    this->rate = 0.0f;
    this->category = "";
    news.push_back(*this);
}//*********************************************
void News::calculateAverageRate() {
    int totalRatings = 0;
    int numRatings = allRate.size();
    if (numRatings == 0) {
        this->rate = 0.0f;
        return;
    }
    for (auto it: allRate) {
        totalRatings += it.second;
    }
    this->rate = (float) totalRatings / numRatings;
}

void News::rateNews(vector<News> &newsRef, string userName) {
    if (news.empty()) {
        cout << "Sorry :( There Isn't any News Right Now\n";
        return;
    }
    cout << "     ============    Here Is ALL News :)      ============    \n";
    for (int i = 0; i < newsRef.size(); i++) {
        cout << "[" << i + 1 << "]" << newsRef[i].title;
    }
    int index;
    do {
        cout << "Enter The News Number To Rate ( Or Enter -1 To Skip)\n";
        cin >> index;
    } while (index < -1 || index > newsRef.size());
    if (index == -1) {
        return;
    }
    index--;
    short userRating;
    do {
        cout << "Enter Your Rating ( It Must Be Between 1 and 5 )\n";
        cin >> userRating;

    } while (userRating < 1 || userRating > 5);
    newsRef[index].allRate.emplace(pair<string, int>(userName, userRating));
    newsRef[index].calculateAverageRate();
    cout << "Your rating has been added successfully." << endl;
}

/////////////////////////////////////// displayNewsByCategoryName ////////////////////////////////////////////
void News::displayNewsByCategoryName(string categoryName) {
    if (news.empty()) {
        cout << "Sorry :( There Isn't any News Right Now\n";
        return;
    }
    bool is_found = false;
    transform(categoryName.begin(), categoryName.end(), categoryName.begin(), ::tolower);
    for (auto it: news) {
        transform(it.category.begin(), it.category.end(), it.category.begin(), ::tolower);
        if (it.category == categoryName) {
            is_found = true;
            break;
        }
    }
    if (is_found) {
        cout << "     ============    Here Is ALL " << categoryName << " News :)      ============    \n";
        for (auto it: news) {
            if (it.category == categoryName) {
                cout << "\nTitle: " << it.title << endl;
                cout << "Description: " << it.description << endl;
                cout << "Date: " << it.date << endl;
                cout << "Category: " << it.category << endl;
                cout << "Rate: " << it.rate << endl;
                cout << "             =========================                       \n";
            }
        }
    } else {
        cout << "sorry :( This Is Category Is Not Exist\n";
    }
}




float News::getRate() {
    return this->rate;
}

string News::getTitle() {
    return this->title;
}

string News::getDescription() {
    return this->description;
}

string News::getCategory() {
    return this->category;
}

string News::getDate() {
    return to_string(this->date->tm_mday) + "/" + to_string(this->date->tm_mon + 1) + "/" +
           to_string(this->date->tm_year + 1900);
}

/////////////////////////////////////// serachNews ////////////////////////////////////////////
vector<News> News::serachNews(string description_key) { // search by descroption for now , title later

    vector<string> keywords = Utility::getKeyWords(description_key); // get all keywords in the search text

    vector<pair<News, int>> searching_result; 
    set<string> taken;
    unordered_map<string, int> indx;

    for (auto &news_post : news) {
        string lowerDescription = Utility::toLower(news_post.getDescription());
        string lowerTitle = Utility::toLower(news_post.getTitle());
        
        for (auto &word : keywords) {
            if (lowerDescription.find(Utility::toLower(word) + " ") != string::npos || // search in title and description
                lowerDescription.find(" " + Utility::toLower(word)) != string::npos || 
                lowerTitle.find(Utility::toLower(word) + " ") != string::npos ||
                lowerTitle.find(" " + Utility::toLower(word)) != string::npos) {

                //cout << "describtionnn : " << lowerDescription << endl;
                if (taken.find(lowerTitle) == taken.end()) {  // if taken i don't need to take it again (no dublicate posts)
                    indx[lowerTitle] = searching_result.size(); // saving the index of the current pushed post to be used later
                    searching_result.push_back({ news_post, 1});
                    taken.insert(lowerTitle); // mark as taken 
                   
                }
                else {
                    // the bigger the score for each post the more to be displayed at the list beginning
                    searching_result[indx[lowerTitle]].second++;
                }
            }
        }
    }

    // sorting the news by the matching score.
    sort(searching_result.begin(), searching_result.end(), [&](auto p1, auto p2)->bool { 
            return p1.second > p2.second;
    });

    // returning the news only without the score
    vector<News> final_serching_result;
    for (auto post : searching_result) {
        final_serching_result.push_back(post.first);
    }

    return final_serching_result;
}
///////////////////////////////////////// displayPost //////////////////////////////////////////
void News::displayPost() {
    cout << "\nTitle: " << this->title << endl;
    cout << "Description: " << this->description << endl;
    cout << "Date: " << this->date << endl;
    cout << "Category: " << this->category << endl;
    cout << "Rate: " << this->rate << endl;
    cout << "             =========================                       \n";
}

///////////////////////////////////////////////////////////////////////////////////
