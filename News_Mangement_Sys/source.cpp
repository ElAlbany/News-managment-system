
#include <iostream>
#include <algorithm>
#include <ctime>
#include "News.h"
#include "Date.h"
#include "News.cpp"
#include "User.h"
#include "User.cpp"

using namespace std;

int main() {
    int admin;
    int registered = 5;
    while (true) // main program
    {
        if (registered == -1) {
            cout << "username already exists" << endl
                 << endl;
            registered = 5;
        } else if (registered == 0) {
            cout << "registered successfully" << endl
                 << endl;
            registered = 5;
        }
        string username, password;
        bool adminExist = false; // to chech weather the account is admin
        int UserIndex = -1;         // to check weather the account is user and if is not -1 then we have the index to use it in other operations
        int choice;
        l :
        cout << "Enter one of the shown operations below\n\n";
        cout << "[1] log in \n[2] sign up \n[3] exit \n\n";

        cin >> choice;
        if (choice == 3) {
            exit(1);
        } else if (choice == 2) // sign up
        {
            registered = User::Register();
            continue;
        } else if (choice == 1) // log in
        {
            admin = User::LogIn();
            if (admin == -1) {

                cout << "Username or Password is incorrect";
                continue;

            }
        } else {
            system("CLS"); // clear screan
            cout << "invalid operation , please select only one of the operations below \n";
            goto l;
        }



        while (admin == 1) // admin
        {
            User::adminMenu();
            int choice2;
            cin >> choice2;
            if (choice2 == 1) //  add new category
            {

                User::addCategory();
            } else if (choice2 == 2) // post news
            {

                User::postNews();
            } else if (choice2 == 3) // remove news
            {

                News::displayAllNews();
                User::removeNews();

            } else if (choice2 == 4) //  update news
            {

            } else if (choice2 == 5) //   display an article rate
            {

                News::displayAllNews();
                User::getAverageRateByTitle();

            }
            else if (choice2 == 6) //display all news
            {
                News::displayAllNews();

            }else if (choice2 == 7) // log out
            {
                admin=-1;
                break;
            } else {
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
            if (choice3 == 1) // search
            {
            } else if (choice3 == 2) // display latest news
            {
                News::displayLatestNews();
            } else if (choice3 == 3) // search by category
            {
                cout<<"enter category you want to see its articles \n";
                string cat;
                cin>>cat;
                News::displayNewsByCategoryName(cat);
            } else if (choice3 == 4) //  rate news
            {
                News::rateNews(News::news, User::currentUsername);
            } else if (choice3 == 5) //   bookmarking
            {
                   User::bookmarkingMenu();
            } else if (choice3 == 6) // trending news
            {
                News::displayTrendingNews();
            } else if (choice3 == 8) // log out
            {
                admin=-1;
                break;
            } else if(choice3 == 7){
              User ob;
              ob.spamNewsFunc();
            } else {
                cout << "invalid operation , please select only one of the operations below \n";
                continue;
            }
        }
    }
}
