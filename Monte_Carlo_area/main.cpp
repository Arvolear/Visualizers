#include "backend.h"
#include "meter.h"
#include "frontend.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    srand(time(0));

    Field *f = new Field(565);

    Meter *m = new Meter(250);

    UI *user = new UI(f, m);

    user->start();

    delete user;

    return 0;
}
