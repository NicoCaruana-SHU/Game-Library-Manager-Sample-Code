//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef UserH
#define UserH

#include "Date.h"
#include "ISerializable.h"
#include "Utils.h"

#include <string>
#include <cassert>

using namespace std;

class User : public ISerializable
{
public:
  User(const string&, const string&, const string&, int);
  User(const Date*, const string&, const string&, int);
  virtual ~User();
  const bool IsValidPassword(const string& input) const;
  int GetCreditBalance() const;
  const string& GetUsername() const;

  void AddCredit(int amount);
  void RemoveCredit(int amount);

  std::ostream& ToStream(std::ostream& os) const override;

private:
  string username_;
  string password_;
  const Date* pDateCreated_; // Owned by the user, needs to be manually deleted
  int credits_;

  bool HasEnoughCreditToPurchase(int cost) const;
};
#endif