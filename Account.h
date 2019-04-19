//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef AccountH
#define AccountH

#include "ISerializable.h"  // For base class inheritance.

#include "Player.h"
#include "Admin.h"
#include "ListT.h"          // For storage of the list of users attached to the account.
#include "Date.h"           // For storage of the account creation date.

#include <cassert>          // For debugging purposes.

class Account : public ISerializable
{
public:
  Account(const string& created, const string& email, const string& password);
  Account(const Date* created, const string& email, const string& password);
  ~Account();

  const string& GetEmail() const;
  bool IsValidPassword(const string& input) const;
  User* GetUser(size_t index) const;
  List<User*>* GetUsers();

  void AddAdministrator(const string& userName, const string& password, int credits = 0);
  void AddUser(const string& userName, const string& password, int credits = 0);
  void RemoveUser(User* user);

  std::ostream& ToStream(std::ostream& os) const override;
  //std::istream& FromStream(std::istream& is) override;

private:
  List<User*> users_; // Owned by the account, need to be manually deleted
  string email_;
  string password_;
  const Date* pDateCreated_;  // Owned by the account, need to be manually deleted
};
#endif // !AccountH
