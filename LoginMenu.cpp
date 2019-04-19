//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "LoginMenu.h"

LoginMenu::LoginMenu(const string& title, Application* app) : Menu(title, app)
{
  // Precondition:
  // Postcondition: LoginMenu object is created, all member variables are initialized, Menu drawn to screen.

  assert(true);

  Paint();
}

LoginMenu::~LoginMenu()
{
  // Precondition:
  // Postcondition: LoginMenu object is destroyed.

  assert(true);
}

void LoginMenu::OutputOptions()
{
  // Precondition: Application must exist and be valid.
  // Postcondition: LoginMenu specific options are displayed to the user.

  assert(app != nullptr);

  if (!app->IsAccountLoggedIn()) // If there is no currently logged in account, allow the user to log one in.
  {
    PickOption(Option::LogIn, "Log in with email address");
    Line();
    PickOption(Option::CreateNewAccount, "Sign up for a new account");
  }
  else // An account is logged in
  {
    if (!app->IsUserLoggedIn()) // If there is no current user of that account logged in, show a list of the users available.
      DisplayAccountUsers();
    else // If there is a user logged in, allow them to log out of user/account.
    {
      Line("Currently logged in as " + app->GetCurrentUser()->GetUsername());
      Line();
      PickOption(Option::Change, "Change user");
    }
    Line();
    PickOption(Option::LogOut, "Logout of account");
  }
}

bool LoginMenu::HandleChoice(char choice)
{
  // Precondition: Application must exist and be valid.
  // Postcondition: LoginMenu specific options are handled appropriately.

  assert(app != nullptr);

  switch (choice)
  {
  case (char)Option::LogIn:
    if (!app->IsAccountLoggedIn()) // If theres no account logged in, let them log in.
      AttemptAccountLogin();
    else if (Utils::ConfirmUserChoice()) // If there is an account logged in, let them log out.
      app->LogoutAccount();
    break;
  case (char)Option::Change:
    if (app->IsUserLoggedIn() && Utils::ConfirmUserChoice()) // If theres a user logged in, let them log out of that user
      app->LogoutUser();
    break;
  case (char)Option::CreateNewAccount:
    AttemptAccountCreation();
    break;

  default:
    if (app->IsAccountLoggedIn()) // Nico - Only allow them to select a user if they are actively logged into an account already
    {
      char userNum = Utils::CharToInt(choice) - 1;
      if (userNum > -1 && userNum < app->GetCurrentAccount()->GetUsers()->length())
        AttemptUserLogin(userNum);
    }
    break;
  }
  return false;
}

void LoginMenu::AttemptAccountLogin()
{
  // Precondition: Application must exist and be valid.
  // Postcondition: An account login attempt is made using details entered by the user.

  assert(app != nullptr);

  string email, password;
  email = Question("Enter email address: ");
  password = Question("Enter password: ");
  app->LoginAccount(email, password);
}

void LoginMenu::AttemptUserLogin(int userSelection)
{
  // Precondition: Application must exist and be valid,
  //               Application must have an account logged in,
  //               userSelection must be a valid index for one of the active Account's users.
  // Postcondition: A login attempt is made using a password entered by the user.

  assert((app != nullptr) &&
    (app->GetCurrentAccount() != nullptr) &&
    (userSelection > -1) && (userSelection < app->GetCurrentAccount()->GetUsers()->length()));

  string password = Question("Enter password: ");
  app->LoginUser(app->GetCurrentAccount()->GetUser(userSelection)->GetUsername(), password);
}

void LoginMenu::DisplayAccountUsers()
{
  // Precondition: Application must exist and be valid, Application must have an account logged in.
  // Postcondition: All users belonging to the current account are displayed on screen next to a command key value to select them.

  assert((app != nullptr) && (app->GetCurrentAccount() != nullptr));

  Line("Select your username - " + app->GetCurrentAccount()->GetEmail());
  for (int i = 0; i < app->GetCurrentAccount()->GetUsers()->length(); i++)
  {
    PickOption(i + 1, app->GetCurrentAccount()->GetUser(i)->GetUsername());
  }
}

void LoginMenu::AttemptAccountCreation()
{
  string email = Question("Enter desired email address: ");
  string accPassword = Question("Enter desired account password: ");
  string username = Question("Enter desired administrator username: ");
  string password = Question("Enter desired administrator password: ");
  app->CreateNewAccount(email, accPassword, username, password);
}
