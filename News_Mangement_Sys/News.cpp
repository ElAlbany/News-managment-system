#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // for the ctime warning
#endif

#include <iostream>
#include <ctime>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include "News.h"
#include "Date.h"
#include "Utility.h"
using namespace std;

// main data structures to store all news (static definition)
vector<News> News::news;
vector<string> News::categories;
map<int,bool> News::valid;


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
        cout << "Sorry There Aren't any News Right Now\n";
        return;
    }
    cout << "Here Are All The articles :\n";
    for (int i = 0; i < newsRef.size(); i++) {
        cout << "[" << i + 1 << "]" << newsRef[i].title <<"\n";
    }
    int index;
    cout << "Enter The Article Number To Rate It ( Or Enter -1 to Skip) : ";
again:
    cin >> index;
    if ((index <= 0 && index != -1) || index > newsRef.size()) {
        cout << "Please Enter a Vaild Article Number to Rate (or Rnter -1 to Skip) : ";
        goto again;
    }
    if (index == -1) {
        return;
    }
    index--;
    short userRating;
    do {
        cout << "Enter Your Rating ( It Must Be Between 1 and 5 ) : ";
        cin >> userRating;
    } while (userRating < 1 || userRating > 5);

    newsRef[index].allRate.erase(userName);
    newsRef[index].allRate.emplace(pair<string, int>(userName, userRating));
    newsRef[index].calculateAverageRate();
    cout << "Your rating has been added successfully." << endl;
}

void News::displayNewsByCategoryName(string categoryName) {
    if (news.empty()) {
        cout << "Sorry There Aren't any Articles Right Now\n";
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
        cout << "\nhere are all the " << categoryName << " News : \n\n";
        for (auto it : news) {
            if (it.category == categoryName) {
                it.displayPost();
            }
        }
    }
    else {
        cout << "sorry this category doesn't exist\n";
    }
    system("pause");
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

float News::getRate() const {
    return this->rate;
}

Date News::getDate() const {
    return this->date;
}

void News::displayAllNews(string sortedBy, int user, string details) {
    if (News::news.size() == 0)
    {
        cout << "there are no articles right now \n";
        system("pause");
    }
    if (sortedBy == "Date") {
       sort(News::news.begin(), News::news.end(), News::sortNewsByDate);
    }
    else {
        sort(News::news.begin(), News::news.end(), News::sortNewsByRating);
    }
    cout << "here are all the articles :\n\n";
    for (int i = 0; i < News::news.size(); i++)
    {
        if (user == 0) {
            auto it = User::users[User::currentUsername].spamNews.find(News::news[i].getTitle());
            if (it != User::users[User::currentUsername].spamNews.end()) {
                News::valid[i+1] = false;
                continue;
            }
            float rate = News::news[i].getRate();

            if (rate >= 2.0 || rate == 0.0)
            {
                cout << "[" << i + 1 << "] ";
                news[i].displayPost();
                News::valid[i + 1] = true;
            }
        }
        else {
            if (details == "Details") {
                cout << "[" << i + 1 << "] ";
                news[i].displayPost();
            }
            else {
                cout << "[" << i + 1 << "] " << news[i].title << "\n";
            }
        }
    }
}

vector<News> News::serachNews(string description_key) { // search by description and title

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
            if (lowerDescription.find(word) != string::npos || // search in title and description
                lowerTitle.find(word) != string::npos ||
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

void News::displayPost() {
    cout << "\nTitle: " << this->title << endl;
    cout << "Description: " << this->description << endl;
    cout << "Date: " << this->date << endl;
    cout << "Category: " << this->category << endl;
    cout << "Rate: " << this->rate << endl;
    cout << "========================================================================================================================\n\n";
}

void News::displayCategories()
{
    if (News::categories.size() == 0) {
        cout << "There are No Categories Right Now \n";
        system("pause");
        return;
    }
    cout << "Here Are All The Categories :\n\n";
    for (int i = 0; i < News::categories.size(); i++)
    {
        cout << "[" << i + 1 << "]" << News::categories[i] << "\n";
    }

}

/////////////////////////////////////////// Update Menu ///////////////////////////////////////////

void News::updateMenu()
{   
    if (News::news.size() == 0)
    {
        cout << "there is no articles right now \n";
        return;
    }
    News::displayAllNews("Date",1,"Details");
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
again:
    cout << "Number : ";
    cin >> choice;
    if (choice == -1)
        return;
    else if (choice == 1)
    {
        cout << "Enter The New Title : ";
        string newTitle;
        cin.ignore();
        getline(cin, newTitle);
        News::news[num - 1].updateNewsTitle(newTitle);
        cout << "Title Updated Successfully\n";
        system("pause");
    }
    else if (choice == 2)
    {
        cout << "Enter The New Description : ";
        string newDescription;
        cin.ignore();
        getline(cin, newDescription);
        News::news[num - 1].updateNewsDescription(newDescription);
        cout << "Description Updated Successfully\n";
        system("pause");
    }
    else if (choice == 3)
    {
        News::news[num - 1].updateNewsCategory();
    }
    else if (choice == 4)
    {
        cout << "Enter The New Date : ";
        string newDate;
        cin >> newDate;
        Utility::dateHandler(newDate);
        News::news[num - 1].updateNewsDate(Date::fromString(newDate));
        cout << "Date Updated Successfully\n";
        system("pause");
    }
    else {
        cout << "you have entered invalid choice please try again\n";
        goto again;
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
    cout << "\n\nEnter The Number of Category to replace it with the Current One : ";
    int choice;
again:
    cin >> choice;
    if (choice > News::categories.size() || choice <= 0)
    {
        cout << "you have entered invalid number please enter a vaild one\n";
        goto again;
    }
    this->category = News::categories[choice - 1];
    cout << "Category Updated Successfully\n";
    system("pause");
}

void News::updateNewsDate(Date new_date) { // later
    this->date = new_date;
}

//////////////////////////////////////////////////Comment class/////////////////////////////////////////////////////////
Comment::Comment(const string& _user_name, const string& _body) {
    this-> commentUserName = _user_name;
    this->commentBody = _body;
  
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

void News::commentMenu()
{
    News::displayAllNews("Date", 0, "Details");
again:
    cout << "[1] add comment\n";
    cout << "[2] display comments\n";
    cout << "[3] return \n";
    int choice;
    cin >> choice;
    if (choice == 1)
        News::addComment();
    else if (choice == 2)
    {
      News::displayComments();
    }
    else if (choice == 3)
    {
        return;
    }
    else
    {
        cout << "you have entered invalid choice please try again\n";
        goto again;
    }
}

void News::removeComment(int index)
{ 
    cout << "if you want to remove one of your comments enter it's number or -1 to skip\n";
    again:
    int commentNum;
    cin >> commentNum;
    if (commentNum == -1)
    {
        return;
    }
    if (commentNum <= 0 || commentNum > News::news[index].comments.size())
    {
        cout << "invalid number , please enter valid number or -1 to skip\n";
        goto again;
    }
    if (News::news[index].comments[commentNum-1].getUserName() != User::currentUsername)
    {
        cout << "you can't remove the comment, try again or enter -1 to skip \n";
        goto again;
    }
    else
    {   
        News::news[index].comments.erase(News::news[index].comments.begin() + commentNum - 1);
    }
}

void News::addComment()
{
again:
    int choice;
    cout << "enter the number of the article you want to add a comment to or -1 to skip\n";
    cin >> choice;
    if (choice == -1)
        return;
    if (choice <= 0 || choice > News::news.size() || News::valid[choice] == false)
    {
        cout << "you have entered an invalid number, please enter a valid one \n";
        goto again;
    }
    string comment;
    cin.ignore();
    getline(cin >> ws, comment);
    News::news[choice - 1].comments.push_back(Comment(User::currentUsername, comment));
    cout << "comment added successfully\n";
    system("pause");
}
void News::displayComments()
{
again:
    cout << "enter number of an article to display its comments  or -1 to skip\n";
    int num;
    cin >> num;

    if (num == -1)
    {
        return;
    }
    if (News::news[num - 1].comments.size() == 0)
    {
        cout << "there are no comments for this article\n";
        system("pause");
        return;
    }
    if (num <= 0 || num > News::news.size() || News::valid[num] == false)
    {
        cout << "you have entered invalid number , please enter valid number \n";
        goto again;
    }
    for (int i = 0; i < News::news[num - 1].comments.size(); i++)
    {
        cout << "[" << i + 1 << "]";
        News::news[num - 1].comments[i].display();
    }
    News::removeComment(num - 1);
    system("pause");
}

void Comment::display() {
    cout << " [User : " << getUserName() << "]\n|----> " << getBody() << "\n\n";
}
//////////////////////////////////////////////////Comment class/////////////////////////////////////////////////////////
