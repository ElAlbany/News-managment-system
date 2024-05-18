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
        userFile << user.getUsername() << ","
            << user.getPassword() << ","
            << user.getEmail() << "\n";
          
    }
    userFile.close();

    ////////////////////////////spam////////////////////////////

    // Saving spam
    ofstream spam("spam.txt");
    if (!spam.is_open()) {
        cerr << "Error opening spam.txt for writing.\n";
        return;
    }
    spam << User::spamNews.size() << "\n";
    for (auto& user : User::spamNews) {
        spam << user.first << "\n";
        spam << user.second.size() << "\n";
        for (const string& Spam : user.second) {
            spam << Spam << "\n";
        }
    }
    spam.close();


    ////////////////////////////bookmark////////////////////////////


    // Saving bookmarks
    ofstream bookmarkFile("bookmarks.txt");
    if (!bookmarkFile.is_open()) {
        cerr << "Error opening bookmarks.txt for writing.\n";
        return;
    }
    bookmarkFile << User::bookmarks.size() << "\n";
    for (auto& user : User::bookmarks) {
        bookmarkFile << user.first << "\n";
        bookmarkFile << user.second.size() << "\n";
        for (const string& bookmark : user.second) {
            bookmarkFile << bookmark << "\n";
        }
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
        outFile << news.getSpamCount() << "\n";

        // Save ratings
        outFile << news.allRate.size() << "\n";
        for (const auto& rate : news.allRate) {
            outFile << rate.first << " " << rate.second << "\n";
        }

        // Save comments
        outFile << news.comments.size() << "\n";
        for (const Comment& comment : news.comments) {
            outFile << comment.getUserName() << "\n" << comment.getBody() << "\n";
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
        string username, password, email ;
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, '\n');

        User user;
        user.setUsername(username);
        user.setPassword(password);
        user.setEmail(email);
       
        User::users[username] = user;
    }
    inFile.close();



    ///////////////////////////spam///////////////////////////

    User::spamNews.clear();
    // Loading spam
    ifstream spam("spam.txt");
    if (!spam.is_open()) {
        cerr << "Error opening spam.txt for reading.\n";
        return;
    }
    size_t spamSize;
    spam >> spamSize;
    spam.ignore();
    for (int i = 0; i < spamSize; i++) {
        string username;
        getline(spam, line);
        username = line;
        int userSpamSize;
        spam >> userSpamSize;
        spam.ignore();
        for (int j = 0; j < userSpamSize; j++) {
            getline(spam, line);
            User::spamNews[username].insert(line);
        }
    }
    spam.close();

    ///////////////////////////bookmark///////////////////////////

    User::bookmarks.clear();
    // Loading bookmarks
    ifstream bookmarkFile("bookmarks.txt");
    if (!bookmarkFile.is_open()) {
        cerr << "Error opening bookmarks.txt for reading.\n";
        return;
    }
    size_t bookmarkSize;
    bookmarkFile >> bookmarkSize;
    bookmarkFile.ignore();
    for (int i = 0; i < bookmarkSize; i++) {
        string username;
        getline(bookmarkFile, line);
        username = line;
        int userBookmarksSize;
        bookmarkFile >> userBookmarksSize;
        bookmarkFile.ignore();
        for (int j = 0; j < userBookmarksSize; j++) {
            getline(bookmarkFile, line);
            User::bookmarks[username].insert(line);
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
        getline(innFile, line);
        int spamCount = stoi(line);

        News newsItem(title, description, category, rate, Date::fromString(dateStr), spamCount); // Assuming a constructor or method to set these

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
            News::news.back().allRate.insert({ username, userRate });
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
            News::news.back().comments.push_back(Comment(userName, comment));
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

    //Utility::DM("database", "news read done"); // debug message
    innnFile.close();
}
