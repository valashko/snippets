#include <PString.h>
#include <cassert>
#include <cstring>
#include <iostream>


int main()
{
  PString s1;
  assert(s1.empty());

  PString s2("Hola amigo!");
  assert(!s2.empty());
  assert(s2.length() == 11);

  PString s3('l');
  assert(s3.length() == 1);
  assert(s2.find(s3) == 2);

  PString s4(s3 * 3);
  assert(std::strcmp(s4.data(), "lll") == 0); // s3 == s4
  assert(s2.find(s4) == NON_POSITION);

  std::cout << "Success!" << std::endl;
  return 0;
}

