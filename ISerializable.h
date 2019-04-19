//OOP - Semester 2 - Group Assignment
//CS4G : Group 5
//Charlie Batten - 27012619, Nico Caruana - 27022205, Alin Medianu - 27005327

#ifndef ISerializableH
#define ISerializableH

#include <iostream> // To provide access to the streams for serializing

#include <cassert>  // For debugging purposes

/// <summary>
/// Abstract class providing interace functions to serialize data to streams.
/// <para>
/// This class can be used with the &lt;&lt; operator for intuitive serialization.
/// </para>
/// </summary>
class ISerializable
{
public:

  /// <summary>
  /// Pure virtual function, to be overriden by derived classes to feed the required data into a stream
  /// </summary>
  /// In:
  /// <param name='os'> Reference to the output stream to use.</param>
  /// Out:
  /// <returns>Returns the reference to output stream object used.</returns>
  virtual std::ostream& ToStream(std::ostream& os) const = 0;

};

std::ostream& operator<<(std::ostream& os, const ISerializable& rhs);

#endif // !ISerializableH
