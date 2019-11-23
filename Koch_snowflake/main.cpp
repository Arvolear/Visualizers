#include "snowflake.h"

using namespace std;
using namespace sf;

int main()
{
    int n;
    double w, h;

    cout << "Insert the depth of the flake (from 0 to 7)\n";
    cin >> n;
    while (n < 0 || n > 7)
    {
        cout << "Insert the depth of the flake (from 0 to 7)\n";
        cin >> n;
    }

    cout << "Insert the length of the starting bar (in pixels) (from 1 to 900)\n";
    cin >> w;
    while (w < 1 || w > 900)
    {
        cout << "Insert the length of the starting bar (in pixels) (from 1 to 900)\n";
        cin >> w;
    }

    cout << "Insert the width of the starting bar (in pixels) (from 1 to 90)\n";
    cin >> h;
    while (h < 1 || h > 90)
    {
        cout << "Insert the width of the starting bar (in pixels) (from 1 to 90)\n";
        cin >> h;
    }

    Koch *k = new Koch(n, w, h);

    k->draw();

    delete k;

    return 0;
}
