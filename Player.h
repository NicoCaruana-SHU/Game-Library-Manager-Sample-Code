//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef PlayerH
#define PlayerH

#include "Filter.h"
#include "User.h"

class Player : public User
{
public:
  Player(const string&, const string&, const string&, int);
  Player(const Date*, const string&, const string&, int);
  ~Player();
  void SortItems(Filter::SortingMode algorithm);
  void AddFilter(const string& name);
  void RemoveFilter(size_t index);
  void MoveToFilter(size_t gameIndex, size_t filterIndex);
  void AddItem(LibraryItem* ownedItem);
  bool HasGame(Game* game) const;
  size_t GetFilterCount() const;
  size_t GetItemCount() const;
  Filter* GetFilter(size_t index);
  LibraryItem* GetOwnedItem(size_t index) const;
private:
  vector<Filter> filters_;
};
#endif