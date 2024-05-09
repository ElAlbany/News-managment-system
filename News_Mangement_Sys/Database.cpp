#include "Database.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include <iostream>
#include "User.h"
#include "News.h"
#include "Date.h"
using namespace std;

void Database::write()
{
    // Saving users
    ofstream userFile("users.txt");
    if (!userFile.is_open()) {
        cerr << "Error opening users.txt for writing.\n";
        return;
    }
    for (auto& pair : User::users) {
        User& user = pair.second;
        userFile << user.Username << ","
            << user.Password << ","
            << user.Email << ","
            << user.spamCount << ",";

        // Saving spam news for this user
        for (auto& newsTitle : user.spamNews) {
            userFile << newsTitle << ";";
        }
        userFile << "\n"; // end of line for one user
    }
    userFile.close();

    /////////////////////////////////////////////////////


    // Saving bookmarks
    ofstream bookmarkFile("bookmarks.txt");
    if (!bookmarkFile.is_open()) {
        cerr << "Error opening bookmarks.txt for writing.\n";
        return;
    }
    for (const auto& pair : User::bookmarks) {
        bookmarkFile << pair.first; // Username
        for (const auto& site : pair.second) {
            bookmarkFile << " " << site;
        }
        bookmarkFile << "\n";
    }
    bookmarkFile.close();



    ///////////////////////////////////

       /////////////////////////////////////////////////////


    // Saving notifications
    ofstream notifications("notifications.txt");
    if (!notifications.is_open()) {
        cerr << "Error opening notifications.txt for writing.\n";
        return;
    }
    for (const auto& pair : User::interestedCategories) {
        notifications << pair.first; // Username
        for (const auto& site : pair.second) {
            notifications << " " << site;
        }
        notifications << "\n";
    }
    notifications.close();



    ///////////////////////////////////

    //News

    ////////////////////////////////////
    ofstream outFile("News.txt");
    if (!outFile) {
        cerr << "Error opening file for writing: " << "News.txt" << endl;
        return;
    }

    for (News& news : News::news) {
        outFile << news.getTitle() << "\n";
        outFile << news.getDescription() << "\n";
        outFile << news.getDate() << "\n";  // assuming Date has a toString() method
        outFile << news.getCategory() << "\n";
        outFile << news.getRate() << "\n";

        // Save ratings
        outFile << news.allRate.size() << "\n";
        for (const auto& rate : news.allRate) {
            outFile << rate.first << " " << rate.second << "\n";
        }

        // Save comments
        outFile << news.comments.size() << "\n";
        for (const Comment& comment : news.comments) {
            outFile << comment.getUserName() << "\n" << comment.getBody() << comment.getDate() << "\n";
        }
    }
    outFile.close();

    ofstream ooutFile("category.txt");
    if (!ooutFile) {
        cerr << "Error opening file for writing: " << "category.txt" << endl;
        return;
    }

    for (string& category : News::categories) {
        ooutFile << category << "\n";
    }
    ooutFile.close();
}

void Database::read()
{
    ifstream inFile("users.txt");
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    User::users.clear(); // Clear existing users
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string username, password, email, spamCountStr, spamNewsStr;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
       
        getline(ss, spamCountStr, ',');
        getline(ss, spamNewsStr);

        User user;
        user.Username = username;
        user.Password = password;
        user.Email = email;
        user.spamCount = stoi(spamCountStr);

        // Extract spam news
        stringstream newsStream(spamNewsStr);
        string newsTitle;
        while (getline(newsStream, newsTitle, ';')) {
            if (!newsTitle.empty()) {  // handle the last trailing semicolon
                user.spamNews.insert(newsTitle);
            }
        }

        User::users[username] = user;
    }
    inFile.close();



    ////////////////////////////////////////////////////

    User::bookmarks.clear();
    // Loading bookmarks
    ifstream bookmarkFile("bookmarks.txt");
    if (!bookmarkFile.is_open()) {
        cerr << "Error opening bookmarks.txt for reading.\n";
        return;
    }
    while (std::getline(bookmarkFile, line)) {
        istringstream iss(line);
        string username;
        iss >> username;
        string site;
        while (iss >> site) {
            User::bookmarks[username].insert(site);
        }
    }
    bookmarkFile.close();

    ////////////////////////////////


     ////////////////////////////////////////////////////

    User::interestedCategories.clear();
    // Loading notifications
    ifstream notifications("notifications.txt");
    if (!notifications.is_open()) {
        cerr << "Error opening notifications.txt for reading.\n";
        return;
    }
    while (std::getline(notifications, line)) {
        istringstream iss(line);
        string username;
        iss >> username;
        string site;
        while (iss >> site) {
            User::interestedCategories[username].insert(site);
        }
    }
    notifications.close();

    ////////////////////////////////

     //news

     ///////////////////////////////

    ifstream innFile("News.txt");
    if (!innFile) {
        cerr << "Error opening file for reading: " << "News.txt" << endl;
        return;
    }

    News::news.clear();
    while (getline(innFile, line) and !line.empty()) {
        string title = line;
        getline(innFile, line);
        string description = line;
        getline(innFile, line);
        string dateStr = line;  // You'll need to convert this back to a Date
        getline(innFile, line);
        string category = line;
        getline(innFile, line);
        float rate = stof(line);

        News newsItem(title, description, category, rate, Date::fromString(dateStr)); // Assuming a constructor or method to set these

        // Read rates
        size_t ratesCount;
        innFile >> ratesCount;
        innFile.ignore(); // to skip newline
        for (size_t i = 0; i < ratesCount; ++i) {
            getline(innFile, line);
            stringstream ss(line);
            string username;
            int userRate;
            ss >> username >> userRate;
            newsItem.allRate.insert({ username, userRate });
        }
 
        // Read comments
        size_t commentsCount;
        innFile >> commentsCount;
        innFile.ignore(); // to skip newline
        for (size_t i = 0; i < commentsCount; ++i) {
            getline(innFile, line);
            string userName = line;
            getline(innFile, line);
            string comment = line;
            getline(innFile, line);
            string comment_date = line;
            newsItem.comments.push_back(Comment(userName, comment, Date(comment_date)));
        }

    }
    innFile.close();
    ifstream innnFile("category.txt");
    if (!innnFile) {
        cerr << "Error opening file for reading: " << "category.txt" << endl;
        return;
    }

    News::categories.clear();
    string category;
    while (getline(innnFile, category)) {
        News::categories.push_back(category);
    }
    
    Utility::DM("database", "news read done"); // debug message
    innnFile.close();
}
