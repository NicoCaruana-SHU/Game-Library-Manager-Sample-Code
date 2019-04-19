//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef AdminrH
#define AdminrH

#include <string>
#include "Player.h"

using namespace std;

class Admin : public Player
{
public:
  Admin(const Date*, const string&, const string&, int credits);
  Admin(const string&, const string&, const string&, int credits);
  ~Admin();
};
#endif 