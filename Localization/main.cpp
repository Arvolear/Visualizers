#include "generator.hpp"
#include "localizer.hpp"
#include "interface.hpp"

int main()
{
    Interface* I = new Interface(1337, 1337);

    I->play();

    delete I;

    return 0;
}
