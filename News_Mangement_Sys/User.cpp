#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include<regex>
#include "User.h"
#include "Utility.h"

using namespace std;

map<string, User> User::users;
string User::currentUsername, User::currentPassword;
unordered_map<string, unordered_set<string>> User::bookmarks;

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

string User::getUsername() {
    return this->Username;
}

string User::getPassword() {
    return this->Password;
}

bool User::is_email_valid(string email)
{
    regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

void User::addCategory() {
    cout << "enter name of category you want to add it : ";
    string cat;
    cin.ignore();
    getline(cin, cat);
    cat = Utility::toLower(cat);
    for (int i = 0; i < News::categories.size(); i++) {
        if (cat == News::categories[i]) {
            cout << "this category already exists \n";
            return;
        }
    }
    News::categories.push_back(cat);
    cout << "added successfully\n";
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
        cout << "there is no news right now \n";
        return;
    }
    News::displayAllNews();
    cout << "\n please selecet one of the shown above to remove  or enter -1 to skip\n";
    int num;
    cin >> num;
    if (num == -1)
        return;
    if (num < 1 || num > News::news.size()) {
        cout << "you have entered an invalid number , please try again \n";
        removeNews();
    }
    News::news.erase(News::news.begin() + num - 1);
    cout << "has been removed successfully\n";
}
void User::postNews() {
    string title, description,category ,date;
    cout << "fulfill required information to add the article into system \n";
    cout << "\n";
    cout << "Enter title : ";
    cin.ignore();
    getline(cin, title);
    cout << "enter description : ";   
    getline(cin, description);
    cout << "Enter category : ";
    getline(cin, category);
    cout << "enter date(mm/dd//year) : ";
    cin >> date;
    News news1(title , description,category,0.0,Date(date));
    addCategoryAuto(Utility::toLower(category));
}
void User::getAverageRateByTitle() {
    bool is_emp = News::displayAllNews();
    if (is_emp == true)
    {
        int num;
        do {
            cout << "Enter The number of article you want to see its rate or -1 to skip\n";
            cin >> num;
            if (num == -1)
                return;
        } while (num<1 || num>News::news.size());
        cout << "rate : " << News::news[num - 1].getRate() << "\n";
    }
    else {
        return;
    }
}
void User::bookmarkingMenu() {
    cout << "[1] add article to your favourite \n";
    cout << "[2] delete marked article \n";
    cout << "[3] display all marked articles \n";
    cout << "press -1 to skip\n";
    cout << "\n";
    cout << "enter your choice : ";
    int choice;
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
    else if (choice == -1)
        return;
    else {
        cout << "please select one of the shown operations above \n";
        bookmarkingMenu();
    }
}
void User::AddToBookmarks() {
    int num;
    News::displayAllNews();
    cout << "enter number : ";
    cin >> num;
    if (num < 1 || num > News::news.size()) {
        cout << "you have entered wrong number \n";
        return;
    }
    bool flag = User::IsInBookmarks(News::news[num - 1].getTitle());
    if (flag) {
        cout << "already exists\n";
        return;
    }
    User::bookmarks[User::currentUsername].insert(News::news[num - 1].getTitle());
    cout << "added successfully\n";
}
bool User::IsInBookmarks(string title) {
    return (User::bookmarks[User::currentUsername].find(title) != User::bookmarks[User::currentUsername].end());
}
void User::RemoveFromBookmarks() {
    User::PrintBookmarks();
    int num;
    cout << "enter number to remove : ";
    cin >> num;
    if (num < 1 || num > User::bookmarks[User::currentUsername].size()) {
        cout << "you have entered wrong one \n";
        return;
    }
    auto it = User::bookmarks[User::currentUsername].begin();
    std::advance(it, num - 1);
    User::bookmarks[User::currentUsername].erase(it);
    cout << "removed successfully\n";
}
void User::PrintBookmarks() {
    auto& it = User::bookmarks[User::currentUsername];
    if (it.empty())
        return void(cout << "You don't have bookmarks.\n");
    cout << "Your Bookmarks :\n";
    int i = 1;
    for (auto& it2 : it) {
        cout << "[" << i++ << "]" << it2 << "\n";
        cout << "~~~~~~";
    }
    cout << "~~~~~~~~~~~~~~~~~~~~\n";
}
int User::Register() {
    string username, password, email;
    cout << endl << "Sign up" << endl;
    cout << endl << "Enter your username" << endl;
    cin >> username;
    cout << endl << "Enter your password" << endl;
    cin >> password;
    cout << endl << "Enter your email" << endl;
    cin >> email;
    while (true) {
        if (!is_email_valid(email)) {
            cout << "\nEmail is invalid, please enter a valid email\n\n";
            cin >> email;
        }
        else {
            break;
        }
    }
    if (username == "admin")
        return -1;

    if (User::users.find(username) != User::users.end()) {
        return -1;
    }
    User usr(username, password, email);
    User::users.insert({ username, usr });
    return 0;
}

User User::searchUserByUsername(string username) {
    User usr;
    if (User::users.find(username) != User::users.end()) {
        return User::users[username];
    }
    return usr;
}

int User::LogIn() {
    string username, password;
    bool LoggedIn = false;
    int responce = 0;
    cout << endl << "Log In" << endl;
    cout << endl << "Enter Username " << endl;
    cin >> username;
    cout << endl << "Enter Password " << endl;
    cin >> password;
    if (username == "admin" && password == "admin") {
        return 1;
    }

    if (User::users.find(username) != User::users.end()) {
        if (User::users[username].Password == password) {
            LoggedIn = true;
            User::users[username].LoginAtempts = 2;
        }
        else {
            User::users[username].LoginAtempts--;
            if (User::users[username].LoginAtempts < 0) {
                cout << "\nEnter [1] to send your password to your email or [0] to continue\n\n";
                cin >> responce;
                if (responce == 1)
                    User::users[username].ForgetPassword(username);
            }
        }
    }


    else if (LoggedIn) {
        currentUsername = username;
        currentPassword = password;
        cout << "Logged in successfully";
        return 0;
    }
    else {
        return -1;
    }
    return -1;
}

void User::ForgetPassword(string username) {
    cout << "\npassword has been sent to your email\n\n";
}

void User::adminMenu() {
    cout << "\twelcome to admin menu\n";
    cout << "Here is all admin operations \n";
    cout << "please select one of the operations below\n\n\n";
    cout << "[1] add new category \n";
    cout << "[2] post news \n";
    cout << "[3] remove news \n";
    cout << "[4] update news \n";
    cout << "[5] display an article rate\n";
    cout << "[6] display all news\n";
    cout << "[7] display details\n";
    cout << "[8] log out\n";
}

void User::userMenu() {
    cout << "\twelcome to user menu\n";
    cout << "Here is all user operations \n";
    cout << "please select one of the operations below\n\n\n";
    cout << "[1] search  \n";//-------
    cout << "[2] display latest news \n";//-----
    cout << "[3] search by category \n";//------
    cout << "[4] rate news \n";
    cout << "[5] bookmarking\n";
    cout << "[6] trending news\n";
    cout << "[7] spam News \n";
    cout << "[8] comment\n";
    cout << "[9] log out\n";
}
   

void User::spamNewsMenu()
{   
    cout << "welcome to spam menu\n";
    cout << "[1]spam news\n";
    cout << "[2]remove from spam \n";
    cout << "[3]print spam \n";
    cout << "[4]return\n";
    int choice;
    cin >> choice;
    if (choice == 4)
        return;
    else if (choice == 1)
        spamNewsFunc();
    else if (choice == 2)
        removeSpamNews();
    else if (choice == 3)
        printSpam();
    
    else
    {       
        cout << "invalid input , please try again \n";
        spamNewsMenu();
    }

}

void User::spamNewsFunc() {
    News::displayNewsForUser();
    int choice4;
    cout << "Enter the number of title which you want to spam or -1 to skip \n ";
    cin >> choice4;
    if (choice4 == -1)
        return;
    else if (!News::validChoice(choice4))
    {
        cout << "you have entered invalid number \n\n\n";
        spamNewsFunc();
    }
    else
    {
        User::users[User::currentUsername].spamNews.insert(News::news[choice4 - 1].getTitle());
        spamCount++;
    }
    cout << User::users[currentUsername].spamNews.size();
}

void User::printSpam()
{
    if (User::users[currentUsername].spamNews.size() <= 0)
    {
        cout << "you haven't added one to spam yet \n";
        return;
    }
    cout << "here is all added spam \n\n";
        int i = 1;
        for (auto news : User::users[currentUsername].spamNews)
        {
            cout << "[" << i++ << "]" << news << "\n";
        }
    
}
void User::removeSpamNews()
{
    if (User::users[currentUsername].spamNews.size() <= 0)
    {
        cout << "you haven't added one to spam yet \n";
        return;
    }

    cout << "here is all added spam \n\n";
    int i = 1;
    for (auto news : User::users[currentUsername].spamNews)
    {
        cout << "[" << i++ << "]" << news << "\n";
    }
    int choice;
    cin >> choice;
    if (choice > User::users[currentUsername].spamNews.size() || choice <= 0)
    {
        system("CLS");
        cout << "you have entered invalid number \n\n\n";
        return;
    }
    else
    {
        auto it = User::users[currentUsername].spamNews.begin();
        advance(it, choice - 1);
        User::users[currentUsername].spamNews.erase(it);
    }
     


}
