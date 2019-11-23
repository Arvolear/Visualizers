#ifndef METER_H
#define METER_H

#include <iostream>

using namespace std;

class Meter 
{
    private:
        int type;
        int type_stock;
        int position;
        int position_stock;
        int length;
        int length_stock;

    public:
        Meter(int _length);
        pair < int, pair < int, int > > calculateMeter(int param);
        
        pair < int, pair < int, int > > calculateMeterShift(int param);
        
        pair < int, pair < int, int > > whatMeter();

        ~Meter();
};

#endif
