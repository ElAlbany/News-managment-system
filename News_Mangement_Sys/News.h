#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
class News
{
	string title;
	string description;
	tm *date;
	string category;
	float rate;				  // this is the actual rate comes from summing rates and divied on their size
	map<string, int> allRate; // username and his rate // rates can be edited so we need the username ,so map is convenient for that

public:
	static vector<News> news; // main data structure to store all news

	// Constructors
	News(string title, string description, string category, float rate);
	News(string title, string description, string category);

	// Getters
	float getRate();
	string getTitle();
	string getDescription();
	string getCategory();
	string getDate();

	// Display News sorted by [rating, date]
	static bool sortNewsByRating(News &news1, News &news2)
	{
		return news1.getRate() > news2.getRate();
	}
	static bool sortNewsByDate(News &news1, News &news2)
	{
		return news1.getDate() > news2.getDate();
	}
	static void displayLatestNews()
	{
		sort(News::news.begin(), News::news.end(), News::sortNewsByDate);
		for (int i = 0; i < (int)News::news.size(); i++)
		{
			cout << "[" << i << "] " << News::news[i].getTitle() << " : " << News::news[i].getDescription() << " \n\tDate : " << News::news[i].getDate() << " \n\tRating : " << News::news[i].getRate() << " \n\tCategory : " << News::news[i].getCategory() << endl;
		}
	}
	static void displayTrendingNews()
	{
		sort(News::news.begin(), News::news.end(), News::sortNewsByRating);
		for (int i = 0; i < (int)News::news.size(); i++)
		{
			cout << "[" << i << "] " << News::news[i].getTitle() << " : " << News::news[i].getDescription() << " \n\tDate : " << News::news[i].getDate() << " \n\tRating : " << News::news[i].getRate() << " \n\tCategory : " << News::news[i].getCategory() << endl;
		}
	}
};
