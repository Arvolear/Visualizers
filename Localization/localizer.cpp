#include "randomnumber.hpp"
#include "localizer.hpp"

Localizer::Localizer(int width, int height)
{
    this->width = width;
    this->height = height;
}

Vector2f Localizer::getFieldPoint()
{
    float x01 = getRandomNumber();
    float y01 = getRandomNumber();

    return {x01 * width, y01 * height};
}

pair < Vector2f, Vector2f > Localizer::getAABB(Vector2f point0, Vector2f point1)
{
    Vector2f MIN, MAX;

    MIN.x = min(point0.x, point1.x);
    MIN.y = min(point0.y, point1.y);

    MAX.x = max(point0.x, point1.x);
    MAX.y = max(point0.y, point1.y);

    return {MIN, MAX};
}

bool Localizer::isOnField(Vector2f point)
{
    if (point.x < wPadding || point.x > width - wPadding)
    {
        return false;
    }

    if (point.y < hPadding || point.y > height - hPadding)
    {
        return false;
    }

    return true;
}

Vector2f Localizer::intersect(Vector2f point00, Vector2f point01, Vector2f point10, Vector2f point11)
{
    double k0 = (point01.y - point00.y) / (point01.x - point00.x);
    double b0 = ((point01.x * point00.y) - (point01.y * point00.x)) / (point01.x - point00.x);
    
    double k1 = (point11.y - point10.y) / (point11.x - point10.x);
    double b1 = ((point11.x * point10.y) - (point11.y * point10.x)) / (point11.x - point10.x);

    /* collinear */
    if (k0 - epsilon < k1 && k0 + epsilon > k1)
    {
        return {-1, -1};
    }

    float kDif = k0 - k1;
    float bDif = b0 - b1;

    bDif /= kDif;
    kDif = 1;

    float X = -bDif;
    float Y = X * k0 + b0;

    return {X, Y};
}
        
bool Localizer::isInside(vector < Vector2f > polygon, Vector2f point)
{
    int counter = 0;

    polygon.push_back(polygon[0]);

    for (size_t i = 0; i < polygon.size() - 1; i++)
    {
        Vector2f line0 = polygon[i];
        Vector2f line1 = polygon[i + 1];
        Vector2f pointEnd = Vector2f(point.x + 1.0, point.y);

        Vector2f inter = intersect(line0, line1, point, pointEnd);
        
        pair < Vector2f, Vector2f > AABB = getAABB(line0, line1);

        if (inter.x == -1 && inter.y == -1)
        {
            continue;
        }

        if (inter.x < point.x)
        {
            continue;
        }

        if (inter.x < AABB.first.x || inter.x > AABB.second.x)
        {
            continue;
        }
        
        if (inter.y < AABB.first.y || inter.y > AABB.second.y)
        {
            continue;
        }

        counter++;
    }

    polygon.pop_back();

    if (!counter || counter % 2 == 0)
    {
        return false;
    }

    return true;
}

void Localizer::generate(vector < Vector2f > polygon, int wPadding, int hPadding, int number)
{
    this->wPadding = wPadding;
    this->hPadding = hPadding;

    points.clear();
    
    while ((int)points.size() < number)
    {
        Vector2f point = getFieldPoint();

        if (isOnField(point))
        {
            if (isInside(polygon, point))
            {
                points.push_back({point, true});
            }
            else
            {
                points.push_back({point, false});
            }
        }
    }
}

vector < pair < Vector2f, bool > > Localizer::getPoints() const
{
    return points;
}

Localizer::~Localizer() {}
