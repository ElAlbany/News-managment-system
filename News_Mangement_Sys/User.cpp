#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "User.h"

using namespace std;

vector<User> User::users;
string User::currentUsername, User::currentPassword;
unordered_map<string, unordered_set<string>> User::bookmarks;

User::User(string username, string password) {
    this->Username = username;
    this->Password = password;
}

User::User() {
    this->Username = "";
    this->Password = "";
}

string User::getUsername() {
    return this->Username;
}

string User::getPassword() {
    return this->Password;
}
void User::addCategory() {
        cout << "enter name of category you want to add it : ";
        string cat;
        cin >> cat;
        for (int i = 0; i < News::categories.size(); i++) {
            if (cat == News::categories[i]) {
                cout << "this category already exists \n";
                return;
            }
        }
        News::categories.push_back(cat);
        cout << "added successfully\n";
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
    cout << "has beed removes successfully\n";
}
void User::postNews() {
    string title, description, date;
    cout << "fulfill required information to add the article into system \n";
    cout << "\n";
    cout << "Enter title : ";
    cin >> title;
    cout << "enter description : ";
    cin >> description;
    News(title, description);
}
void User::getAverageRateByTitle() {
      bool is_emp = News::displayAllNews();
      if(is_emp==true)
      {
          int num;
          do {
          cout << "Enter The number of article you want to see its rate or -1 to skip\n";
          cin >> num;
          if (num == -1)
              return;
          }while(num<1||num>News::news.size());
          cout << "rate : " << News::news[num - 1].getRate() << "\n";
      }else{
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
    } else if (choice == 2) {
        RemoveFromBookmarks();
    } else if (choice == 3) {
        PrintBookmarks();
    } else if (choice == -1)
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
    auto &it = User::bookmarks[User::currentUsername];
    if (it.empty())
        return void(cout << "You don't have bookmarks.\n");
    cout << "Your Bookmarks :\n";
    int i = 1;
    for (auto &it2: it) {
        cout << "[" << i++ << "]" << it2 << "\n";
        cout << "~~~~~~";
    }
    cout << "~~~~~~~~~~~~~~~~~~~~\n";
}
int User::Register() {
    string username, password;
    cout << endl << "Sign In" << endl;
    cout << endl << "Enter your username" << endl;
    cin >> username;
    cout << endl << "Enter your password" << endl;
    cin >> password;
    if (username == "admin")
        return -1;
    for (int i = 0; i < User::users.size(); i++) {
        if (username == User::users[i].Username) {
            return -1;
        }
    }
    User usr(username, password);
    User::users.push_back(usr);
    return 0;
}

User User::searchUserByUsername(string username) {
    User us;
    for (int i = 0; i < User::users.size(); i++) {
        if (username == User::users[i].Username) {
            return User::users[i];
        }
    }
    return us;
}

void User::displayAllUsers() {
    for (int i = 0; i < User::users.size(); i++) {
        cout << endl << "[" << i << "]" << endl;
        cout << "username: " + User::users[i].Username << endl;
        cout << "password: " + User::users[i].Password << endl;
    }
}

int User::LogIn() {
    string username, password;
    bool LoggedIn = false;
    cout << endl << "Log In" << endl;
    cout << endl << "Enter Username" << endl;
    cin >> username;
    cout << endl << "Enter Password" << endl;
    cin >> password;
    for (int i = 0; i < User::users.size(); i++) {
        if (username == User::users[i].Username && password == User::users[i].Password) {
            LoggedIn = true;
        }
    }
    if (username == "admin" && password == "admin") {
        return 1;
    } else if (LoggedIn) {
        currentUsername = username;
        currentPassword = password;
        cout << "Logged in successfully";
        return 0;
    } else {
        return -1;
    }
    return -1;


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
    cout << "[7] log out\n";
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
    cout << "[8] log out\n";
}
void User::spamNewsFunc(){
  bool is_found = News::displayAllNews();
  if(is_found){
    int choice4;
    do {
        cout << "Enter the number of title which you want to spam \n ";
        cin >> choice4;
    } while (choice4>News::news.size()&& choice4<=0);
    choice4--;
    spamNews.emplace(News::news[choice4].getTitle());
    spamCount++;
  }
  return;
}
