//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "Account.h"

Account::Account(const string& created, const string& email, const string& password) :
  email_(email), password_(password), pDateCreated_(Date::CreateDate(created))
{

}

Account::Account(const Date* created, const string& email, const string& password) :
  email_(email), password_(password), pDateCreated_(created)
{

}

Account::~Account()
{
  for (int i = 0; i < users_.length(); ++i)
    delete users_[i];
  delete pDateCreated_;
}

const string& Account::GetEmail() const
{
  return email_;
}

bool Account::IsValidPassword(const string & input) const
{
  return input == password_;
}

User* Account::GetUser(size_t index) const
{
  return users_[index];
}

List<User*>* Account::GetUsers()
{
  return &users_;
}

void Account::AddAdministrator(const string& userName, const string& password, int credits)
{
  users_.addAtEnd(new Admin(Date::CurrentDate(), userName, password, credits));
  ((Player*)users_.last())->AddFilter("Global");
}

void Account::AddUser(const string & userName, const string & password, int credits)
{
  users_.addAtEnd(new Player(Date::CurrentDate(), userName, password, credits));
  ((Player*)users_.last())->AddFilter("Global");
}

void Account::RemoveUser(User * user)
{
  assert(user);
  users_.deleteOne(user);
  delete user;
}

std::ostream& Account::ToStream(std::ostream & os) const
{
  os << "ACCOUNT\n" << (*pDateCreated_) << '\n' << email_ + '\n' << password_ + '\n';
  return os;
}

