//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "Application.h"

Application::Application()
  : accounts_(), store_(), pCurrentAccount_(nullptr), pCurrentUser_(nullptr), userIsLoggedIn_(false)
{
  // Precondition:
  // Postcondition: Application object is constructed.

  assert(true);
}

Application::~Application()
{
  // Precondition:
  // Postcondition: Each account's memory is deallocated, the account List is cleared and the Application is destroyed .

  assert(true);

  for (int i = 0; i < accounts_.length(); ++i)
    delete accounts_[i];
}

bool Application::IsUserLoggedIn() const
{
  // Precondition:
  // Postcondition: userIsLoggedIn value is returned.

  assert(true);

  return userIsLoggedIn_;
}

bool Application::IsAccountLoggedIn() const
{
  // Precondition:
  // Postcondition: Returns true if an account is assigned to pCurrentAccount.

  assert(true);
  return pCurrentAccount_ != nullptr;
}

Account* Application::GetCurrentAccount() const
{
  // Precondition:
  // Postcondition: Returns pointer to the currently logged in account, or nullptr.

  assert(true);

  return pCurrentAccount_;
}

User* Application::GetCurrentUser() const
{
  // Precondition:
  // Postcondition: Returns pointer to the currently logged in user, or nullptr.

  assert(true);

  return pCurrentUser_;
}

Store* Application::GetStore()
{
  // Precondition: Store object exists.
  // Postcondition: Returns pointer to the store object.

  assert(true);

  return &store_;
}

bool Application::LoginAccount(const string & email, const string & password)
{
  bool emailFound = false;
  bool passwordMatch = false;
  int iterator = 0;
  while (!emailFound && iterator < accounts_.length())
  {
    if (email == accounts_[iterator]->GetEmail())
      emailFound = true;
    else
      ++iterator;
  }
  if (emailFound)
  {
    if (accounts_[iterator]->IsValidPassword(password))
    {
      pCurrentAccount_ = accounts_[iterator];
      passwordMatch = true;
    }
  }
  return emailFound && passwordMatch;
}

void Application::LogoutAccount()
{
  LogoutUser();
  pCurrentAccount_ = nullptr;
}

bool Application::LoginUser(const std::string & username, const std::string & password)
{
  bool usernameFound = false;
  bool passwordMatch = false;
  int iterator = 0;
  while (!usernameFound && iterator < pCurrentAccount_->GetUsers()->length())
  {
    if (username == pCurrentAccount_->GetUser(iterator)->GetUsername())
      usernameFound = true;
    else
      ++iterator;
  }
  if (usernameFound)
  {
    if (pCurrentAccount_->GetUser(iterator)->IsValidPassword(password))
    {
      passwordMatch = true;
      pCurrentUser_ = pCurrentAccount_->GetUser(iterator);
      userIsLoggedIn_ = true;
    }
  }
  return usernameFound && passwordMatch;
}

void Application::LogoutUser()
{
  pCurrentUser_ = nullptr;
  userIsLoggedIn_ = false;
}

void Application::CreateNewAccount(const string & email, const string & accPassword, const string & admin, const string & adminPass)
{
  bool isEmailInUse = false;
  int i = 0;
  while (!isEmailInUse && i < accounts_.length())
  {
    if (accounts_[i]->GetEmail() == email)
    {
      isEmailInUse = true;
    }
    ++i;
  }

  if (!isEmailInUse)
  {
    Account* newAcc = new Account(Date::CurrentDate(), email, accPassword);
    newAcc->AddAdministrator(admin, adminPass);
    accounts_.addAtEnd(newAcc);
  }
}

void Application::Save(const string & fileName)
{
  ofstream fileWriter(fileName);
  size_t gameCount = store_.GetGames()->length();
  for (size_t gameIndex = 0; gameIndex < gameCount; ++gameIndex)
    fileWriter << "GAME" << endl << gameIndex << *(store_.GetGame(gameIndex));
  size_t accountCount = accounts_.length();
  for (size_t accountIndex = 0; accountIndex < accountCount; ++accountIndex)
  {
    fileWriter << *(accounts_[accountIndex]);
    size_t userCount = accounts_[accountIndex]->GetUsers()->length();
    for (size_t userIndex = 0; userIndex < userCount; ++userIndex)
    {
      User* user = accounts_[accountIndex]->GetUser(userIndex);
      fileWriter << *user;
      Player* player = (Player*)user;
      size_t filterCount = player->GetFilterCount();
      for (size_t y = 0; y < filterCount; ++y)
      {
        Filter* filter = player->GetFilter(y);
        fileWriter << *filter;
        size_t itemCount = filter->GetItemCount();
        for (size_t w = 0; w < itemCount; ++w)
        {
          LibraryItem* item = filter->GetOwnedItem(w);
          Game currentUserGame = *item->GetGame();
          fileWriter << "ACCOUNT-USER-GAME" << endl
            << store_.GetGames()->indexOf(&currentUserGame) << *item;
        }
      }
    }
  }
}


void Application::Load(const string & fileName)
{
  FileReader fileReader(fileName, { "GAME", "ACCOUNT", "ACCOUNT-USER",  "FILTER", "ACCOUNT-USER-GAME" });
  vector<tuple<vector<string>, FileReader::EntryType>> entries = fileReader();
  for (const tuple<vector<string>, FileReader::EntryType>& entry : entries)
  {
    vector<string> entryData = get<0>(entry);
    switch (get<1>(entry))
    {

    case FileReader::EntryType::Game:
      store_.GetGames()->addAtEnd(new Game(entryData.at(0), entryData.at(1),
        Utils::ToInt(entryData.at(2)), Utils::ToInt(entryData.at(3))));
      break;
    case FileReader::EntryType::Account:
      accounts_.addAtEnd(new Account(entryData.at(0), entryData.at(1), entryData.at(2)));
      break;
    case FileReader::EntryType::User:
      assert(accounts_.length());
      if (accounts_.last()->GetUsers()->length())
        accounts_.last()->GetUsers()->addAtEnd(new Player(entryData.at(0), entryData.at(1),
          entryData.at(2), Utils::ToInt(entryData.at(3))));
      else
        accounts_.last()->GetUsers()->addAtEnd(new Admin(entryData.at(0), entryData.at(1),
          entryData.at(2), Utils::ToInt(entryData.at(3))));
      break;
    case FileReader::EntryType::Filter:
      assert(accounts_.length());
      assert(accounts_.last()->GetUsers()->length());
      ((Player*)accounts_.last()->GetUsers()->last())->
        AddFilter(entryData.at(0));
      break;
    case FileReader::EntryType::Item:
      assert(accounts_.length());
      assert(accounts_.last()->GetUsers()->length());
      Player* currentPlayer = ((Player*)accounts_.last()->GetUsers()->last());
      size_t filterCount = currentPlayer->GetFilterCount();
      assert(filterCount);
      assert(store_.GetGames()->length() > Utils::ToInt(entryData.at(0)));
      (*currentPlayer->GetFilter(filterCount - 1)).AddItem(
        new LibraryItem(store_.GetGame(Utils::ToInt(entryData.at(0))),
          entryData.at(1), Utils::ToInt(entryData.at(2))));
      break;
    }
  }
}
