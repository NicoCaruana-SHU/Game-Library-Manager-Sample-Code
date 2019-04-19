//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef ApplicationH
#define ApplicationH

#include "Account.h"      // For storage of the user accounts of the application, as well as operations for the current account.
#include "User.h"         // For operations involving the current user.
#include "Store.h"        // For storage of the store inventory
#include "FileReader.h"   // For Loading/Saving
#include "Utils.h"        // For access to data conversion functions (toint) used in the application load functions.
#include "ListT.h"        // For storage of the user accounts of the application with advanced container operations.

#include <cassert>        // For debugging purposes

/// <summary>
/// Main data class for the program, stores all state info within.
/// <para>
/// Contains functions for Loading and Saving state information.
/// </para>
/// <para>
/// Also has functions to log users/accounts in and out, modifiying the program states.
/// </para>
/// </summary>
class Application
{
public:
  Application();
  ~Application();

#pragma region Accessor Functions

  /// <summary>
  /// Check if an account is currently logged in.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns true if an account is currently logged in.</returns>
  bool IsAccountLoggedIn() const;

  /// <summary>
  /// Check if a user is currently logged in.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns true if a user is currently logged in.</returns>
  bool IsUserLoggedIn() const;

  /// <summary>
  /// Get a pointer to the currently logged in account.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns pointer to the currently logged in account, or nullptr.</returns>
  Account* GetCurrentAccount() const;

  /// <summary>
  /// Get a pointer to the currently logged in user.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns pointer to the currently logged in user, or nullptr.</returns>
  User* GetCurrentUser() const;

#pragma endregion Accessor Functions

  /// <summary>
  /// Get a pointer to the store object.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns pointer to the store object.</returns>
  Store* GetStore();

  bool LoginAccount(const string& email, const string& password);
  void LogoutAccount();
  bool LoginUser(const string& username, const string& password);
  void LogoutUser();

  void CreateNewAccount(const string& email, const string& accPassword, const string& admin, const string& adminPass);

  void Save(const string& fileName);
  void Load(const string& fileName);

private:
  List<Account*> accounts_;
  Store store_;
  Account* pCurrentAccount_;
  User* pCurrentUser_;
  bool userIsLoggedIn_;
};
#endif // !ApplicationH
