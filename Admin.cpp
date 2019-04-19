//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "Admin.h"

Admin::Admin(const Date* created, const string& username, const string& password, int credits) :
  Player(created, username, password, credits)
{

}

Admin::Admin(const string& created, const string& username, const string& password, int credits) :
  Player(created, username, password, credits)
{

}

Admin::~Admin()
{

}