//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "Date.h"

const int Date::daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(int year, int month, int day)
  : year_(year), month_(month), day_(day), totalDays_(CalculateNumberOfDays(*this))
{
  // Precondition: year, month and date must be a valid date.
  // Postcondition: Date object is created with the appropriate values based on the parameters passed in.

  assert(IsValidDate(year, month, day));
}

Date::~Date()
{
  // Precondition:
  // Postcondition: Date object is destroyed.

  assert(true);
}

#pragma region Accessor Functions

int Date::GetYear() const
{
  // Precondition:
  // Postcondition: Year value returned.

  assert(true);

  return year_;
}

int Date::GetMonth() const
{
  // Precondition:
  // Postcondition: Month value returned.

  assert(true);

  return month_;
}

int Date::GetDay() const
{
  // Precondition:
  // Postcondition: Day value returned.

  assert(true);

  return day_;
}

#pragma endregion Accessor Functions

#pragma region Operator Overloads

bool Date::operator==(const Date& rhs) const
{
  // Precondition: This date and the rhs date passed in must be valid.
  // Postcondition: True returned if both dates contain the same value, otherwise False.

  assert(IsValidDate(*this) && IsValidDate(rhs));

  return year_ == rhs.year_ && month_ == rhs.month_ && day_ == rhs.day_;
}

bool Date::operator!=(const Date& rhs) const
{
  // Precondition: This date and the rhs date passed in must be valid.
  // Postcondition: True returned if both dates do not contain the same value, otherwise False.

  assert(IsValidDate(*this) && IsValidDate(rhs));

  return !(*this == rhs);
}

bool Date::operator<(const Date & rhs) const
{
  // Precondition: This date and the rhs date passed in must be valid.
  // Postcondition: True returned if this date is earlier than the rhs date object, otherwise False.

  assert(IsValidDate(*this) && IsValidDate(rhs));

  return !(*this > rhs);
}

/*bool Date::operator>(const Date & rhs) const
{
  //years * 365

  //	months 2: 28
  //	4,6,9,11 : 30
  //	1,3,5,7,8,10,12 : 31

  //	switch (m_months) {
  //	case 1:
  //		//add nothing
  //	case 2:
  //		//add 31
  //	case 3:
  //		//add 31 and 28
  //	}

  bool bigger = false;
  if (m_year > rhs.m_year)
  {
    bigger = true;
  }
  else {
    if (m_year == rhs.m_year)
    {
      if (m_month > rhs.m_month)
      {
        bigger = true;
      }
      else {
        if (m_month == rhs.m_month)
        {
          if (m_day > rhs.m_day)
          {
            bigger = true;
          }
        }
      }
    }
  }
  return bigger;
}*/

bool Date::operator>(const Date & rhs) const
{
  // Precondition: This date and the rhs date passed in must be valid.
  // Postcondition: True returned if this date is later than the rhs date object, otherwise False.

  assert(IsValidDate(*this) && IsValidDate(rhs));

  return this->totalDays_ > rhs.totalDays_;
}

bool Date::operator<=(const Date & rhs) const
{
  // Precondition: This date and the rhs date passed in must be valid.
  // Postcondition: True returned if this date is earlier than, or the same as the rhs date object, otherwise False.

  assert(IsValidDate(*this) && IsValidDate(rhs));

  return (!(*this > rhs)) || *this == rhs;
}

bool Date::operator>=(const Date & rhs) const
{
  // Precondition: This date and the rhs date passed in must be valid.
  // Postcondition: True returned if this date is later than, or the same as the rhs date object, otherwise False.

  assert(IsValidDate(*this) && IsValidDate(rhs));

  return *this > rhs || *this == rhs;
}

#pragma endregion Operator Overloads

std::ostream& Date::ToStream(std::ostream & os) const
{
  os << std::setfill('0') << year_ << '-' << std::setw(2)
    << month_ << '-' << std::setw(2) << day_;
  return os;
}

Date* Date::CurrentDate()
{
  time_t rawCurrentTime = time(0);
  tm parsedCurrentTime;
  localtime_s(&parsedCurrentTime, &rawCurrentTime);
  return CreateDate(parsedCurrentTime.tm_year + 1900, parsedCurrentTime.tm_mon + 1, parsedCurrentTime.tm_mday); // tm_year is current year minus 1900, tm_month jan = 0
}

bool Date::IsValidDate(int year, int month, int day)
{
  return (IsValidMonth(month) && IsValidDay(year, month, day));
}

bool Date::IsValidDate(const std::string & yyyy_mm_dd)
{
  std::istringstream input(yyyy_mm_dd);
  int year, month, day;
  ParseString(input, year, month, day);
  return IsValidDate(year, month, day);
}

bool Date::IsValidDate(const Date & date)
{
  return (IsValidMonth(date.month_) && IsValidDay(date.year_, date.month_, date.day_));
}

Date* Date::CreateDate(const std::string & yyyy_mm_dd)
{
  std::istringstream input(yyyy_mm_dd);
  int year(0), month(0), day(0);
  ParseString(input, year, month, day);
  return CreateDate(year, month, day);
}

Date* Date::CreateDate(const char yyyy__mm__dd[])
{
  std::string rawInput;
  for (size_t i = 0; i < strlen(yyyy__mm__dd); i++)
  {
    rawInput += yyyy__mm__dd[i];
  }
  return CreateDate(rawInput);
}

Date* Date::CreateDate(int year, int month, int day)
{
  try {
    if (!IsValidDate(year, month, day))
      throw std::invalid_argument::invalid_argument("Date parameters incorrect");
  }
  catch (std::invalid_argument & e) {
    std::cerr << e.what();
  }
  return new Date(year, month, day);
}

bool Date::IsValidMonth(int month)
{
  assert(true);

  return (month > 0 && month < 13);
}

bool Date::IsValidDay(int year, int month, int day)
{
  assert(IsValidMonth(month));

  bool validDay = false;
  switch (month)
  {
  case 2: // February only has 28 days
    if (day > 0 && day < 29)
    {
      validDay = true;
    }
    else {
      if (day == 29 && IsLeapYear(year))
      {
        validDay = true;
      }
    }
    break;
  case 4:
  case 6:
  case 9:
  case 11: // Months with only 30 days (April, June, September, November)
    if (day > 0 && day < 31)
    {
      validDay = true;
    }
    break;
  default:
    if (day > 0 && day < 32) {
      validDay = true;
    }
    break;
  }
  return validDay;
}

bool Date::IsLeapYear(int year)
{
  //To determine whether a year is a leap year, follow these steps :
  //If the year is evenly divisible by 4, go to step 2. Otherwise, go to step 5.
  //  If the year is evenly divisible by 100, go to step 3. Otherwise, go to step 4.
  //  If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.
  //  The year is a leap year(it has 366 days).
  //  The year is not a leap year(it has 365 days).

  assert(true);

  return year % 4 == 0;
}

int Date::CalculateNumberOfDays(const Date & date)
{
  // TODO - Function is not calculating stuff right
  int numOfDays = 0;
  numOfDays += date.GetYear() + IsLeapYear(date.GetYear());

  for (int i = 0; i < date.GetMonth(); i++)
    numOfDays += Date::daysInMonth[i];

  numOfDays += date.GetDay();
  return numOfDays;
}

std::istream& Date::ParseString(std::istream & is, int& year, int& month, int& day)
{
  char ch;
  is >> year >> ch >> month >> ch >> day;
  return is;
}
