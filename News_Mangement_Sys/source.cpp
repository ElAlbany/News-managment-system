#include <iostream>
#include <algorithm>
#include <ctime>
#include "UserRepository.h"
#include "UserRepository.cpp"
#include "News.h"

#include "Date.h"


#include "News.cpp"
#include "User.h"
#include "User.cpp"

using namespace std;
int main()
{

	Date d("12-3-2022");
	cout << d.getDay() << endl;
	cout << d.getMonth() << endl;
	
	return 0;

	// Some News Objects Samples for testing ONLY!!!!
	News new1("Derby Match", "zamalek won 2-1 today againest al ahly", "Sport", 3.4);
	News new2("Covid19", "coronavirus aka covid19 is back!", "Health", 3.8);
	News new3("KSA", "KSA gained 100 trillion dollars from oil!", "Industry", 2);

	int admin;
	int registered = 5;
	while (true) // main program
	{
		system("CLS");
		if (registered == -1)
		{
			cout << "username already exists" << endl
				 << endl;
			registered = 5;
		}
		else if (registered == 0)
		{
			cout << "registered successfully" << endl
				 << endl;
			registered = 5;
		}
		string username, password;
		bool adminExist = false; // to chech weather the account is admin
		int UserIndex = -1;		 // to check weather the account is user and if is not -1 then we have the index to use it in other operations
		int choice;
		cout << "Enter one of the shown operations below\n\n";
		cout << "[1] log in \n[2] sign up \n[3] exit \n\n";

		cin >> choice;
		if (choice == 3)
		{
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
			if (admin == -1)
			{
				system("CLS");
				cout << "Username or Password is incorrect";
				continue;
			}
		}
		else
		{
			system("CLS"); // clear screan
			cout << "invalid operation , please select only one of the operations below \n";
			// goto ;
		}

		system("CLS");

		while (admin == 1) // admin
		{
			UserRepository::adminMenu();
			int choice2;
			cin >> choice2;
			if (choice2 == 1) //  add new category
			{
			}
			else if (choice2 == 2) // post news
			{
			}
			else if (choice2 == 3) // remove news
			{
			}
			else if (choice2 == 4) //  update news
			{
			}
			else if (choice2 == 5) //   display an article rate
			{
			}
			else if (choice2 == 6) // display all news
			{
			}
			else if (choice2 == 7) //   add new admin
			{
			}
			else if (choice2 == 8) //  remove admin
			{
			}
			else if (choice2 == 9) // log out
			{
				break;
			}
			else
			{
				system("CLS"); // clear screan
				cout << "invalid operation , please select only one of the operations below \n";
				continue;
			}
		}

		while (admin == 0) // user
		{
			UserRepository::userMenu();
			int choice3;
			cin >> choice3;
			if (choice3 == 1) // search
			{
			}
			else if (choice3 == 2) // display latest news
			{
				News::displayLatestNews();
			}
			else if (choice3 == 3) // search by category
			{
			}
			else if (choice3 == 4) //  rate news
			{
			}
			else if (choice3 == 5) //   bookmarking
			{
			}
			else if (choice3 == 6) // trending news
			{
				News::displayTrendingNews();
			}

			else if (choice3 == 7) // log out
			{
				break;
			}
			else
			{
				system("CLS"); // clear screan
				cout << "invalid operation , please select only one of the operations below \n";
				continue;
			}
		}
	}
}