#pragma once
#include<iostream>
#include<vector>
#include<map>
using namespace std;


class Utility {
private:

public:
	/// <summary>
	/// checks if char belongs to {'1','2',..,'9'}
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	static bool isDigitChar(char c);

	/// <summary>
	/// returns true if the format is right else false
	/// </summary>
	/// <param name="date">the date string</param>
	/// <returns>boolean value</returns>
	static bool checkDateFormat(string date); // check if the date is like the format: dd/mm/yyyy 12/3/2023 


	static string toString(int num);
	static int toInt(string str);


};

