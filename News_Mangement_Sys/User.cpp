#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include<regex>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime> 
#include "User.h"
#include "Utility.h"
#include "Style.h"

using namespace std;

map<string, User> User::users;
string User::currentUsername, User::currentPassword;
unordered_map<string, unordered_set<string>> User::bookmarks;
unordered_map<string, unordered_set<string>> User::interestedCategories;


// Constructors
User::User(string username, string password, string email) {
    this->Username = username;
    this->Password = password;
    this->Email = email;
    this->LoginAtempts = 2;
}
User::User() {
    this->Username = "";
    this->Password = "";
    this->LoginAtempts = 2;
}


// Getters
string User::getUsername() {
    return this->Username;
}

string User::getPassword() {
    return this->Password;
}

bool User::is_email_valid(string email) // regex to check if the email is vaild or not
{
    regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

void User::addCategory() {
    cout << "Enter The Name of The Category You Want to Add : ";
    string category;
    cin.ignore();
    getline(cin, category);
    category = Utility::toLower(category);
    for (int i = 0; i < News::categories.size(); i++) {
        if (category == News::categories[i]) {
            cout << "This Category Already Exists\n";
            system("pause");
            return;
        }
    }
    News::categories.push_back(category);
    cout << "Added Successfully\n";
    system("pause");
}
void User::addCategoryAuto(string cate) {
 
    for (int i = 0; i < News::categories.size(); i++) {
        if (cate == News::categories[i]) {
            return;
        }
    }
    News::categories.push_back(cate);
}
void User::removeNews() {
    if (News::news.size() == 0) {
        cout << "There Are No Articles Right Now \n";
        return;
    }
    News::displayAllNews("Date",1,"NoDetails");
    cout << "\nPlease Select One of The Shown Above to Remove or Enter -1 to Skip : ";
    int num;
again:
    cin >> num;
    if (num == -1)
        return;
    if (num < 1 || num > News::news.size()) {
        cout << "You Have Entered an Invalid Number, Please Try Again : ";
        goto again;
    }
    News::news.erase(News::news.begin() + num - 1);
    cout << "Article Has Been Removed Successfully\n";
    system("pause");
}
void User::postNews() {
    string title, description,category ,date;
    cout << "Fulfill Required Information to Add The Article Into The System : \n\n";
    cout << "Enter Title : ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Description : ";   
    getline(cin, description);
    cout << "Enter Category : ";
    getline(cin, category);
    cout << "Enter Date (dd/mm/yyyy) or (yyyy/mm/dd) : ";
    cin >> date;

    Utility::dateHandler(date);
    News news1(title , description, Utility::toLower(category),0.0, Date::fromString(date));
    addCategoryAuto(Utility::toLower(category));
    User::emailInterestedUsers(Utility::toLower(category));

    cout << "Article Posted Successfuly\n";
    system("pause");
}
void User::getAverageRateByTitle() {
    if (News::news.size() != 0)
    {
        int num;
        do {
            cout << "\nEnter The Number of Article You Want to See Its Rate or -1 to Skip : ";
            cin >> num;
            if (num == -1)
                return;
        } while (num<1 || num>News::news.size());
        cout << "Rate : " << News::news[num - 1].getRate() << "\n";
        system("pause");
    }
    else {
        cout << "\nThere Are No Articles Right Now \n";
        system("pause");
        return;
    }
}
void User::bookmarkingMenu() {
    cout << "[1] Add Article to Your Favourite \n\n";
    cout << "[2] Delete Marked Article \n\n";
    cout << "[3] Display All Marked Articles \n\n";
    cout << "[4] Return \n\n";
    cout << "\nEnter Your Choice : ";
    int choice;
again:
    cin >> choice;
    if (choice == 1) {
        AddToBookmarks();
    }
    else if (choice == 2) {
        RemoveFromBookmarks();
    }
    else if (choice == 3) {
        PrintBookmarks();
    }
    else if (choice == 4) {
        return;
    }
    else {
        cout << "Please Select One of The Shown Operations Above : ";
        goto again;
    }
    system("pause");
}
void User::AddToBookmarks() {
    int num;
    News::displayAllNews("Date",0,"Details");
    cout << "Enter a Number : ";
    cin >> num;
    if (num < 1 || num > News::valid.size()) {
        cout << "You Have Entered a Wrong Number \n";
        return;
    }
    bool flag = User::IsInBookmarks(News::news[num - 1].getTitle());
    if (flag) {
        cout << "Bookmark Already Exists\n";
        return;
    }
    User::bookmarks[User::currentUsername].insert(News::news[num - 1].getTitle());
    cout << "Bookmark Added Successfully\n";
}
bool User::IsInBookmarks(string title) {
    return (User::bookmarks[User::currentUsername].find(title) != User::bookmarks[User::currentUsername].end());
}
void User::RemoveFromBookmarks() {
    User::PrintBookmarks();
    int num;
    if (User::bookmarks[User::currentUsername].size() == 0)
        return;
    cout << "\nEnter Number to Remove : ";
    cin >> num;
    if (num < 1 || num > User::bookmarks[User::currentUsername].size()) {
        cout << "You Have Entered a Wrong Number \n";
        return;
    }
    auto it = User::bookmarks[User::currentUsername].begin();
    advance(it, num - 1);
    User::bookmarks[User::currentUsername].erase(it);
    cout << "Removed Successfully\n";
}
void User::PrintBookmarks() {
    auto& it = User::bookmarks[User::currentUsername];
    if (it.empty())
        return void(cout << "\nYou Don't Have Any Bookmarks\n");
    cout << "\nYour Bookmarks :\n\n";
    int i = 1;
    for (auto& it2 : it) {
        cout << "[" << i++ << "]" << it2 << "\n";
    }
}
void User::AddCategoryToInterested()
{

    cout << "Choose a Category Of The Following to Add to Your Interested Categories : \n\n";

    for (int i = 0; i < (int)News::categories.size(); i++) {
        cout << "[" << (i + 1) << "] " << News::categories[i] << "\n";
    }

    int category;
    cout << "\n\nChoice : ";
again:
    cin >> category;
    if (category >= 1 && category <= (int)News::categories.size()) {
        if (find(interestedCategories[currentUsername].begin(), interestedCategories[currentUsername].end(), News::categories[category-1]) != interestedCategories[currentUsername].end()) {
            cout << "Category Already Exists in Your Interested\n";
            system("pause");
            return;
        }
        interestedCategories[currentUsername].insert(News::categories[category-1]);
        cout << "Category Added Successfully\n";
    }
    else {
        cout << "\nPlease Choose a Vaild Category to Add : ";
        goto again;
    }
    system("pause");
    
}

void User::RemoveCategoryFromInterested()
{
    if (!interestedCategories[currentUsername].size()) {
        cout << "You Have no Interested Categories\n";
    }
    else {
        cout << "Choose a Category From yours to Remove From Your Interested Categories\n\n";
        int counter = 1;
        for (unordered_set<string>::iterator i = interestedCategories[currentUsername].begin(); i != interestedCategories[currentUsername].end(); i++) {
            cout << "[" << counter << "] " << *i << "\n";
            counter++;
        }
        int category;
        cout << "Choice : ";
    again:
        cin >> category;
        if (category >= 1 && category <= (int)interestedCategories[currentUsername].size()) {
            auto it = interestedCategories[currentUsername].begin();
            advance(it, category - 1);
            interestedCategories[currentUsername].erase(it);
            cout << "\nCategory Removed Successfuly\n";
        }
        else {
            cout << "\nPlease Choose a Vaild Category to Remove : ";
            goto again;
        }
    }
    system("pause");
}

void User::displayInterestedCategories()
{
    if (!interestedCategories[User::currentUsername].size()) {
        cout << "You Have No Interested Categories\n";
    }
    else {
        cout << "Your interested Categores :\n\n";
        int counter = 1;
        for (auto& it2 : (interestedCategories[User::currentUsername])) {
            cout << "[" << counter << "] " << it2 << "\n";
            counter++;
        }
    }
    system("pause");
}

void User::emailInterestedUsers(string category)
{
    for (auto& user : User::users) {
        if (find(interestedCategories[user.first].begin(), interestedCategories[user.first].end(), category) != interestedCategories[user.first].end()) {
            string mail = User::users[user.first].Email;
            fstream file;
            file.open("emailNotification.ps1", ios::in | ios::out);

            if (!file) {
                cout << "Error in opening file";
                return;
            }

            string line;
            string content = "";
            int lineNumber = 1;

            while (getline(file, line)) {
                if (lineNumber == 4) {
                    line += mail + "\"";
                }

                if (lineNumber == 6)
                {
                    line += "You Have A New Article For Your Interested Category : " + category +  ".\"";
                }
                content += line + "\n";

                lineNumber++;
            }

            file.clear();
            file.seekp(0, ios::beg);
            file << content;
            file.close();

            system("powershell -ExecutionPolicy Bypass -File emailNotification.ps1");

            string newContent = "";
            string::size_type pos;
            lineNumber = 1;

            file.open("emailNotification.ps1", ios::in);

            while (getline(file, line)) {
                if (lineNumber == 4) {
                    pos = line.find(mail + "\"");
                    if (pos != string::npos) {
                        line.erase(pos, mail.size() + 1);
                    }
                }
                if (lineNumber == 6) {
                    pos = line.find("You Have A New Article For Your Interested Category : " + category + ".\"");
                    if (pos != string::npos) {
                        line.erase(pos, 56 + category.size());
                    }
                }
                newContent += line + "\n";

                lineNumber++;
            }
            file.close();
            file.open("emailNotification.ps1", ios::out);
            file << newContent;
            file.close();
        }
    }
}

int User::Register() {
    Style::styleText(" Sign up ");
    string username, password, email;
    cout << "\nEnter Your Username : ";
    cin >> username;
    cout << "Enter Your Password : ";
    cin >> password;
    cout << "Enter Your Email : ";
    cin >> email;
    while (true) {
        if (!is_email_valid(email)) {
            cout << "\n\nEmail is Invalid, Please Enter a Valid Email : ";
            cin >> email;
        }
        else {
            break;
        }
    }
    if (username == "admin")
        return -1;

    if (User::users.find(username) != User::users.end()) {
        cout << "User Already Exists\n";
        system("pause");
        return -1;
    }
    User usr(username, password, email);
    User::users.insert({ username, usr });
    cout << "Registered Successfully\n";
    system("pause");
    return 0;
}

User User::searchUserByUsername(string username) {
    User usr;
    if (User::users.find(username) != User::users.end()) {
        return User::users[username];
    }
    return usr;
}

void User::search()
{
    string key;
    cout << "[Search for]-> ";
    cin.ignore();
    getline(cin, key);
    int i = 1;
    auto search_result = News::serachNews(key);
    if (search_result.empty()) {
        cout << "No Articles Found\n";
    }
    else {
        cout << "\nSearch Result : \n\n";
        for (auto news_post : search_result) {
            cout << '[' << i++ << ']';
            news_post.displayPost();
        }

    }
    system("pause");
}

//News User::searchByTitle(string title)
//{
//    for (auto& it : News::news) {
//        if (title.compare(it.getTitle()) == 0) {
//            return it;
//        }
//    }
//}

int User::LogIn() {
    string username, password;
    bool LoggedIn = false;
    int responce = 0;
    
    Style::styleText("  Log In  ");
    cout << "\nEnter Username : ";
    cin >> username;
    cout << "Enter Password : ";
    cin >> password;

    if (username == "admin" && password == "admin") {
        cout << "Logged in Successfully as an Admin\n";
        system("pause");
        return 1;
    }

    if (User::users.find(username) != User::users.end()) {

        if (User::users[username].Password == password) {
            LoggedIn = true;
            User::users[username].LoginAtempts = 2;
            currentUsername = username;
            currentPassword = password;
            News::valid.clear();
            for (int i = 0; i < News::news.size(); i++)
            {
                auto it = User::users[User::currentUsername].spamNews.find(News::news[i].getTitle());
                if (it != User::users[User::currentUsername].spamNews.end()) {
                    continue;
                }
                float rate = News::news[i].getRate();

                if (rate >= 2.0 || rate == 0.0)
                {
                    News::valid.push_back(News::news[i]);
                }
            }
            cout << "Logged in Successfully\n";
            system("pause");
            return 0;
        }
        else {
            User::users[username].LoginAtempts--;
            if (User::users[username].LoginAtempts < 0) {
                cout << "\nEnter [1] to Send a 6-digit Code to Your Email or -1 to Continue : ";
                cin >> responce;
                if (responce == 1)
                    User::users[username].ForgetPassword(username);
            }
            else {
                cout << "Username or Password is Incorrect\n";
                system("pause");
            }
        }
    }
    else {
        cout << "Username or Password is Incorrect\n";
        system("pause");
    }

    return -1;
}

int User::ForgetPassword(string username) {
    string mail, randomCode, enteredCode, password, confirmPassword;
    mail = User::users[username].Email;
    randomCode = User::GenRandomPassword();
    fstream file;
    file.open("ForgetPassword.ps1", ios::in | ios::out);

    if (!file) {
        cout << "Error in opening file";
        return 0;
    }

    string line;
    string content = "";
    int lineNumber = 1;

    while (getline(file, line)) {
        if (lineNumber == 4) {
            line += mail + "\"";
        }

        if (lineNumber == 6)
        {
            line += randomCode + "\"";
        }
        content += line + "\n";

        lineNumber++;
    }

    file.clear();
    file.seekp(0, ios::beg);
    file << content;
    file.close();

    system("powershell -ExecutionPolicy Bypass -File ForgetPassword.ps1");

    string newContent = "";
    string::size_type pos;
    lineNumber = 1;

    file.open("ForgetPassword.ps1", ios::in);

    while (getline(file, line)) {
        if (lineNumber == 4) {
            pos = line.find(mail + "\"");
            if (pos != string::npos) {
                line.erase(pos, mail.size() + 1);
            }
        }
        if (lineNumber == 6) {
            pos = line.find(randomCode + "\"");
            if (pos != string::npos) {
                line.erase(pos, randomCode.size() + 1);
            }
        }
        newContent += line + "\n";

        lineNumber++;
    }
    file.close();
    file.open("ForgetPassword.ps1", ios::out);
    file << newContent;
    file.close();
    cout << "Enter The 6-digit Code or Enter \"1\" to Exit\n";
    cin >> enteredCode;
    while (true) {
        if (enteredCode == randomCode) {
            cout << "\nEnter Your New Password : ";
            cin >> password;
            cout << "\nEnter Your New Password Again : ";
            cin >> confirmPassword;
            if (password == confirmPassword) {
                User::users[username].Password = password;
                cout << "\nPassword Changed Successfuly\n";
                User::users[username].LoginAtempts = 2;
                system("pause");
                break;
            }
            else {
                cout << "\nPasswords Do not Match\n";
            }
        }
        else if (enteredCode == "1") {
            system("CLS");
            break;
        }
        else {
            cout << "Codes Don't Match\n\nPlease Enter The 6-digit Code Again : ";
            cin >> enteredCode;
        }
    }
    return 0;
}

void User::adminMenu() {
    Style::styleText(" Admin's Main Menu ");
    cout << "[1] Add New Category \n\n";
    cout << "[2] Post News \n\n";
    cout << "[3] Remove News \n\n";
    cout << "[4] Update News \n\n";
    cout << "[5] Display an Article Rate\n\n";
    cout << "[6] Display All News\n\n";
    cout << "[7] Display Details\n\n";
    cout << "[8] Log Out\n\n";
}

void User::userMenu() {
    Style::styleText(" User's Main Menu ");
    cout << "[1] Search \n\n";//-------
    cout << "[2] Display Latest News \n\n";//-----
    cout << "[3] Search by Category \n\n";//------
    cout << "[4] Rate News \n\n";
    cout << "[5] Bookmarking\n\n";
    cout << "[6] Trending News\n\n";
    cout << "[7] Spam News \n\n";
    cout << "[8] Comment\n\n";
    cout << "[9] Add Category to Interested\n\n";
    cout << "[10] Remove Category From Interested\n\n";
    cout << "[11] Display Interested Categories\n\n";
    cout << "[12] Log Out\n\n";
}
   

void User::spamNewsMenu()
{   
    cout << "Welcome To Spam Menu\n\n";
    cout << "[1] Spam News\n\n";
    cout << "[2] Remove From Spam \n\n";
    cout << "[3] Print Spam \n\n";
    cout << "[4] Return\n\n";

    int choice;
    cout << "Choice : ";
again:
    cin >> choice;
    if (choice == 4)
        return;
    else if (choice == 1)
        spamNewsFunc();
    else if (choice == 2)
        removeSpamNews();
    else if (choice == 3) {
        printSpam();
        system("pause");
    }
    else
    {       
        cout << "Invalid Input, Please Try Again : ";
        goto again;
    }
}

void User::spamNewsFunc() {
    News::displayAllNews("Date",0,"Details");
    int choice4;
    
    cout << "Enter The Number Of Title Which You Want to Spam or -1 to Skip : ";
 again:
    cin >> choice4;
    if (choice4 == -1)
        return;
    else if (choice4 < 1 || choice4 > News::valid.size())
    {
        cout << "you have entered invalid number , please enter valid choice or -1 to skip : ";
        goto again;
    }
    else
    {
        User::users[User::currentUsername].spamNews.insert(News::news[choice4 - 1].getTitle());
        spamCount++;
        auto it = News::valid.begin();
        advance(it, choice4 - 1);
        News::valid.erase(it);
        User::bookmarks[User::currentUsername].erase(News::news[choice4 - 1].getTitle());
        cout << "Article Added To Your Spam Successfuly\n";
        system("pause");
    }
    cout << User::users[currentUsername].spamNews.size();
}

bool User::printSpam()
{
    if (User::users[currentUsername].spamNews.size() <= 0)
    {
        cout << "You Haven't Added One to Spam Yet \n";
        system("pause");
        return false;
    }
    cout << "Here Are All Added Spam :\n\n";
    int i = 1;
    for (auto news : User::users[currentUsername].spamNews)
    {
        cout << "[" << i++ << "] " << news << "\n";
    }
    return true;
}
void User::removeSpamNews()
{
    bool notEmpty = User::printSpam();
    if (notEmpty) {
        int choice;
        cin >> choice;
        if (choice > User::users[currentUsername].spamNews.size() || choice <= 0)
        {
            cout << "You Have Entered Invalid Number \n";
            system("pause");
            return;
        }
        else
        {
            auto it = User::users[currentUsername].spamNews.begin();
            advance(it, choice - 1);
            string title = *it;
            User::users[currentUsername].spamNews.erase(it);
            for (int i = 0; i < News::news.size(); i++) {
                if (News::news[i].getTitle() == title) {
                    News::valid.push_back(News::news[i]);
                }
            }
            cout << "Article Removed Successfully From Spam\n";
            system("pause");
        }
    }

}

string User::GenRandomPassword() {
    string alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string random;
    srand(time(0));

    for (int i = 0; i < 6; ++i) {
        random += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return random;
}
