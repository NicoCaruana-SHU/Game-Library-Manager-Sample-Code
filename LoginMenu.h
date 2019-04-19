//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef LoginMenuH
#define LoginMenuH

#include "Menu.h"   // For base class inheritance.

#include <cassert>  // For debugging purposes

/// <summary>
/// LoginMenu provides display and handling of options related to logging in the store.
/// <para>
/// </para>
/// </summary>
class LoginMenu final : public Menu
{
public:
  /// <summary>
  /// Create an instance of LoginMenu class.
  /// </summary>
  /// In:
  /// <param name="title">String to be displayed in the Menu's header</param>
  /// <param name="app">Pointer to the application.</param>
  /// Out:
  /// <returns></returns>
  LoginMenu(const string& title, Application* app);

  /// <summary>
  /// Destroys the LoginMenu instance.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  ~LoginMenu();

  /// <summary>
  /// Overriden inherited virtual function, outputs all the options specific to LoginMenu.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void OutputOptions() final;

  /// <summary>
  /// Overriden inherited virtual function, handles all the options specific to LoginMenu.
  /// <para>
  /// Returning true means you are ready to go back to the previous menu
  /// </para>
  /// <para>
  /// Returning false means you will stay on the same menu
  /// </para>
  /// </summary>
  /// In:
  /// <param name="choice">Character corresponding to the user's desired course of action.</param>
  /// Out:
  /// <returns></returns>
  bool HandleChoice(char choice) final;

private:
  /// <summary>
  /// Prompt the user to enter an email address and password, then attempt to login to an account with their repsonse.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void AttemptAccountLogin();

  /// <summary>
  /// Prompt the user to enter a password, then attempt to login to a user with the user index and their password repsonse.
  /// </summary>
  /// In:
  /// <param name="userSelection">Integer representing the user's index in the account storage container</param>
  /// Out:
  /// <returns></returns>
  void AttemptUserLogin(int userSelection);

  /// <summary>
  /// All users belonging to the current account are displayed on screen next to a command key value to select them.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void DisplayAccountUsers();

  void AttemptAccountCreation();
};

#endif // !LoginMenuH
