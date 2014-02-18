/*
    PString is designed to handle immutable strings
    by providing graceful memory management for c-style strings
    and adding several convenient features, such as
    built-in concatenation and Python-like multiplication.
    PString is null-terminated.
    (c) Volodymyr Lashko 2014
*/

#include <cstring>
#include <iostream>


#define NON_POSITION -1
#define ALPHABETICAL_LESS -1
#define ALPHABETICAL_EQUAL 0
#define ALPHABETICAL_MORE 1
// use COMPARE macro to avoid code duplication
#define COMPARE(LHS, RHS, RES) RES = std::strcmp((LHS).data(), (RHS).data())

class PString
{
private:
  char * data_;

public:
  PString()
  {
    data_ = new char('\0');
  }

  PString(const char c)
  {
    data_ = new char[2];
    data_[0] = c;
    data_[1] = '\0';
  }

  PString(const char * str)
  {
    data_ = new char[std::strlen(str)];
    std::strcpy(data_, str);
  }

  PString(const PString & other)
  {
    data_ = new char[other.length()];
    std::strcpy(data_, other.data());
  }

  ~PString()
  {
    delete[] data_;
  }

  unsigned int length() const
  {
    return strlen(data_);
  }

  const char * data() const
  {
    return data_;
  }

  bool empty() const
  {
    return length() == 0;
  }

  // returns position of the first occurence of substring
  // in given string or NON_POSIITON if substring was not found
  int find(const PString & substr) const
  {
    const char * occurence = std::strstr(this->data(), substr.data());
    if (occurence != NULL) {
      return (int)(occurence - this->data());
    } else {
      return NON_POSITION;
    }
  }

  PString operator+(const PString & rhs) const
  {
    char * result = new char[this->length() + rhs.length()];
    std::strcpy(result, this->data());
    std::strcpy(result + this->length(), rhs.data());
    return result;
  }

  // repeat string several times: "abc" * 3 == "abcabcabc"
  PString operator*(int multiplier) const
  {
    char * result = new char[length() * multiplier];
    for(int i = 0; i < multiplier; ++i) {
      std::strcpy(result + length() * i, data());
    }
    return result;
  }

  bool operator==(const PString & rhs) const
  {
    int result;
    COMPARE(*this, rhs, result);
    return result == ALPHABETICAL_EQUAL;
  }
  
  bool operator!=(const PString & rhs) const
  {
    int result;
    COMPARE(*this, rhs, result);
    return result != ALPHABETICAL_EQUAL;
  }
  
  bool operator<(const PString & rhs) const
  {
    int result;
    COMPARE(*this, rhs, result);
    return result == ALPHABETICAL_LESS;
  }
  
  bool operator>(const PString & rhs) const
  {
    int result;
    COMPARE(*this, rhs, result);
    return result == ALPHABETICAL_MORE;
  }
  
  const char & operator[](const int index) const
  {
    // we copy the character before returning so that the user
    // could not take it's address and access our internal char * array
    // like so:
    // const PString str("hello");
    // char * intruder = const_cast< char * >(&str[0]);
    // intruder[0] = 'B'; intruder[1] = 'A'; intruder[2] = 'D';
    // cout << str; // "BADlo" - Muhahaha!
    const char chr = data()[index];
    return chr;
  }
};



std::ostream & operator<<(std::ostream & os, const PString & str)
{
  os << str.data();
  return os;
}

