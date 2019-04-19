//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef MenuH
#define MenuH

#include "Utils.h"          // For access to the generic functions to get user input.
#include "Application.h"    // For access to application specific functions in derived classes.

#include <cassert>          // For debugging purposes.

/// <summary>
/// Abstract class providing interace functions to create specialised menu objects.
/// <para>
/// </para>
/// </summary>
class Menu
{
public:
  /// <summary>
  /// Create the Menu base class as part of a derived class.
  /// </summary>
  /// In:
  /// <param name="title">String to be displayed in the Menu's header</param>
  /// <param name="app">Pointer to the application.</param>
  /// Out:
  /// <returns></returns>
  Menu(const string& title, Application* app);

  /// <summary>
  /// Destroy the Menu base class, virtual to allow derived classes to be deleted safely polymorphically.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  virtual ~Menu();

  /// <summary>
  /// Display the menu.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void Paint();

  /// <summary>
  /// Pure virtual function, to be overriden by derived classes to output all the options specific to themselves.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  virtual void OutputOptions() = 0;

  /// <summary>
  /// Pure virtual function, to be overriden by derived classes to handle the possible choices from the specific menu.
  /// <para>
  /// Returning true means you are ready to go back to the previous menu
  /// </para>
  /// <para>
  /// Returning false means you will stay on the same menu
  /// </para>
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  virtual bool HandleChoice(char) = 0;

protected:
  /// <summary>
  /// Enum class providing reference to Option commands and their corresponding character for use in functions.
  /// </summary>
  enum class Option : char
  {
    LogIn = 'L',
    LogOut = 'L',
    Back = 'B',
    Store = 'S',
    Search = 'D',
    Profile = 'P',
    Buy = 'P',
    Change = 'C',
    Play = 'P',
    SortByName = 'N',
    SortByDate = 'S',
    AddFilter = 'F',
    RemoveFilter = 'D',
    MoveToFilter = 'M',
    PurchaseSmallCredit = 'O',
    PurchaseMediumCredit = 'T',
    PurchaseLargeCredit = 'H',
    AddUser = 'A',
    RemoveUser = 'R',
    ManageGuestAccess = 'G',
    Error = 'X',
    CreateNewAccount = 'N'
  };

  /// <summary>
  /// Pointer to the application, can be used to run application specific functions.
  /// </summary>
  Application* app;

  /// <summary>
  /// Display an empty line.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void Line() const;

  /// <summary>
  /// Display the text passed in.
  /// </summary>
  /// In:
  /// <param name="text">Reference to string containing message to display.</param>
  /// Out:
  /// <returns></returns>
  void Line(const std::string& text) const;

  /// <summary>
  /// Display command text, followed by an additional message on the same line.
  /// </summary>
  /// In:
  /// <param name="option">Enum value for the desired command to display.</param>
  /// <param name="option">Reference to string containing message to display after the command.</param>
  /// Out:
  /// <returns></returns>
  void PickOption(Option option, const string& message) const;

  /// <summary>
  /// Display command text, followed by an additional message on the same line.
  /// </summary>
  /// In:
  /// <param name="option">Integer corresponding for the desired command to display.</param>
  /// <param name="option">Reference to string containing message to display after the command.</param>
  /// Out:
  /// <returns></returns>
  void PickOption(int id, const string& option) const;

  /// <summary>
  /// Display question to user, get their response and return it as a string.
  /// </summary>
  /// In:
  /// <param name="question">Reference to string containing the question to display.</param>
  /// Out:
  /// <returns>String containing the user answer.</returns>
  string Question(const string& question) const;

private:
  /// <summary>
  /// String containing the text to display as the Menu's title in the default header.
  /// </summary>
  string title_;

  /// <summary>
  /// Display default header information.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void Header();

  /// <summary>
  /// Display default footer information.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns></returns>
  void Footer();
};
#endif // !MenuH
