#include "poisson.hpp"
#include "convexhull.hpp"
#include "interface.hpp"

int main()
{
    Interface* I = new Interface(1337, 1337);

    I->play();

    delete I;

    return 0;
}
