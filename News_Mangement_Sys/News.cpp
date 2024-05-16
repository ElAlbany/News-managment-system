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
vector<News> News::valid;


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

void News::rateNews(string userName) {

    if (News::valid.empty()) {
        cout << "Sorry There Aren't any News Right Now\n";
        return;
    }
    cout << "Here Are All The articles :\n\n";
    for (int i = 0; i < News::valid.size(); i++) {
        cout << "[" << i + 1 << "] " << News::valid[i].title <<"\n";
    }
    int index;
    cout << "Enter The Article Number To Rate It ( Or Enter -1 to Skip) : ";
again:
    cin >> index;
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');
    if ((index <= 0 && index != -1) || index > News::valid.size()) {
        cout << "Please Enter a Vaild Article Number to Rate (or Rnter -1 to Skip) : ";
        goto again;
    }
    if (index == -1) {
        return;
    }
    short userRating;
    do {
        cout << "Enter Your Rating ( It Must Be Between 1 and 5 ) : ";
        cin >> userRating;
        cin.fail();
        cin.clear();
        cin.ignore(256, '\n');
    } while (userRating < 1 || userRating > 5);

    for (int i = 0; i < news.size(); i++) {
        if (news[i].getTitle().compare(News::valid[index-1].getTitle()) == 0) {
            news[i].allRate.erase(userName);
            news[i].allRate.emplace(pair<string, int>(userName, userRating));
            news[i].calculateAverageRate();
            News::valid[index - 1].rate = news[i].rate;
        }
    }
    if (News::valid[index - 1].rate != 0 && News::valid[index - 1].rate < 2) {
        auto it = News::valid.begin();
        advance(it, index - 1);
        News::valid.erase(it);
    }
    cout << "Your rating has been added successfully";
    system("pause");
}

void News::displayNewsByCategoryName(string categoryName) {
    if (valid.empty()) {
        cout << "Sorry There Aren't any Articles Right Now\n";
        return;
    }
    bool is_found = false;
    for (auto it : categories) {
        if (Utility::toLower(it) == Utility::toLower(categoryName)) {
            is_found = true;
            break;
        }
    }
    bool catNewsFound = false;
    int counter = 1;
    if (is_found) {
        for (auto it : valid) {
            if (Utility::toLower(it.category) == Utility::toLower(categoryName)) {
                catNewsFound = true;
                break;
            }
        }
        if (!catNewsFound) {
            cout << "\nSorry There Are No News For This Category Right Meow\n";
        }
        else {
            cout << "\nHere Are All The " << categoryName << " News : \n\n";
            for (auto it : valid) {
                if (Utility::toLower(it.category) == Utility::toLower(categoryName)) {
                    catNewsFound = true;
                    cout << "[" << counter++ << "] ";
                    it.displayPost();
                }
            }
        }
    }
    else {
        cout << "Sorry This Category Doesn't Exist\n";
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
        cout << "There Are No Articles Right Now \n";
        system("pause");
        return;
    }
    cout << "Here Are All The Articles :\n\n";
    if (user == 0) { // user
        if (sortedBy == "Date") {
            sort(News::valid.begin(), News::valid.end(), News::sortNewsByDate);
        }
        else {
            sort(News::valid.begin(), News::valid.end(), News::sortNewsByRating);
        }
        for (int i = 0; i < News::valid.size(); i++)
        {
            cout << "[" << i + 1 << "] ";
            News::valid[i].displayPost();
        }
    }
    else { // admin
        if (sortedBy == "Date") {
            sort(News::news.begin(), News::news.end(), News::sortNewsByDate);
        }
        else {
            sort(News::news.begin(), News::news.end(), News::sortNewsByRating);
        }
        if (details == "Details") {
            for (int i = 0; i < News::news.size(); i++)
            {
                cout << "[" << i + 1 << "] ";
                news[i].displayPost();
            }
        }
        else {
            for (int i = 0; i < News::news.size(); i++)
            {
                cout << "[" << i + 1 << "] " << news[i].title << "\n";
            }
        }
    }
}

vector<News> News::serachNews(string description_key) { // search by description and title

    int N = valid.size();
    vector<string> keywords = Utility::getKeyWords(description_key); // get all keywords in the search text
    for (auto& word : keywords) {
        word = Utility::toLower(word);
    }

    vector<pair<News, int>> searching_result;
    vector<bool>taken(N + 7, 0);
    unordered_map<int, int> loc;
    int year, month, day;

    for (int i = 0; i < N; i++) {

        auto news_post = valid[i];
        string lowerDescription = Utility::toLower(news_post.getDescription());
        string lowerTitle = Utility::toLower(news_post.getTitle());
        string date = news_post.getDate().fullDate('/');
        Utility::getDateOrder(date,year,month,day);
        string reverseDate = Utility::toString(day) + '/' + Utility::toString(month) + '/' + Utility::toString(year);;
        for (auto word : keywords) {
            if (lowerDescription.find(word) != string::npos || // search in title, description and date
                lowerTitle.find(word) != string::npos ||
                date.find(word) != string::npos ||
                date.compare(word) == 0 || 
                reverseDate.compare(word) == 0 ||
                reverseDate.find(word) != string::npos){

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
    cout << "======================================================================================================================\n";
}

void News::displayCategories()
{
    if (News::categories.size() == 0) {
        cout << "\nThere are No Categories Right Now \n";
        system("pause");
        return;
    }
    cout << "\nHere Are All The Categories :\n\n";
    for (int i = 0; i < News::categories.size(); i++)
    {
        cout << "[" << i + 1 << "] " << News::categories[i] << "\n";
    }

}

/////////////////////////////////////////// Update Menu ///////////////////////////////////////////

void News::updateMenu()
{   
    if (News::news.size() == 0)
    {
        cout << "There Are No Articles Right Now \n";
        return;
    }
    News::displayAllNews("Date",1,"Details");
    cout << "Enter Number To Edit in Article Information or -1 to Skip : ";
    int num;
again:
    cin >> num;
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');
    if (num == -1) {
        return;
    }
    if (num > News::news.size() || num <= 0)
    {
        cout << "You Have Entered an Invalid Number, Please Enter a Valid One : ";
        goto again;
    }

    cout << "Enter One of The Operations Below or -1 to Skip : \n\n";
    cout << "[1] Title\n\n";
    cout << "[2] Description\n\n";
    cout << "[3] Category\n\n";
    cout << "[4] Date\n\n";
    int choice;
again1:
    cout << "Choice : ";
    cin >> choice;
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');
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
        cout << "You Have Entered Invalid Choice Please Try Again\n";
        goto again1;
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
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');
    if (choice > News::categories.size() || choice <= 0)
    {
        cout << "You Have Entered Invalid Number Please Enter a Vaild One\n";
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
    cout << "\n[1] Add Comment\n\n";
    cout << "[2] Display Comments\n\n";
    cout << "[3] Return \n\n";
again:
    int choice;
    cout << "\nChoice : ";
    cin >> choice;
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');
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
        cout << "You Have Entered Invalid Choice Please Try Again\n\n";
        goto again;
    }
}

void News::removeComment(int index)
{ 
    cout << "If You Want to Remove One of Your Comments Enter It's Number or -1 to Skip : ";
again:
    int commentNum;
    cin >> commentNum;
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');
    if (commentNum == -1)
    {
        return;
    }
    if (commentNum <= 0 || commentNum > News::valid[index].comments.size())
    {
        cout << "Invalid Number, Please Enter Valid Number or -1 to Skip : ";
        goto again;
    }
    if (News::valid[index].comments[commentNum-1].getUserName() != User::currentUsername)
    {
        cout << "You Can't Remove The Comment, Try Again or Enter -1 to Skip : ";
        goto again;
    }
    else
    {   
        News::valid[index].comments.erase(News::valid[index].comments.begin() + commentNum - 1);
        for (int i = 0; i < News::news.size(); i++) {
            if (News::news[i].getTitle().compare(News::valid[index].getTitle()) == 0) {
                News::news[i].comments.erase(News::news[i].comments.begin() + commentNum - 1);
            }
        }
        cout << "Comment Removed Successfully\n";
    }
}

void News::addComment()
{
    int choice;
    cout << "Enter The Number of The Article You Want to Add a Comment to or -1 to Skip : ";
again:
    cin >> choice;
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');
    if (choice == -1)
        return;
    if (choice <= 0 || choice > News::valid.size())
    {
        cout << "You Have Entered an Invalid Number, Please Enter a Valid One : ";
        goto again;
    }
    string comment;
    cout << "Enter Your Comment : ";
    cin.ignore();
    getline(cin >> ws, comment);
    News::valid[choice - 1].comments.push_back(Comment(User::currentUsername, comment));
    for (int i = 0; i < News::news.size(); i++) {
        if (News::valid[choice - 1].getTitle().compare(News::news[i].getTitle()) == 0) {
            News::news[i].comments.push_back(Comment(User::currentUsername, comment));
        }
    }
    cout << "Comment Added Successfully\n";
    system("pause");
}
void News::displayComments()
{
    cout << "Enter Number of an Article to Display Its Comments or -1 to Skip : ";
again:
    int num;
    cin >> num;
    cin.fail();
    cin.clear();
    cin.ignore(256, '\n');

    if (num == -1)
    {
        return;
    }
    if (News::valid[num - 1].comments.size() == 0)
    {
        cout << "There Are No Comments For This Article\n";
        system("pause");
        return;
    }
    if (num <= 0 || num > News::valid.size())
    {
        cout << "You Have Entered Invalid Number, Please Enter Valid Number \n";
        goto again;
    }
    for (int i = 0; i < News::valid[num - 1].comments.size(); i++)
    {
        cout << "\n[" << i + 1 << "]";
        News::valid[num - 1].comments[i].display();
    }
    News::removeComment(num - 1);
    system("pause");
}

void Comment::display() {
    cout << " [User : " << getUserName() << "]\n|----> " << getBody() << "\n\n";
}
//////////////////////////////////////////////////Comment class/////////////////////////////////////////////////////////
