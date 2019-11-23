#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

class Field
{
    private:
        int size;
        int dotsIn;

        vector < vector < int > > field;

    public:

        Field(int _size);

        void setDot(int _lin, int _col, int _color);

        void fillIn(int _lin, int _col, int _color);

        pair < int, int > randomDot(int _linL, int _colL, int _linR, int _colR);

        int displaydotsIn();

        void dotsInNull();

        bool calculatePixels(int _lin, int _col);

        void displayField();

        int getSize();

        int getDot(int _lin, int _col);

        void clearField();

        ~Field();
};

#endif
