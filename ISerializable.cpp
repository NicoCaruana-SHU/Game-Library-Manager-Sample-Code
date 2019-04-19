//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#include "ISerializable.h"

std::ostream& operator<<(std::ostream& os, const ISerializable& rhs) {
  // Precondition: os and rhs exist
  // Postcondition: Reference to output stream returned with new data inserted.

  assert(true);

  return rhs.ToStream(os);
}
