#include <iostream>
#include <algorithm>
#include <ctime>
#include "UserRepository.h"
#include "News.h"
#include "Date.h"
#include "User.h"
#include "Database.h"
using namespace std;

int main() {

    Database::read();

    int admin;
    int registered = 5;
    while (true) // main program
    {
        if (registered == -1) {
            cout << "username already exists" << endl
                << endl;
            registered = 5;
        }
        else if (registered == 0) {
            cout << "registered successfully" << endl
                << endl;
            registered = 5;
        }
        string username, password;
        bool adminExist = false; // to chech weather the account is admin
        int UserIndex = -1;         // to check weather the account is user and if is not -1 then we have the index to use it in other operations
        int choice;
    l:
        cout << "\nEnter one of the shown operations below\n\n";
        cout << "[1] log in \n[2] sign up \n[3] exit \n\n";

        cin >> choice;
        if (choice == 3) {
            Database::write();
            exit(1);
        }
        else if (choice == 2) // sign up
        {
            registered = User::Register();
            continue;
        }
        else if (choice == 1) // log in
        {
            admin = User::LogIn();
            if (admin == -1) {
                continue;
            }
        }
        else {
            system("CLS"); // clear screan
            cout << "invalid operation , please select only one of the operations below \n";
            goto l;
        }



        while (admin == 1) // admin
        {
            //cout << News::categories.size() << endl;
            User::adminMenu();
            int choice2;
            cin >> choice2;
            if (choice2 == 1) //  add new category
            {

                User::addCategory();
            }
            else if (choice2 == 2) // remove category
            {
                User::postNews();
               
            }
            else if (choice2 == 3) // remove news
            {

                User::removeNews();
               

            }
            else if (choice2 == 4) //  update news
            {
              
                News::updateMenu();
            }
            else if (choice2 == 5) //   display an article rate
            {

                News::displayAllNews();
                User::getAverageRateByTitle();

            }
            else if (choice2 == 6) //display all news
            {
                News::displayAllNews();

            }
            else if (choice2 == 7) //display details
            {
                News::displayAllNews();
                cout << "enter number to see its details \n";
                int choice3; cin >> choice3;
                if (choice3 > News::news.size() || choice3 <= 0)
                {
                    cout << "you have entered invalid number\n";
                    continue;
                }
                News::news[choice3 - 1].displayPost();

            }
            else if (choice2 == 8) // log out
            {
                admin = -1;
                break;
            }
            else {
                system("CLS"); // clear screan
                cout << "invalid operation , please select only one of the operations below \n";
                continue;
            }
        }

        while (admin == 0) // user
        {
            User::userMenu();
            int choice3;
            cin >> choice3;
            if (choice3 == 1) // search news
            {
                string key;
                cout << "[Search for]-> ";
                cin.ignore();
                getline(cin, key);
                int i = 1;
                auto search_result = News::serachNews(key);
                if (search_result.empty()) cout << "NO NEWS FOUND!\n";
                else {
                    cout << "\t--------------SEARCH RESULt-----------\n";
                    for (auto news_post : search_result) {
                        cout << '[' << i++ << ']' << endl;
                        news_post.displayPost();
                    }

                }
            }
            else if (choice3 == 2) // display latest news
            {
                News::displayLatestNews(0);
            }
            else if (choice3 == 3) // search by category
            {
                cout << "enter category you want to see its articles \n";
                string cat;
                cin >> cat;
                News::displayNewsByCategoryName(cat);
            }
            else if (choice3 == 4) //  rate news
            {
                News::rateNews(News::news, User::currentUsername);
            }
            else if (choice3 == 5) //   bookmarking
            {
                User::bookmarkingMenu();
            }
            else if (choice3 == 6) // trending news
            {
                News::displayTrendingNews();
            }
           
            else if (choice3 == 7) { // spam function
              
                User ob;
                ob.spamNewsMenu();
            }
            else if (choice3 == 8) { // comment
                News::displayLatestNews(8);
            }
            else if (choice3 == 9) { // add interested categories
               User::AddCategoryToInterested();
            }
            else if (choice3 == 10) { // log out
                admin = -1;
                break;
            }
            else if (choice3 == 11) {
                User::displayInterestedCategories();
            }
            else {
                cout << "invalid operation , please select only one of the operations below \n";
                continue;
            }
        }
    }
}
