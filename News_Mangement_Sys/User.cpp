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
            cout << "this category already exists\n";
            system("pause");
            return;
        }
    }
    News::categories.push_back(cat);
    cout << "added successfully\n";
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
        cout << "there is no articles right now \n";
        return;
    }
    News::displayAllNews("Date",1,"NoDetails");
    cout << "\n please select one of the shown above to remove  or enter -1 to skip\n";
    int num;
    cin >> num;
    if (num == -1)
        return;
    if (num < 1 || num > News::news.size()) {
        cout << "you have entered an invalid number , please try again \n";
        removeNews();
    }
    News::news.erase(News::news.begin() + num - 1);
    cout << "article has been removed successfully\n";
    system("pause");
}
void User::postNews() {
    string title, description,category ,date;
    cout << "fulfill required information to add the article into the system : \n\n";
    cout << "Enter title : ";
    cin.ignore();
    getline(cin, title);
    cout << "enter description : ";   
    getline(cin, description);
    cout << "Enter category : ";
    getline(cin, category);
    cout << "enter date(dd/mm/year) : ";
    cin >> date;

    Utility::dateHandler(date);
    News news1(title , description, Utility::toLower(category),0.0, Date::fromString(date));
    addCategoryAuto(Utility::toLower(category));
    User::emailInterestedUsers(Utility::toLower(category));

    cout << "article posted successfuly\n";
    system("pause");
}
void User::getAverageRateByTitle() {
    if (News::news.size() == 0)
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
    system("pause");
}
void User::AddToBookmarks() {
    int num;
    News::displayAllNews("Date",0,"Details");
    cout << "enter a number : ";
    cin >> num;
    if (News::valid[num]==false) {
        cout << "you have entered a wrong number \n";
        return;
    }
    bool flag = User::IsInBookmarks(News::news[num - 1].getTitle());
    if (flag) {
        cout << "bookmark already exists\n";
        return;
    }
    User::bookmarks[User::currentUsername].insert(News::news[num - 1].getTitle());
    cout << "bookmark added successfully\n";
}
bool User::IsInBookmarks(string title) {
    return (User::bookmarks[User::currentUsername].find(title) != User::bookmarks[User::currentUsername].end());
}
void User::RemoveFromBookmarks() {
    User::PrintBookmarks();
    int num;
    if (User::bookmarks[User::currentUsername].size() == 0)
        return;
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
void User::AddCategoryToInterested()
{

    cout << "Choose a category of the following to add to your interested Categories\n\n";

    for (int i = 0; i < (int)News::categories.size(); i++) {
        cout << "[" << (i + 1) << "]" << News::categories[i] << "\n";
    }
again:
    int category;
    cin >> category;

    if (category >= 1 && category <= (int)News::categories.size()) {
        if (find(interestedCategories[currentUsername].begin(), interestedCategories[currentUsername].end(), News::categories[category-1]) != interestedCategories[currentUsername].end()) {
            cout << "Category already exists in your interested\n";
            system("pause");
            return;
        }
        interestedCategories[currentUsername].insert(News::categories[category-1]);
        cout << "Category added successfully\n";
    }
    else {
        cout << "\nPlease choose a vaild category to add\n";
        goto again;
    }
    system("pause");
    
}

void User::RemoveCategoryFromInterested()
{
    if (!interestedCategories[currentUsername].size()) {
        cout << "You have no interested categories\n";
    }
    else {
        cout << "Choose a category from yours to remove from your interested Categories\n\n";
        int counter = 1;
        for (unordered_set<string>::iterator i = interestedCategories[currentUsername].begin(); i != interestedCategories[currentUsername].end(); i++) {
            cout << "[" << counter << "]" << *i << "\n";
            counter++;
        }
    again:
        int category;
        cin >> category;

        if (category >= 1 && category <= (int)interestedCategories[currentUsername].size()) {
            auto it = interestedCategories[currentUsername].begin();
            advance(it, category - 1);
            interestedCategories[currentUsername].erase(it);
            cout << "\nCategory Removed Successfuly\n";
        }
        else {
            cout << "\nPlease choose a vaild category to remove\n\n";
            goto again;
        }
    }
    system("pause");
}

void User::displayInterestedCategories()
{
    if (!interestedCategories[User::currentUsername].size()) {
        cout << "You have no interested categories\n";
    }
    else {
        cout << "Your interested Categores :\n\n";
        int counter = 1;
        for (auto& it2 : (interestedCategories[User::currentUsername])) {
            cout << "[" << counter << "]" << it2 << "\n";
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
                    line += "You have a new article for your interested category : " + category +  ".\"";
                }
                content += line + "\n";

                lineNumber++;
            }

            file.clear();
            file.seekp(0, ios::beg);
            file << content;
            file.close();

            system("powershell -ExecutionPolicy Bypass -File C:\\Users\\alyas\\source\\repos\\News-managment-system\\News_Mangement_Sys\\emailNotification.ps1");

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
                    pos = line.find("You have a new article for your interested category : " + category + ".\"");
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
    cout << endl << "Enter your Username, Password and Email :" << endl;
    cin >> username;
    cin >> password;
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
        cout << "User already exists\n";
        system("pause");
        return -1;
    }
    User usr(username, password, email);
    User::users.insert({ username, usr });
    cout << "registered successfully\n";
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

int User::LogIn() {
    string username, password;
    bool LoggedIn = false;
    int responce = 0;
    
    Style::styleText("  Log In  ");
    cout << endl << "Enter Username and Password :" << endl;
    cin >> username;
    cin >> password;

    if (username == "admin" && password == "admin") {
        cout << "Logged in successfully as an admin\n";
        system("pause");
        return 1;
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    if (username == "makaty" and password == "makaty") goto direct; // this is just for fast debugging
    ///////////////////////////////////////////////////////////////////////////////////////
    /// 
    if (User::users.find(username) != User::users.end()) {

        if (User::users[username].Password == password) {

direct:
            LoggedIn = true;
            User::users[username].LoginAtempts = 2;
            currentUsername = username;
            currentPassword = password;
            cout << "Logged in successfully\n";
            system("pause");
            return 0;
        }
        else {
            User::users[username].LoginAtempts--;
            if (User::users[username].LoginAtempts < 0) {
                cout << "\nEnter [1] to send your password to your email or [0] to continue\n\n";
                cin >> responce;
                if (responce == 1)
                    User::users[username].ForgetPassword(username);
            }
            else {
                cout << "Username or Password is incorrect\n";
                system("pause");
            }
        }
    }
    else {
        cout << "Username or Password is incorrect\n";
        system("pause");
    }

    return -1;
}

int User::ForgetPassword(string username) {
    string mail, randomCode, enteredCode, password, confirmPassword;
    mail = User::users[username].Email;
    randomCode = User::gen_random();
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

    system("powershell -ExecutionPolicy Bypass -File C:\\Users\\alyas\\source\\repos\\News-managment-system\\News_Mangement_Sys\\ForgetPassword.ps1");

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
    cout << "enter the 6-digit code or enter \"1\" to exit\n";
    cin >> enteredCode;
    while (true) {
        if (enteredCode == randomCode) {
            cout << "\nenter your new password twice\n";
            cin >> password;
            cin >> confirmPassword;
            if (password == confirmPassword) {
                User::users[username].Password = password;
                cout << "\npassword changed successfuly\n\n";
                User::users[username].LoginAtempts = 2;
                system("pause");
                break;
            }
            else {
                cout << "\npasswords do not match\n";
            }
        }
        else if (enteredCode == "1") {
            system("CLS");
            break;
        }
        else {
            cout << "code does'nt match\n\nplease enter the 6-digit code again\n";
            cin >> enteredCode;
        }
    }
    return 0;
}

void User::adminMenu() {
    //cout << "\twelcome to admin menu\n";
    //cout << "Here is all admin operations \n";
    //cout << "please select one of the operations below\n\n\n";
    Style::styleText(" Admin's Main Menu ");
    cout << "[1] add new category \n\n";
    cout << "[2] post news \n\n";
    cout << "[3] remove news \n\n";
    cout << "[4] update news \n\n";
    cout << "[5] display an article rate\n\n";
    cout << "[6] display all news\n\n";
    cout << "[7] display details\n\n";
    cout << "[8] log out\n\n";
}

void User::userMenu() {
    //cout << "\twelcome to user menu\n";
    //cout << "Here is all user operations \n";
    //cout << "please select one of the operations below\n\n\n";
    Style::styleText(" User's Main Menu ");
    cout << "[1] search  \n\n";//-------
    cout << "[2] display latest news \n\n";//-----
    cout << "[3] search by category \n\n";//------
    cout << "[4] rate news \n\n";
    cout << "[5] bookmarking\n\n";
    cout << "[6] trending news\n\n";
    cout << "[7] spam News \n\n";
    cout << "[8] comment\n\n";
    cout << "[9] add category to interested\n\n";
    cout << "[10] remove category from interested\n\n";
    cout << "[11] display Interested Categories\n\n";
    cout << "[12] log out\n\n";
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
    News::displayAllNews("Date",0,"Details");
    int choice4;
    
    cout << "Enter the number of title which you want to spam or -1 to skip \n ";
    again:
    cin >> choice4;
    if (choice4 == -1)
        return;
    else if (News::valid[choice4]==false)
    {
        cout << "you have entered invalid number , please enter valid choice or -1 to skip\n\n\n";
        goto again;
    }
    else
    {
        User::users[User::currentUsername].spamNews.insert(News::news[choice4 - 1].getTitle());
        spamCount++;
        News::valid[choice4] = false;
        User::bookmarks[User::currentUsername].erase(News::news[choice4 - 1].getTitle());
        cout << "article added you spam successfuly\n";
        system("pause");
    }
    cout << User::users[currentUsername].spamNews.size();
}

void User::printSpam()
{
    if (User::users[currentUsername].spamNews.size() <= 0)
    {
        cout << "you haven't added one to spam yet \n";
        system("pause");
        return;
    }
    cout << "here is all added spam \n\n";
    int i = 1;
    for (auto news : User::users[currentUsername].spamNews)
    {
        cout << "[" << i++ << "]" << news << "\n";
    }
    system("pause");
}
void User::removeSpamNews()
{
    if (User::users[currentUsername].spamNews.size() <= 0)
    {
        cout << "you haven't added one to spam yet \n";
        system("pause");
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
        cout << "you have entered invalid number \n";
        system("pause");
        return;
    }
    else
    {
        auto it = User::users[currentUsername].spamNews.begin();
        advance(it, choice - 1);
        User::users[currentUsername].spamNews.erase(it);
        cout << "article removed successfully from spam\n";
        system("pause");
    }

}

string User::gen_random() {
    string alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string random;
    srand(time(0));

    for (int i = 0; i < 6; ++i) {
        random += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return random;
}
