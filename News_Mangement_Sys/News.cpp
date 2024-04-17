#include "News.h"
#include <ctime>
#include <vector>

vector<News> News::news; // main data structure to store all news

News::News(string title, string description, string category, float rate)
{
    time_t now = time(0);
    this->date = localtime(&now);
    this->title = title;
    this->description = description;
    this->category = category;
    this->rate = rate;
    news.push_back(*this);
}

News::News(string title, string description, string category)
{
    time_t now = time(0);
    this->date = localtime(&now);
    this->title = title;
    this->description = description;
    this->category = category;
    news.push_back(*this);
}

float News::getRate()
{
    return this->rate;
}

string News::getTitle()
{
    return this->title;
}

string News::getDescription()
{
    return this->description;
}

string News::getCategory()
{
    return this->category;
}

string News::getDate()
{
    return to_string(this->date->tm_mday) + "/" + to_string(this->date->tm_mon + 1) + "/" + to_string(this->date->tm_year + 1900);
}
