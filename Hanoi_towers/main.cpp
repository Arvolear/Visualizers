#include "hanoi.h"

using namespace std;
using namespace sf;

int main()
{
    int h;
    cout << "Insert the height of the towers (from 1 to 20)\n";
    cin >> h;

    while (h < 1 || h > 20)
    {
        cout << "Insert the height of the towers (from 1 to 20)\n";
        cin >> h;    
    }

    Hanoi *H = new Hanoi(h);
    
    H->start();

    delete H;
    
    return 0;
}
