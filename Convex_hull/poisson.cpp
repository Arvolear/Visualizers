#include "randomnumber.hpp"
#include "poisson.hpp"

PoissonDisk::PoissonDisk(unsigned int height, unsigned int width)
{
    this->height = height;
    this->width = width;

    this->radius = 0;

    this->sampleSize = 0;
    this->gridHeight = this->gridWidth = 0;

    this->padding = 0;
}
        
void PoissonDisk::addSample(const GridInfo& GI)
{
    active.push_back(GI);

    grid[round(GI.y / sampleSize)][round(GI.x / sampleSize)] = GI; 
}

PoissonDisk::GridInfo PoissonDisk::generateAround(const GridInfo& GI)
{
    float angle = getRandomNumber() * 2 * 3.14159265;

    float newRadius = getRandomNumber() * radius + radius;

    float newX = GI.x + newRadius * cos(angle);
    float newY = GI.y + newRadius * sin(angle);

    return GridInfo(newX, newY);
}
        
bool PoissonDisk::withinExtent(const GridInfo& GI)
{
    if (GI.x < padding || GI.x > float(width) - padding)
    {
        return false;
    }
    
    if (GI.y < padding || GI.y > float(height) - padding)
    {
        return false;
    }

    return true;
}
        
bool PoissonDisk::near(const GridInfo& GI)
{
    unsigned int gridX = round(GI.x / sampleSize);
    unsigned int gridY = round(GI.y / sampleSize);
    
    unsigned int checkBox = 2;

    int x0 = max(int(gridX - checkBox), 0);
    int y0 = max(int(gridY - checkBox), 0);
    int x1 = min(gridX + checkBox + 1, gridWidth);
    int y1 = min(gridY + checkBox + 1, gridHeight);

    for (int i = y0; i < y1; i++)
    {
        for (int j = x0; j < x1; j++)
        {
            if (grid[i][j].x != -1 && grid[i][j].y != -1)
            {
                GridInfo chosen = grid[i][j];

                if (chosen.distance(GI) < radius)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void PoissonDisk::setPadding(float padding)
{
    this->padding = padding;
}

void PoissonDisk::generate(float radius, float startX, float startY)
{
    clear();

    this->radius = radius;

    if (!padding)
    {
        padding = radius;
    }

    this->sampleSize = radius / sqrt(2);

    this->gridHeight = ceil(height / sampleSize);
    this->gridWidth = ceil(width / sampleSize);

    grid.resize(gridHeight, vector < GridInfo >(gridWidth, GridInfo()));

    addSample(GridInfo(startX, startY));

    while (true)
    {
        unsigned int index = round(getRandomNumber() * (active.size() - 1));

        GridInfo chosen = active[index];

        bool fine = false;

        for (size_t i = 0; i < 100; i++)
        {
            GridInfo newGI = generateAround(chosen);

            if (withinExtent(newGI) && !near(newGI))
            {
                addSample(newGI); 
                fine = true;
                break;
            }
        }

        if (!fine)
        {
            swap(active[index], active[active.size() - 1]);
            active.pop_back();
        }

        if (active.empty())
        {
            break;
        }
    }
}
        
vector < PoissonDisk::GridInfo > PoissonDisk::getDisk() const
{
    vector < GridInfo > res;

    for (size_t i = 0; i < gridHeight; i++)
    {
        for (size_t j = 0; j < gridWidth; j++)
        {
            if (grid[i][j].x != -1 && grid[i][j].y != -1)
            {
                res.push_back(grid[i][j]);
            }
        }
    }

    return move(res);
}
        
void PoissonDisk::clear()
{   
    grid.clear();
    active.clear();
}

PoissonDisk::~PoissonDisk() {}
