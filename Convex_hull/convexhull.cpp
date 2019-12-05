#include "poisson.hpp"
#include "convexhull.hpp"

ConvexHull::ConvexHull() {}

int ConvexHull::orientation(PoissonDisk::GridInfo a, PoissonDisk::GridInfo b, PoissonDisk::GridInfo c)
{
    int orient = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

    if (!orient)
    {
        return 0; // collinear
    }

    return orient > 0 ? 1 : -1; // clock : counter
}

vector < PoissonDisk::GridInfo > ConvexHull::generate(vector < PoissonDisk::GridInfo > grid)
{   
    float minInd = 0;

    for (size_t i = 1; i < grid.size(); i++)
    {
        if ((grid[i].y < grid[minInd].y) || (grid[i].y == grid[minInd].y && grid[i].x < grid[minInd].x))
        {
            minInd = i;
        }
    }
    
    pivot = grid[minInd];
    swap(grid[0], grid[minInd]);

    sort(grid.begin() + 1, grid.end(), 
    [&](PoissonDisk::GridInfo a, PoissonDisk::GridInfo b)->bool
    {
        if (pivot.angle(a) < pivot.angle(b))
        {
            return true;
        }

        return false;
    });
    
    vector < PoissonDisk::GridInfo > res;

    res.push_back(grid[0]);
    res.push_back(grid[1]);
    res.push_back(grid[2]);

    for (size_t i = 3; i < grid.size(); i++)
    {
        while (res.size() > 1 && orientation(res[res.size() - 2], res[res.size() - 1], grid[i]) != -1)
        {
            res.pop_back();
        }

        res.push_back(grid[i]);
    }

    return res;
}

ConvexHull::~ConvexHull() {}
