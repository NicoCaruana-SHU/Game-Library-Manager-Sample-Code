//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "Menu.h"

Menu::Menu(const string& title, Application* app) :
  title_(title), app(app)
{
  // Precondition:
  // Postcondition: Menu object is created, all member variables are initialized.

  assert(true);
}

Menu::~Menu()
{
  // Precondition:
  // Postcondition: Menu object is destroyed.

  assert(true);
}

void Menu::Paint()
{
  // Precondition:
  // Postcondition: Menu data is rendered to the screen, user is asked for input.

  assert(true);

  bool readyToGoBack = false;

  while (!readyToGoBack)
  {
    Header();
    OutputOptions();
    Line();
    PickOption(Option::Back, "Back");
    Footer();

    char choice = Utils::GetCharFromUser();

    if (choice == (char)Option::Back)
      readyToGoBack = true;
    else
      readyToGoBack = HandleChoice(choice);
  }
}

void Menu::Line() const
{
  // Precondition:
  // Postcondition: New line is output to cout.

  assert(true);

  std::cout << '\n';
}

void Menu::Line(const std::string & text) const
{
  // Precondition:
  // Postcondition: The argument passed in is output to cout.

  assert(true);

  std::cout << "  " << text << "\n";
}

void Menu::PickOption(Option option, const string & message) const
{
  // Precondition:
  // Postcondition: The character assigned to the option argument passed in is output to cout, and the message.

  assert(true);

  std::cout << "  " << (char)option << ") " << message << '\n';
}

void Menu::PickOption(int option, const string & message) const
{
  // Precondition:
  // Postcondition: The character assigned to the option argument passed in is output to cout, and the message.

  assert(true);

  std::cout << "  " << option << ") " << message << '\n';
}

std::string Menu::Question(const string & question) const
{
  // Precondition:
  // Postcondition: The question argument passed in is output to cout, user is prompted for input, which is then returned as a string.

  assert(true);

  std::cout << "  " << question;
  return Utils::GetLineFromUser();
}

void Menu::Header()
{
  // Precondition:
  // Postcondition: The default header layout is passed into cout.

  assert(true);

#if defined _WIN32 || defined _WIN64
  // we are running on windows so use CLS to clear the screen
  system("CLS");
#else
  // we are running on mac or linux so use CLEAR to clear the screen
  system("CLEAR");
#endif

  std::cout << '\n';
  std::cout << "  -= " << title_ << " =-  \n";
  std::cout << '\n';
}

void Menu::Footer()
{
  // Precondition:
  // Postcondition: The default footer layout is passed into cout.

  assert(true);

  std::cout << '\n';
  std::cout << '\n';
  std::cout << "  >>> ";
}