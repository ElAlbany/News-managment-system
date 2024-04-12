#include <iostream>
using namespace std;

int main()
{

	while (true)//main program
	{
		bool adminExist = false; //to chech weather the account is admin
		int UserIndex = -1; // to check weather the account is user and if is not -1 then we have the index to use it in other operations
		int choice;
		cout << "Enter one of the shown operations below\n\n";
		cout << "[1] log in \n[2] sign up \n[3] exit \n";
		
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
		}
		else
		{
			system("CLS"); // clear screan
			cout << "invalid operation , please select only one of the operations below \n";
			continue;
		}

		while(adminExist)//admin
		{

		}


		while (UserIndex !=-1)//user
		{


			
		}
	}
	return 0;
}
