#pragma once

#include <algorithm>
#include <vector>

using namespace std;

class ConvexHull
{
    private:
        int orientation(PoissonDisk::GridInfo a, PoissonDisk::GridInfo b, PoissonDisk::GridInfo c);
        
        PoissonDisk::GridInfo pivot;
        
    public:
        ConvexHull();

        vector < PoissonDisk::GridInfo > generate(vector < PoissonDisk::GridInfo > grid);

        ~ConvexHull();
};
