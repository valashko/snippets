#include <iostream>

#include "access_private.h"

class Foo
{
private:
    void bar() {
      std::cout << "bar() called" << std::endl;
    }
    void baz() {
      std::cout << "baz() called" << std::endl;
    }
    void kazzum(int a, int b) {
      std::cout << "kazzum is " << a + b << std::endl;
    }
    int hidden = 42;
};

INIT_PRIVATE_METHOD_WRAPPER(Foo, void, bar, void)
INIT_PRIVATE_METHOD_WRAPPER(Foo, void, baz, void)
INIT_PRIVATE_METHOD_WRAPPER(Foo, void, kazzum, int, int)
INIT_PRIVATE_MEMBER_WRAPPER(Foo, int, hidden)

int main() {
    Foo foo;
    PRIVATE(foo, Foo, bar)();
    PRIVATE(foo, Foo, baz)();
    PRIVATE(foo, Foo, kazzum)(2, 2);
    std::cout << "before modification hidden is " << PRIVATE(foo, Foo, hidden) << std::endl;
    PRIVATE(foo, Foo, hidden) = 1111;
    std::cout << "after modification hidden is " << PRIVATE(foo, Foo, hidden) << std::endl;
    return 0;
}

