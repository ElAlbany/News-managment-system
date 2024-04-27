#include <iostream>
#include "UserRepository.h"
using namespace std;

void UserRepository::adminMenu()
{
	cout << "\twelcome to admin menu\n";
	cout << "Here is all admin operations \n";
	cout << "please select one of the operations below\n\n\n";
	cout << "[1] add new category \n";
	cout << "[2] post news \n";
	cout << "[3] remove news \n";
	cout << "[4] update news \n";
	cout << "[5] display an article rate\n";
	cout << "[6] display all news\n";
	cout << "[7] add new admin \n";
	cout << "[8] remove admin\n";
	cout << "[9] log out\n";
}

void UserRepository::userMenu()
{
	cout << "\twelcome to user menu\n";
	cout << "Here is all user operations \n";
	cout << "please select one of the operations below\n\n\n";
	cout << "[1] search  \n";
	cout << "[2] display latest news \n";
	cout << "[3] search by category \n";
	cout << "[4] rate news \n";
	cout << "[5] bookmarking\n";
	cout << "[6] trending news\n";
	cout << "[7] log out\n";
}
