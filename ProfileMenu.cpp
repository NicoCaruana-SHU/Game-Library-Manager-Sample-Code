//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "ProfileMenu.h"

ProfileMenu::ProfileMenu(const string& title, Application* app)
  :Menu(title, app)
{
  // Precondition:
  // Postcondition: ProfileMenu object is created, all member variables are initialized, Menu drawn to screen.

  assert(true);

  Paint();
}

ProfileMenu::~ProfileMenu()
{
  // Precondition:
  // Postcondition: ProfileMenu object is destroyed.

  assert(true);
}

void ProfileMenu::OutputOptions()
{
  // Precondition: Application must exist and be valid, user must be logged in.
  // Postcondition: ProfileMenu specific options are displayed to the user.

  assert(app != nullptr && app->IsUserLoggedIn());

  DisplayOwnedGames();
  DisplayCreditPurchaseOptions();
  if (typeid(*app->GetCurrentUser()) == typeid(Admin)) // If the user is an administrator of the account, show additional options.
    DisplayAdministratorOptions();
}

bool ProfileMenu::HandleChoice(char choice)
{
  // Precondition: Application must exist and be valid, user must be logged in.
  // Postcondition: ProfileMenu specific options are handled appropriately.

  assert(app != nullptr && app->IsUserLoggedIn());

  switch (choice)
  {
  case (char)Option::Play:
  {
    LibraryItem* gameOfChoice = ((Player*)app->GetCurrentUser())->GetOwnedItem(
      Utils::ToInt(Question("Game number: ")) - 1);
    if (gameOfChoice != nullptr)
      gameOfChoice->PlayGame();
  }
  break;
  case (char)Option::SortByName:
    ((Player*)app->GetCurrentUser())->
      SortItems(Filter::SortingMode::Name);
    break;
  case (char)Option::SortByDate:
    ((Player*)app->GetCurrentUser())->
      SortItems(Filter::SortingMode::Date);
    break;
  case (char)Option::AddFilter:
    ((Player*)app->GetCurrentUser())->AddFilter(
      Question("Filter name: "));
    break;
  case (char)Option::RemoveFilter:
  {
    Player* currentPlayer = (Player*)app->GetCurrentUser();
    if (currentPlayer->GetFilterCount() > 1)
      currentPlayer->RemoveFilter(
        Utils::ToInt(Question("Filter number: ")));
  }
  break;
  case (char)Option::MoveToFilter:
  {
    Player* currentPlayer = (Player*)app->GetCurrentUser();
    if (currentPlayer->GetFilterCount() > 1)
    {
      string game = Question("Game number: ");
      string filter = Question("Filter number: ");
      currentPlayer->MoveToFilter(
        Utils::ToInt(game) - 1, Utils::ToInt(filter));
    }
  }
  break;
  case (char)Option::PurchaseSmallCredit:
    app->GetCurrentUser()->AddCredit(100);
    break;
  case (char)Option::PurchaseMediumCredit:
    app->GetCurrentUser()->AddCredit(500);
    break;
  case (char)Option::PurchaseLargeCredit:
    app->GetCurrentUser()->AddCredit(1000);
    break;
  case (char)Option::AddUser:
    if (typeid(*app->GetCurrentUser()) == typeid(Admin))
    {
      string username = Question("Enter desired username: ");
      string password = Question("Enter desired password: ");
      app->GetCurrentAccount()->AddUser(username, password);
    }
    break;
  case (char)Option::RemoveUser:
    if (typeid(*app->GetCurrentUser()) == typeid(Admin))
      RemoveUserMenu("Remove User", app);
    break;
  case (int)Option::ManageGuestAccess:
    // TODO - Nico _ Not yet implemented
    break;
  default:
    break;
  }
  return false;
}

void ProfileMenu::DisplayCreditPurchaseOptions() const
{
  // Precondition: Application must exist and be valid, user must be logged in.
  // Postcondition: Credit purchase options are displayed on screen.

  assert(app != nullptr && app->IsUserLoggedIn());

  Line("Credits: " + to_string(app->GetCurrentUser()->GetCreditBalance()));
  PickOption(Option::PurchaseSmallCredit, "Purchase 100 credits (\x9C"  "1 Value)");
  PickOption(Option::PurchaseMediumCredit, "Purchase 500 credits (\x9C" "5 Value)");
  PickOption(Option::PurchaseLargeCredit, "Purchase 1000 credits (\x9C" "10 Value)");
  Line();
}

void ProfileMenu::DisplayOwnedGames() const
{
  // Precondition: Application must exist and be valid, user must be logged in.
  // Postcondition: Owned games and related sorting options are displayed on screen.

  assert(app != nullptr && app->IsUserLoggedIn());

  Player * player = (Player*)app->GetCurrentUser();
  Line("Games");
  if (player->GetItemCount() > 0) // TODO Error, no point displaying game related options when user has no games. Temp fix in
  {
    PickOption(Option::Play, "Play a game");
    PickOption(Option::SortByName, "Sort by name");
    PickOption(Option::SortByDate, "Sort by date");
    PickOption(Option::AddFilter, "Add a new filter");
	Line();
    size_t filterCount = player->GetFilterCount();
    if (filterCount > 0)// TODO Error when no games/filters are set up - Temporary fix in
    {
	  if (filterCount > 1)
	  {
		 PickOption(Option::RemoveFilter, "Remove a filter");
	  	 PickOption(Option::MoveToFilter, "Add a game to a filter");
	  }
      for (long long itemIndex = 0, filterIndex = filterCount - 1;
        filterIndex >= 0; --filterIndex)
      {
        const Filter* currentFilter = player->GetFilter(filterIndex);
        if (filterIndex)
        {
          Line();
          Line(currentFilter->GetName() + ":");
        }
        size_t itemCount = currentFilter->GetItemCount();
		if (itemCount == 0)
			PickOption(Option::Error, "Empty");
        else 
			for (long long actualItemIndex = 0; actualItemIndex < itemCount; ++itemIndex, ++actualItemIndex)
          PickOption(itemIndex + 1, player->GetOwnedItem(itemIndex)->GetGame()->GetName() + " -> " + Utils::FormatPlaytime(player->GetOwnedItem(itemIndex)->GetPlaytime()));
        if (filterIndex)
          Line("---------------------------");
      }
      Line();
    }
  }
  else {
    Line("You do not currently own any games, please visit the store to purchase some.");
    Line();
  }

}

void ProfileMenu::DisplayAdministratorOptions() const
{
  // Precondition: Application must exist and be valid, user must be logged in, user is an administrator of the account.
  // Postcondition: Profile administration options are displayed on screen.

  assert(app != nullptr && app->IsUserLoggedIn() && typeid(*app->GetCurrentUser()) == typeid(Admin));

  Line("Administrator");
  PickOption(Option::AddUser, "Add new user");
  PickOption(Option::RemoveUser, "Remove user");
  PickOption(Option::ManageGuestAccess, "Manage guest's access");
  Line();
}
