#include <PString.h>
#include <cassert>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;


int main()
{
  PString s1;
  assert(s1.empty());
  cout << "s1='" << s1 << "'" << endl;

  PString s2("Hola amigo!");
  cout << "s2='" << s2 << "'" << endl;
  assert(!s2.empty());
  assert(s2.length() == 11);

  PString s3('l');
  assert(s3.length() == 1);
  assert(s2.find(s3) == 2);

  PString s4(s3 * 3);
  assert(s4 == "lll");
  assert(s2.find(s4) == NON_POSITION);
  
  const PString str("test");
  char * intruder = const_cast< char * >(&str[0]);
  intruder[2] = 'X'; // expect to see "teXt"
  assert(str == "test");
  cout << "str='" << str << "' - intrusion FAILED!" << endl;

  cout << "Success!" << endl;
  return 0;
}

