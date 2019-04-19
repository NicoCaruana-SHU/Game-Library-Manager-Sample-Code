//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "Player.h"


Player::Player(const string& created, const string& username, const string& password, int credits) :
  User(created, username, password, credits)
{
  filters_.reserve(16);
}

Player::Player(const Date* created, const string& username, const string& password, int credits) :
  User(created, username, password, credits)

{
  filters_.reserve(16);
}

Player::~Player()
{

}

void Player::SortItems(Filter::SortingMode mode)
{
  for (Filter& filter : filters_)
    filter.Sort(mode);
}

void Player::AddFilter(const string & name)
{
  filters_.emplace_back(name);
}

void Player::RemoveFilter(size_t index)
{
  size_t actualIndex = filters_.size() - index;
  if (actualIndex && actualIndex < filters_.size())
  {
    vector<LibraryItem*>& gloabalItems = filters_.at(0).GetOwnedItems();
    vector<LibraryItem*>& filteredItems = filters_.at(actualIndex).GetOwnedItems();
    gloabalItems.insert(gloabalItems.end(),
      std::make_move_iterator(filteredItems.begin()),
      std::make_move_iterator(filteredItems.end()));
    filteredItems.clear();
    filters_.erase(filters_.begin() + actualIndex);
  }
}

void Player::MoveToFilter(size_t gameIndex, size_t filterIndex)
{
  size_t currentGameIndex = gameIndex;
  size_t filterCount = filters_.size();
  size_t actualFilterIndex = filterCount - filterIndex;
  if (actualFilterIndex && actualFilterIndex < filters_.size())
    for (long long currentFilterIndex = filterCount - 1; currentFilterIndex >= 0; --currentFilterIndex)
    {
      size_t currentFilterSize = filters_.at(currentFilterIndex).GetItemCount();
      if (currentGameIndex >= currentFilterSize)
        currentGameIndex -= currentFilterSize;
      else
      {
        filters_.at(actualFilterIndex).AddItem(filters_.at(currentFilterIndex).RemoveItem(currentGameIndex));
        break;
      }
    }
}

void Player::AddItem(LibraryItem * ownedItem)
{
  filters_.at(0).AddItem(ownedItem);
}

bool Player::HasGame(Game * game) const
{
  for (const Filter& filter : filters_)
    if (filter.HasGame(game))
      return true;
  return false;
}

size_t Player::GetFilterCount() const
{
  return filters_.size();
}

size_t Player::GetItemCount() const
{
  size_t itemCount = 0;
  for (const Filter& filter : filters_)
    itemCount += filter.GetItemCount();
  return itemCount;
}

Filter* Player::GetFilter(size_t index)
{
  return &filters_.at(index);
}

LibraryItem* Player::GetOwnedItem(size_t index) const
{
  size_t currentIndex = index;
  size_t filterCount = filters_.size();
  for (long long filterIndex = filterCount - 1; filterIndex >= 0; --filterIndex)
  {
    size_t currentFilterSize = filters_.at(filterIndex).GetItemCount();
    if (currentIndex >= currentFilterSize)
      currentIndex -= currentFilterSize;
    else
      return filters_.at(filterIndex).GetOwnedItem(currentIndex);
  }
  return nullptr;
}
