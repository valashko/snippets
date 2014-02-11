#include <StrictPtr.h>
#include <Reporter.h>
#include <iostream>
using std::cout;
using std::endl;


int main()
{
  {
    StrictPtr< Reporter > p(new Reporter()); // constructor
    // basic stuff
    cout << "*p : " << *p << endl;
    cout << "p->id() : " << p->id() << endl;
    cout << "p.ptr() : " << p.ptr() << endl;
    cout << "p.isNull() : " << std::boolalpha << p.isNull() << endl;
  }

  Reporter::report(false);

  return 0;
}

