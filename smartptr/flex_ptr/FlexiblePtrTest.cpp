#include <FlexiblePtr.h>
#include <Reporter.h>
#include <iostream>
using std::cout;
using std::endl;


int main()
{
  {
    FlexiblePtr< Reporter > p(new Reporter()); // constructor
    // basic stuff
    cout << "*p : " << *p << endl;
    cout << "p->id() : " << p->id() << endl;
    cout << "p.ptr() : " << p.ptr() << endl;
    cout << "p.isNull() : " << std::boolalpha << p.isNull() << endl;

    Reporter * rawPtr = p.release(); // release
    cout << "*rawPtr : " << *rawPtr << endl;
    delete rawPtr;
    rawPtr = NULL;

    FlexiblePtr< Reporter > p2(new Reporter());
    FlexiblePtr< Reporter > p3(new Reporter());
    p.reset(p2); // reset
    p3.reset(); // reset with default parameter
    p3 = p; // assignment
    FlexiblePtr< Reporter > p4(p3); // copy constructor
    FlexiblePtr< Reporter > p5(new Reporter());
    p5 = p5; // self assignment testing
  }

  Reporter::report(false);

  return 0;
}

