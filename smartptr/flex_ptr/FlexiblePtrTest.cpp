#include "FlexiblePtr.h"
#include <string>
using std::string;


int main()
{
  FlexiblePtr< int > p(new int(42));
  *p;
  p.isNull()
  return 0;
}

