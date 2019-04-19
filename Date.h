//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef DateH
#define DateH

#include "ISerializable.h"  // For base class inheritance.

#include <iostream>         // For dealing with streams to parse data.
#include <iomanip>          // For setting minimum item widths in stream outputs and default fill characters.
#include <string>           // For creating a standardised data structure for parsing inputs/ conversion from cstring format.
#include <sstream>          // For extracting data from the string.
#include <ctime>            // For getting the current system time.

#include <cassert>          // For debugging purposes.

/// <summary>
/// Date holds a valid date value and provides functions for working with it.
/// <para>
/// This class can be compared with another instance using the standard comparison operators.
/// </para>
/// <para>
/// This class can be used with the &lt;&lt; operator for intuitive serialization.
/// </para>
/// </summary>
class Date : public ISerializable
{
public:
  ~Date();

#pragma region Accessor Functions

  /// <summary>
  /// Get the year value of the date stored.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns the integer value of the year stored.</returns>
  int GetYear() const;

  /// <summary>
  /// Get the month value of the date stored.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns the integer value of the month stored.</returns>
  int GetMonth() const;

  /// <summary>
  /// Get the day value of the date stored.
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns the integer value of the day stored.</returns>
  int GetDay() const;

#pragma endregion Accessor Functions

#pragma region Operator Overloads

  /// <summary>
  /// Compare the Date object values for equality.
  /// </summary>
  /// In:
  /// <param name="rhs">Reference to Date object to compare to this one.</param>
  /// Out:
  /// <returns>Returns true returned if both Date objects contain the same value.</returns>
  bool operator==(const Date& rhs) const;

  /// <summary>
  /// Compare the Date object values for inequality.
  /// </summary>
  /// In:
  /// <param name="rhs">Reference to Date object to compare to this one.</param>
  /// Out:
  /// <returns>Returns true if both Date objects do not contain the same value.</returns>
  bool operator!=(const Date& rhs) const;

  /// <summary>
  /// Compare the Date values to determine the earliest.
  /// </summary>
  /// In:
  /// <param name="rhs">Reference to Date object to compare to this one.</param>
  /// Out:
  /// <returns>Returns true if the left Date occurs before the right Date.</returns>
  bool operator<(const Date& rhs) const;

  /// <summary>
  /// Compare the Date values to determine the most recent.
  /// </summary>
  /// In:
  /// <param name="rhs">Reference to Date object to compare to this one.</param>
  /// Out:
  /// <returns>Returns true if the left Date occurs after the right Date.</returns>
  bool operator>(const Date& rhs) const; // ***CHARLIE comparison

  /// <summary>
  /// Compare the Date values to determine if equal or earlier.
  /// </summary>
  /// In:
  /// <param name="rhs">Reference to Date object to compare to this one.</param>
  /// Out:
  /// <returns>Returns true if the left Date is equal to or occurs before the right Date.</returns>
  bool operator<=(const Date& rhs) const;

  /// <summary>
  /// Compare the Date values to determine if equal or more recent.
  /// </summary>
  /// In:
  /// <param name="rhs">Reference to Date object to compare to this one.</param>
  /// Out:
  /// <returns>Returns true if the left Date is equal to or occurs more recently than the right Date.</returns>
  bool operator>=(const Date& rhs) const;

#pragma endregion Operator Overloads

  /// <summary>
  /// Check if the arguments passed can be used to construct a valid Date object.
  /// <para>
  /// Leap years are accounted for.
  /// </para>
  /// </summary>
  /// In:
  /// <param name="year">Integer to be checked for validity as a year.</param>
  /// <param name="month">Integer to be checked for validity as a month</param>
  /// <param name="day">Integer to be checked for validity as a day</param>
  /// Out:
  /// <returns>Returns true if the arguments are valid</returns>
  static bool IsValidDate(int year, int month, int day);

  /// <summary>
  /// Check if the argument passed can be used to construct a valid Date object.
  /// <para>
  /// Leap years are accounted for.
  /// </para>
  /// </summary>
  /// In:
  /// <param name="yyyy_mm_dd">String reference to be checked for validity as a complete date.</param>
  /// Out:
  /// <returns>Returns true if the argument is valid</returns>
  static bool IsValidDate(const std::string& yyyy_mm_dd);

  /// <summary>
  /// Check if the argument passed can be used to construct a valid Date object.
  /// <para>
  /// Leap years are accounted for.
  /// </para>
  /// </summary>
  /// In:
  /// <param name="date">Date object reference to be checked for value validity.</param>
  /// Out:
  /// <returns>Returns true if the argument is valid</returns>
  static bool IsValidDate(const Date& date);

  /// <summary>
  /// Construct a Date object using the current system date.
  /// <para>
  /// System date is validated before construction, no need for a manual check.
  /// </para>
  /// </summary>
  /// In:
  /// <param></param>
  /// Out:
  /// <returns>Returns a pointer to a Date object with the current system date.</returns>
  static Date* CurrentDate();

  /// <summary>
  /// Construct a Date object using values from the argument passed.
  /// <para>
  /// Check intended argument with IsValidDate() before running this function.
  /// </para>
  /// </summary>
  /// In:
  /// <param name="yyyy_mm_dd">String reference to be used as values to construct Date object.</param>
  /// Out:
  /// <returns>Returns a pointer to a Date object with values taken from the argument passed.</returns>
  static Date* CreateDate(const std::string& yyyy_mm_dd);

  /// <summary>
  /// Construct a Date object using values from the argument passed.
  /// <para>
  /// Check intended argument with IsValidDate() before running this function.
  /// </para>
  /// </summary>
  /// In:
  /// <param name="yyyy_mm_dd">C-string/Char* to be used as values to construct Date object.</param>
  /// Out:
  /// <returns>Returns a pointer to a Date object with values taken from the argument passed.</returns>
  static Date* CreateDate(const char yyyy__mm__dd[]);

  /// <summary>
  /// Construct a Date object using values from the arguments passed.
  /// <para>
  /// Check intended arguments with IsValidDate() before running this function.
  /// </para>
  /// </summary>
  /// In:
  /// <param name="year">Integer to be used as year value.</param>
  /// <param name="month">Integer to be used as month value.</param>
  /// <param name="day">Integer to be used as day value.</param>
  /// Out:
  /// <returns>Returns a pointer to a Date object with values taken from the arguments passed.</returns>
  static Date* CreateDate(int year, int month, int day);

#pragma region Overriden Inherited Functions

  std::ostream& ToStream(std::ostream& os) const final;

#pragma endregion Overriden Inherited Functions

private:
  const static int daysInMonth[];
  int year_;
  int month_;
  int day_;
  int totalDays_;

  Date(int year, int month, int day);

  static std::istream& ParseString(std::istream& is, int& year, int& month, int& day);
  static bool IsValidMonth(int month);
  static bool IsValidDay(int year, int month, int day);
  static bool IsLeapYear(int year);
  static int CalculateNumberOfDays(const Date& date);
};

#endif // !DateH

