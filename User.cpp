//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "User.h"

User::User(const string& created, const string& username, const string& password, int credits) :
  username_(username), password_(password), pDateCreated_(Date::CreateDate(created)), credits_(credits)
{

}User::User(const Date* created, const string& username, const string& password, int credits) :
  username_(username), password_(password), pDateCreated_(created), credits_(credits)
{

}

User::~User()
{
  delete pDateCreated_;
}

const string& User::GetUsername() const
{
  return username_;
}

const bool User::IsValidPassword(const string& input) const
{
  return input == password_;
}

int User::GetCreditBalance() const
{
  return credits_;
}

void User::AddCredit(int amount)
{
  assert(amount > 0);
  credits_ += amount;
}

void User::RemoveCredit(int amount)
{
  assert(amount > 0 && HasEnoughCreditToPurchase(amount));
  credits_ -= amount;
}

std::ostream& User::ToStream(std::ostream& os) const
{
  os << "ACCOUNT-USER\n" << (*pDateCreated_) << '\n' << username_ << '\n' << password_ << '\n' << Utils::ToString(credits_) << '\n';
  return os;
}

bool User::HasEnoughCreditToPurchase(int cost) const
{
  return credits_ >= cost;
}
