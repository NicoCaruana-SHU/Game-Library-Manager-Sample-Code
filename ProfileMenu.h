//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef ProfileMenuH
#define ProfileMenuH

#include "Menu.h"     // For base class inheritance.
#include "RemoveUserMenu.h" // Nico - To allow us to transition to the admin remove user choices

#include <typeinfo>   // For the safe usage of typeid to determine derived class type from base class pointer.

#include <cassert>  // For debugging purposes.

/// <summary>
/// ProfileMenu provides display and handling of options related to viewing a user profile.
/// <para>
/// </para>
/// </summary>
class ProfileMenu final : public Menu
{
public:
  /// <summary>
  /// Create an instance of ProfileMenu class.
  /// </summary>
  /// In:
  /// <param name="title">String to be displayed in the Menu's header</param>
  /// <param name="app">Pointer to the application.</param>
  /// Out:
  /// <returns></returns>
  ProfileMenu(const string& title, Application* app);

  /// <summary>
  /// Destroys the ProfileMenu instance.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  ~ProfileMenu();

  /// <summary>
  /// Overriden inherited virtual function, outputs all the options specific to ProfileMenu.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void OutputOptions() final;

  /// <summary>
  /// Overriden inherited virtual function, handles all the options specific to ProfileMenu.
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
  /// Display credit purchase options on screen.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void DisplayCreditPurchaseOptions() const;

  /// <summary>
  /// Display user's owned games and their related sorting options on screen.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void DisplayOwnedGames() const;

  /// <summary>
  /// Display administrator options on screen.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void DisplayAdministratorOptions() const;
};
#endif // !ProfileMenuH
