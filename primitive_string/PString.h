/*
    PString is designed to handle immutable strings
    by providing graceful memory management for c-style strings
    and adding several convenient features, such as
    built-in concatenation and Python-like multiplication.
    PString is null-terminated.
    (c) Volodymyr Lashko 2014
*/

#include <cstring>


#define NON_POSITION -1

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
};

