#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;

class PoissonDisk
{
    public:
        struct GridInfo
        {
            double x, y;

            GridInfo()
            {
                this->x = this->y = -1;
            }
            
            GridInfo(double x, double y)
            {
                this->x = x;
                this->y = y;
            }
            
            GridInfo(const GridInfo& GI)
            {
                this->x = GI.x;
                this->y = GI.y;
            }
            
            GridInfo& operator=(const GridInfo& GI)
            {
                this->x = GI.x;
                this->y = GI.y;

                return *this;
            }
        
            double distance(const GridInfo& GI) const
            {
                return sqrt((x - GI.x) * (x - GI.x) + (y - GI.y) * (y - GI.y));
            }

            double angle(const GridInfo& GI) const
            {
                GridInfo tmp = GI;
                tmp.x -= x;
                tmp.y -= y;

                double length = tmp.distance(GridInfo(0, 0));

                double cosangle = tmp.x / length;

                return acos(cosangle);
            }
        };

    private:
        unsigned int height, width;
        float radius;
        float padding;

        float sampleSize;

        unsigned int gridHeight, gridWidth;

        vector < vector < GridInfo > > grid;
        vector < GridInfo > active;

        void addSample(const GridInfo& GI);
        GridInfo generateAround(const GridInfo& GI);
        bool withinExtent(const GridInfo& GI);
        bool near(const GridInfo& GI);

        void clear();

    public:
        PoissonDisk(unsigned int height, unsigned int width);

        void setPadding(float padding);
        void generate(float radius, float startX, float startY);

        vector < GridInfo > getDisk() const; 

        ~PoissonDisk();
};
