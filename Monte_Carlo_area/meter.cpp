#include "meter.h"

using namespace std;

Meter::Meter(int _length)
{
    type = 0;
    type_stock = 0;
    position = 0;
    position_stock = 0;
    length = _length;
    length_stock = _length;
}

pair < int, pair < int, int > > Meter::calculateMeter(int param)
{
    if (param == 1)
    {
        length -= 10;
        position += 5;
        
        if (length <= 5)
        {
            if (type < 4)
            {
                type++;
                position = position_stock;
                length = length_stock;
            }
            else
            {
                position -= 5;
                length += 10;
            }
        }
    }

    if (param == -1)
    {
        length += 10;
        position -= 5;

        if (length >= 555)
        {
            if (type > -4)
            {
                type--;
                position = position_stock;
                length = length_stock;
            }
            else
            {
                position += 5;
                length -= 10;
            }
        }
    }

    return {type, {position, length}};
}

pair < int, pair < int, int > > Meter::calculateMeterShift(int param)
{
    if (param == 1)
    {
        if (type < 4)
            type++;
    }
    if (param == -1)
    {
        if (type > -4)
            type--;
    }

    return {type, {position, length}};
}


pair < int, pair < int, int > > Meter::whatMeter()
{
    return {type, {position, length}};
}

Meter::~Meter(){}
