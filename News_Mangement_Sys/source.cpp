#include <iostream>
#include "UserRepository.h"
#include "News.h"


using namespace std;

int main()
{
	while (true)//main program
	{
		system("CLS");
		string username, password;
		bool adminExist = false; //to chech weather the account is admin
		int UserIndex = -1; // to check weather the account is user and if is not -1 then we have the index to use it in other operations
		int choice;
		cout << "Enter one of the shown operations below\n\n";
		cout << "[1] log in \n[2] sign up \n[3] exit \n\n";
		cout << "no";

		cin >> choice;
		if (choice == 3) {
			exit(1);
		}
		else if (choice == 2)//sign up
		{

			continue;
		}
		else if (choice == 1)//log in
		{
			//log in function should return index of the user or admin in a 
			//variable called UserIndex to use it on user functions easily
			//adminExist = adminExist() function; return bool
			//UserIndex = userExist() function; return index
			if (adminExist == false && UserIndex == -1)
			{
				system("CLS");
				cout << "invalid username or password \n please try again\n\n";
				continue;
			}
		}
		else
		{
			system("CLS"); // clear screan
			cout << "invalid operation , please select only one of the operations below \n";
			continue;
		}

		while (adminExist)//admin
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


		while (UserIndex != -1)//user
		{
			UserRepository::userMenu();
			int choice3;
			cin >> choice3;
			if (choice3 == 1) // search
			{

			}
			else if (choice3 == 2) // display latest news
			{

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
