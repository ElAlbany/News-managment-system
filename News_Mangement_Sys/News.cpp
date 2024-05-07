#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // for the ctime warning
#endif

#include <iostream>
#include <ctime>
#include <vector>
#include <set>
#include "News.h"
#include "Date.h"
#include "Utility.h"
#include <unordered_map>
#include <algorithm>
using namespace std;

// main data structures to store all news (static definition)
vector<News> News::news;
vector<string> News::categories;
set<int> News::valid;
map<int, vector<Comment>> News::saveComments;

// chaining constructor
News::News(string title, string description, string category, float rate, Date date) {
    this->title = title;
    this->description = description;
    this->category = category;
    this->rate = rate;
    this->date = date;
    News::news.push_back(*this);
}

News::News(string title, string description, string category, float rate) : News(title, description, category, rate, Date::getCurrentDate('/')) {}

News::News(string title, string description, string category) : News(title, description, category, 0.f) {}

News::News(string title, string description) : News(title, description, "NO_CATEGORY_SPECIFIED") {}



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
    for (auto it : news) {
        transform(it.category.begin(), it.category.end(), it.category.begin(), ::tolower);
        if (it.category == categoryName) {
            is_found = true;
            break;
        }
    }
    if (is_found) {
        cout << "     ============    Here Is ALL " << categoryName << " News :)      ============    \n";
        for (auto it : news) {
            if (it.category == categoryName) {
                cout << "\nTitle: " << it.title << endl;
                cout << "Description: " << it.description << endl;
                //cout << "Date: " << it.date.fullDate << endl;
                cout << "Category: " << it.category << endl;
                cout << "Rate: " << it.rate << endl;
                cout << "             =========================                       \n";
            }
        }
    }
    else {
        cout << "sorry :( This Is Category Is Not Exist\n";
    }
}
//**************************************************************************




float News::getRate() const {
    return this->rate;
}
string News::getTitle() const {
    return this->title;
}
string News::getDescription() const {
    return this->description;
}
string News::getCategory() const {
    return this->category;
}

void News::displayLatestNews() {
    sort(News::news.begin(), News::news.end(), News::sortNewsByDate);
    for (int i = 0; i < (int)News::news.size(); i++) {
        cout << "[" << i + 1 << "] ";
        news[i].displayNewsPost();

        saveComments.insert({ i + 1, news[i].comments });
    }
    
    cout << endl;
    displayCommentsOnUserChoice();
    saveComments.clear();
  
}


void News::displayTrendingNews() {

    sort(News::news.begin(), News::news.end(), News::sortNewsByRating);
    for (int i = 0; i < (int)News::news.size(); i++) {

        // display post
        cout << "[" << i+1 << "] ";
        news[i].displayNewsPost();

        // save comments for user choice after the displaying
        saveComments.insert({ i + 1, news[i].comments });
      
    }
    cout << endl;
    News::displayCommentsOnUserChoice(); // make the user choose the post he want to display the comments
    saveComments.clear();

}


bool News::displayAllNews() {
    if (News::news.size() == 0)
    {
        cout << "there is no news right now \n";
        return false;
    }
    cout << "here is all the news\n";
    cout << "\n";
    for (int i = 0; i < News::news.size(); i++)
    {
        cout << "[" << i + 1 << "] " << news[i].getTitle() << "\n";
    }
    return true;
}
void News::displayNewsForUser() {
    if (News::news.size() == 0)
    {
        cout << "there is no news right now \n";
        return;
    }
    cout << "some content will be hidden for you if was needed\n";
    cout << "here is all the news\n";
    cout << "\n";
   
    for (int i = 0; i < News::news.size(); i++)
    {
        auto it = User::users[User::currentUsername].spamNews.find(news[i].getTitle());
        if (it != User::users[User::currentUsername].spamNews.end())
            continue;
        float rate = News::news[i].getRate();
        if (rate >= 2.0 || rate == 0.0)
        {
            cout << "[" << i + 1 << "] ";
            news[i].displayNewsPost();
            News::valid.insert(i+1);
        }
    }

   
}
bool  News::validChoice(int choice)
{
    auto it = News::valid.find(choice);
    if (it == News::valid.end())
        return false;
    return true;
}



Date News::getDate() const {
    return this->date;
}

/////////////////////////////////////// serachNews //////////////////////////////////////////// Optimization later
vector<News> News::serachNews(string description_key) { // search by descroption for now , title later

    int N = news.size();
    vector<string> keywords = Utility::getKeyWords(description_key); // get all keywords in the search text
    for (auto& word : keywords) {
        word = Utility::toLower(word);
    }



    vector<pair<News, int>> searching_result;
    vector<bool>taken(N + 7, 0);
    unordered_map<int, int> loc;

    for (int i = 0; i < N; i++) {

        auto news_post = news[i];
        string lowerDescription = Utility::toLower(news_post.getDescription());
        string lowerTitle = Utility::toLower(news_post.getTitle());
        for (auto word : keywords) {
            if (lowerDescription.find(word + " ") != string::npos || // search in title and description
                lowerDescription.find(" " + word) != string::npos ||
                lowerTitle.find(word + " ") != string::npos ||
                lowerTitle.find(" " + word) != string::npos ||
                lowerTitle == word) {

                if (!taken[i]) {  // if taken i don't need to take it again (no dublicate posts)
                    loc[i] = searching_result.size(); // saving the index of the current pushed post to be used later
                    searching_result.push_back({ news_post, 1 });
                    taken[i] = true; // mark as taken 

                }
                else {
                    // the bigger the score for each post the more to be displayed at the list beginning
                    searching_result[loc[i]].second++;
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
    cout << "Date: " << this->date.fullDate('/') << endl;
    cout << "Category: " << this->category << endl;
    cout << "Rate: " << this->rate << endl;
    cout << "             =========================                       \n";
}

////////////////////////////////////////Updating///////////////////////////////////////////

void News::displayCategories()
{
    if (News::categories.size() == 0) {
        cout << "there is no categories right now \n";
        return;
    }
    cout << "here is all of categories :\n";
    for (int i = 0; i < News::categories.size(); i++)
    {
        cout << "[" << i + 1 << "]" << News::categories[i] << "\n";
    }

}
void News::updateMenu()
{   
    if (News::news.size() == 0)
    {
        cout << "there is no news right now \n";
        return;
    }
    News::displayAllNews();
    cout << "enter number to edit in information or -1 to skip\n";
    int num;
    cin >> num;
    if (num == -1) {
        return;
    }
    if (num > News::news.size() || num <= 0)
    {
        cout << "you have entered invalid number \n";
        return;
    }

    cout << "enter one of the operations below or -1 to skip\n";
    cout << "[1]title\n";
    cout << "[2]description\n";
    cout << "[3]category\n";
    cout << "[4]date\n";
    int choice;
    cin >> choice;
    if (choice == -1)
        return;
    else if (choice == 1)
    {
        string newTitle;
        cin.ignore();
        getline(cin, newTitle);
        News::news[num - 1].updateNewsTitle(newTitle);
    }
    else if (choice == 2)
    {
        string newDescription;
        cin.ignore();
        getline(cin, newDescription);
        News::news[num - 1].updateNewsDescription(newDescription);
    }
    else if (choice == 3)
    {
        News::news[num - 1].updateNewsCategory();
    }
    else if (choice == 4)
    {
        string newDate;
        cin >> newDate;
        News::news[num - 1].updateNewsDate(newDate);
    }

}
void News::updateNewsTitle(string new_title) {
    this->title = new_title;
}

void News::updateNewsDescription(string new_description) {
    this->description = new_description;
}

void News::updateNewsCategory() {

    displayCategories();
    cout << "\n\nEnter one to replace it with the current\n";
    int choice;
    cin >> choice;
    if (choice > News::categories.size() || choice <= 0)
    {
        cout << "you have entered invalid number \n";
        return;
    }
    this->category = News::categories[choice - 1];
}

void News::updateNewsDate(Date new_date) { // later
    this->date = new_date;
}


void News::displayNewsPost() const {
    cout << this->title << " : " << this->description
            << " \n\tDate : " << this->date << " \n\tRating : " << this->rate
            << " \n\tCategory : " << this->category << endl;
}

//////////////////////////////////////////////////Comment class/////////////////////////////////////////////////////////
Comment::Comment(const string& _user_name, const string& _body, const Date& _date) {
    this-> commentUserName = _user_name;
    this->commentBody = _body;
    this->commentDate = _date;
}

void Comment::setCommentBody(const string& new_body) {
    this->commentBody = new_body;
}

void Comment::setUserName(const string& new_user_name) {
    this->commentUserName = new_user_name;
}

string Comment::getUserName() const {
    return this->commentUserName;
}

string Comment::getBody() const {
    return this->commentBody;
}

Date Comment::getDate() const {
    return this->commentDate;
}

void News::addComment()
{
    string comment;
    getline(cin >> ws, comment);
    comments.push_back(Comment(User::currentUsername, comment, Date::getCurrentDate('/')));
}
void News::displayCommentsOnUserChoice()
{
    cout << "\t\tEnter the post for which you want the comments (other number to continue..): \n";
    for (auto p : saveComments) {
        cout << "Post (" << p.first << ')' << '\n';
    }

again:
    cout << "-> "; 
    string s;
    cin.ignore();
    cin >> s;
    int choice = (s[0] - '0'); // so to prevent infinite loop on invalid inputs
    if (s.size() == 1 and saveComments.find(choice) != saveComments.end()) { // if post number exist in the map

        if (saveComments[choice].empty()) cout << "[no comments]\n";
        else
        {
            cout << "--------------Comments----------------------------\n";
            for (int i = 0; i < saveComments[choice].size(); i++) {
                saveComments[choice][i].display();
            }
            cout << "--------------------------------------------------\n";
        }
        
        goto again;
    }
    else goto done;

done: {saveComments.clear(); }
    
 
}

void Comment::display() {
    cout << "| [User : " << getUserName() << " - " << getDate() << "]" << "\n|----> " << getBody() << "\n|\n";
}
//////////////////////////////////////////////////Comment class/////////////////////////////////////////////////////////
