#include "backend.h"

using namespace std;

Field::Field(int _size)
{
    size = _size;
    dotsIn = 0;

    field.resize(_size);

    for (int i = 0; i < field.size(); i++)
        field[i].resize(_size);
}

Field::~Field(){};

void Field::setDot(int _lin, int _col, int _color)
{
    if (_lin >= 0 && _lin < size && _col >= 0 && _col < size)
        field[_lin][_col] = _color;
}

void Field::fillIn(int _lin, int _col, int _color)
{
    vector < vector < int > > used(size, vector < int > (size));

    queue < pair < int, int > > q;

    q.push({_lin, _col});

    int __saved_color = field[_lin][_col];

    used[_lin][_col] = 1;

    while (!q.empty())
    {
        int __lin = q.front().first;
        int __col = q.front().second;

        q.pop();

        field[__lin][__col] = _color;


        if (__lin - 1 >= 0)
            if (field[__lin - 1][__col] == __saved_color)
                if (used[__lin - 1][__col] == 0)
                {
                    q.push({(__lin - 1), __col});
                    used[__lin - 1][__col] = 1;
                }
            
        if (__lin + 1 < size)
            if (field[__lin + 1][__col] == __saved_color)
                if (used[__lin + 1][__col] == 0)
                {
                    q.push({(__lin + 1), __col});
                    used[__lin + 1][__col] = 1;
                }

        if (__col - 1 >= 0)
            if (field[__lin][__col - 1] == __saved_color)
                if (used[__lin][__col - 1] == 0)
                {
                    q.push({__lin, (__col - 1)});
                    used[__lin][__col - 1] = 1;
                }

        if (__col + 1 < size)
            if (field[__lin][__col + 1] == __saved_color)
                if (used[__lin][__col + 1] == 0)
                {
                    q.push({__lin, (__col + 1)});
                    used[__lin][__col + 1] = 1;
                }
    }
}

bool Field::calculatePixels(int _lin, int _col)
{
    if (field[_lin][_col])
    {
        dotsIn++;
        return true;
    }

    return false;
}

pair < int, int > Field::randomDot(int _linL, int _colL, int _linR, int _colR)
{
    double o = double(rand()) / double(RAND_MAX);

    double linRand = o * (_linR - _linL) + _linL;

    o = double(rand()) / double(RAND_MAX);

    double colRand = o * (_colR - _colL) + _colL;

    if (linRand >= _linR)
        linRand--;
    if (colRand >= _colR)
        colRand--;

    return {int(linRand), int(colRand)};
}

int Field::displaydotsIn()
{
    return dotsIn;
}

void Field::dotsInNull()
{
    dotsIn = 0;
}

void Field::displayField()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << field[i][j];
        }

        cout << endl;
    }

    cout << endl;
}

int Field::getSize()
{
    return size;
}

int Field::getDot(int _lin, int _col)
{
    return field[_lin][_col];
}

void Field::clearField()
{
    field.clear();

    dotsIn = 0;

    field.resize(size);

    for (int i = 0; i < field.size(); i++)
        field[i].resize(size);
}
