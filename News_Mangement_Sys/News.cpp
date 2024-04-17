#include "News.h"
#include <ctime>
#include <vector>

vector<News> News::news; // main data structure to store all news

News::News(string title, string description, string category, float rate)
{
    time_t now = time(0);
    this->date = localtime(&now);
    this->title = title;
    this->description = description;
    this->category = category;
    this->rate = rate;
    news.push_back(*this);
}

News::News(string title, string description, string category)
{
    time_t now = time(0);
    this->date = localtime(&now);
    this->title = title;
    this->description = description;
    this->category = category;
    news.push_back(*this);
}//*********************************************
void News::calculateAverageRate() {
    int totalRatings = 0;
    int numRatings = allRate.size();
    if (numRatings == 0) {
        this->rate = 0.0f;
        return;
    }
    for (auto it : allRate) {
        totalRatings += it.second;
    }
    this->rate = (float)totalRatings / numRatings;
}
void News::rateNews(vector<News>& newsRef, string userName) {
    if (news.empty()) {
        cout << "Sorry :( There Isn't any News Right Now\n";
        return;
    }
    cout << "     ============    Here Is ALL News :)      ============    \n";
    for (int i = 0; i < newsRef.size(); i++)
    {
        cout << "[" << i + 1 << "]" << newsRef[i].title;
    }
    int index;
    do {
        cout << "Enter The News Number To Rate ( Or Enter -1 To Skip)\n";
        cin >> index;
    } while (index<-1 || index>newsRef.size());
    if (index == -1) {
        return;
    }
    index--;
    short  userRating;
    do {
        cout << "Enter Your Rating ( It Must Be Between 1 and 5 )\n";
        cin >> userRating;

    } while (userRating < 1 || userRating >5);
    newsRef[index].allRate.emplace(pair<string, int>(userName, userRating));
    newsRef[index].calculateAverageRate();
    cout << "Your rating has been added successfully." << endl;
}
void News::displayNewsByCategoryName(string categoryName){
        if (news.empty()) {
        cout << "Sorry :( There Isn't any News Right Now\n";
        return;
    }
    bool is_found = false;
    transform(categoryName.begin(), categoryName.end(), categoryName.begin(), ::tolower);
    for(auto it:news){
        transform(it.category.begin(), it.category.end(), it.category.begin(), ::tolower);
        if (it.category == categoryName) {
            is_found = true;
            break;
        }
    }
    if(is_found){
        cout << "     ============    Here Is ALL "<< categoryName<<" News :)      ============    \n";
        for(auto it :news){
            if (it.category == categoryName) {
            cout << "\nTitle: " << it.title << endl;
            cout << "Description: " << it.description   << endl; 
            cout << "Date: " << it.date << endl;
            cout << "Category: " << it.category << endl;
            cout << "Rate: " << it.rate << endl;
            cout << "             =========================                       \n";
            }
        }
    }
    else{
        cout << "sorry :( This Is Category Is Not Exist\n";
    }
}
float News::getAverageRateByTitle(string target_title){
    if (news.empty()) {
        cout << "Sorry :( There Isn't any News to display rate\n";
        return -1.0f;
    }
    bool is_found = false;
    transform(target_title.begin(), target_title.end(), target_title.begin(), ::tolower);
    for(auto it:news){
        transform(it.title.begin(), it.title.end(), it.title.begin(), ::tolower);
        if (target_title == it.title) {
            is_found = true;
            break;
        }
        if(is_found){
            for(auto it :news){
                if (it.title == it.title) {
                    int totalRatings = 0;
                    int numRatings = it.allRate.size();
                    if (numRatings == 0) {
                        return 0.0f;
                    }
                    for (auto it2 : it.allRate) {
                        totalRatings += it2.second;
                    }
                    return (float)totalRatings / numRatings;
                    break;
                }
        }
        } else{
            cout << "sorry :( This Is title Is Not Exist\n";
            return -1.0f;
        }
    }
}

//**************************************************************************
float News::getRate()
{
    return this->rate;
}

string News::getTitle()
{
    return this->title;
}

string News::getDescription()
{
    return this->description;
}

string News::getCategory()
{
    return this->category;
}

string News::getDate()
{
    return to_string(this->date->tm_mday) + "/" + to_string(this->date->tm_mon + 1) + "/" + to_string(this->date->tm_year + 1900);
}
