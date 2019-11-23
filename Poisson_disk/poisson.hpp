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
            float x, y;

            GridInfo()
            {
                this->x = this->y = -1;
            }
            
            GridInfo(float x, float y)
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
        };

    private:
        unsigned int height, width;
        float radius;

        float sampleSize;

        unsigned int gridHeight, gridWidth;

        vector < vector < GridInfo > > grid;
        vector < GridInfo > active;

        float distance(const GridInfo& GI0, const GridInfo& GI1);

        void addSample(const GridInfo& GI);
        GridInfo generateAround(const GridInfo& GI);
        bool withinExtent(const GridInfo& GI);
        bool near(const GridInfo& GI);

        void clear();

    public:
        PoissonDisk(unsigned int height, unsigned int width);

        void generate(float radius, float startX, float startY);

        vector < GridInfo > getDisk() const; 

        ~PoissonDisk();
};
