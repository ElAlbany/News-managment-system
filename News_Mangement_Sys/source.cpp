#include <iostream>
#include <algorithm>
#include <ctime>
#include "News.h"
#include "Date.h"
#include "User.h"
#include "Database.h"
#include <windows.h>
#include "Style.h"
using namespace std;


int main() {

    // read from database (files) and style the console background and set width
    Style::setupConsole();

    int admin;
    int registered = 5;

    /////////////////////////// MAIN PROGRAM ///////////////////////////
    while (true) 
    {
        if (registered == -1) {
            cout << "Username Already Exists" << endl
                << endl;
            registered = 5;
        }
        else if (registered == 0) {
            cout << "Registered Successfully" << endl
                << endl;
            registered = 5;
        }
        string username, password;
        bool adminExist = false; // to chech weather the account is admin
        int UserIndex = -1;      // to check weather the account is user and if is not -1 then we have the index to use it in other operations
        int choice;

        
        // add a background and center align the text.
        
    l:
        system("CLS");
        Style::styleText(" Enter One of The Shown Operations Below ");
        cout << "[1] Log in \n\n[2] Sign up \n\n[3] Exit \n\n";

        cout << "Choice : ";
        cin >> choice; 
        cin.fail();
        cin.clear();
        cin.ignore(256, '\n');
        if (choice == 3) { // exit
            Database::write();
            exit(1);
        }
        else if (choice == 2) // sign up
        {
            system("CLS");
            registered = User::Register();
            continue;
        }
        else if (choice == 1) // log in
        {
            system("CLS");
            admin = User::LogIn();
            if (admin == -1) {
                continue;
            }
        }
        else { // invalid
            cout << "Invalid Operation, Please Enter a Vaild Choice : ";
            system("pause");
            goto l;
        }
        system("CLS");


        ////////////////////////////////// ADMIN'S MAIN MENU //////////////////////////////////
        while (admin == 1) 
        {
            system("ClS");
            User::adminMenu();
            int choice2;
            cout << "Choice : ";
            cin >> choice2;
            cin.fail();
            cin.clear();
            cin.ignore(256, '\n');
            system("ClS");
            Style::styleText(" Admin's Main Menu ");
            if (choice2 == 1) // add new category
            {
                User::addCategory();
            }
            else if (choice2 == 2) // add post
            {
                User::postNews();
            }
            else if (choice2 == 3) // remove news
            {
                User::removeNews();
            }
            else if (choice2 == 4) // update news
            {
                News::updateMenu();
            }
            else if (choice2 == 5) // display an article rate
            {
                News::displayAllNews("Date", 1, "NoDetails", News::news.size());
                User::getAverageRateByTitle();
            }
            else if (choice2 == 6) // display all news
            {
                News::displayAllNews("Date",1,"NoDetails", News::news.size());
                system("pause");
            }
            else if (choice2 == 7) // display details
            {
                News::displayNewsDetails();
                system("pause");
            }
            else if (choice2 == 8) // log out
            {
                admin = -1;
                break;
            }
            else {
                cout << "Invalid Operation, Please Select Only One of The Operations Below \n";
                system("pause");
                goto l;
            }
            system("CLS");
        }
        ////////////////////////////////// USER'S MAIN MENU //////////////////////////////////
        while (admin == 0) 
        {
            system("ClS");
            User::userMenu();
            int choice3;
            cout << "Choice : ";
            cin >> choice3;
            cin.fail();
            cin.clear();
            cin.ignore(256, '\n');
            system("ClS");
            Style::styleText(" User's Main Menu ");
            if (choice3 == 1) // search news
            {
                User::search();
            }
            else if (choice3 == 2) // display latest news
            {
                News::displayAllNews("Date", 0, "Details");
                system("pause");
            }
            else if (choice3 == 3) // search by category
            {
                News::displayNewsByCategoryName();
            }
            else if (choice3 == 4) // rate news
            {
                News::rateNews(User::currentUsername);
            }
            else if (choice3 == 5) // bookmarking
            {
                User::bookmarkingMenu();
            }
            else if (choice3 == 6) // trending news
            {
                News::displayAllNews("Trending", 0, "Details");
                system("pause");
            }
           
            else if (choice3 == 7) { // spam function
              
                User ob;
                ob.spamNewsMenu();
            }
            else if (choice3 == 8) { // comment
                News::commentMenu();

            }
            else if (choice3 == 9) { // add to interested categories
               User::InterestedCategoriesMenu();
            }
            else if (choice3 == 10) { // log out
                admin = -1;
                break;
            }
            else { // invalid
                cout << "Invalid Operation, Please Select Only One of The Operations Below \n";
                system("pause");
                continue;
            }
            system("CLS");
        }
    }
}
