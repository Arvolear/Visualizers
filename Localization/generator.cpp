#include "randomnumber.hpp"
#include "generator.hpp"

Generator::Generator(int width, int height)
{
    this->width = width;
    this->height = height;
}

Vector2f Generator::getFieldPoint()
{
    float x01 = getRandomNumber();
    float y01 = getRandomNumber();

    return {x01 * width, y01 * height};
}
        
bool Generator::isOnField(Vector2f point)
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
       
bool Generator::isSameSide(Vector2f line0, Vector2f line1, Vector2f point0, Vector2f point1, Vector2f point2)
{
    double k = (line1.y - line0.y) / (line1.x - line0.x); 
    double b = ((line1.x * line0.y) - (line1.y * line0.x)) / (line1.x - line0.x);
  
    float sign0 = point0.x * k - point0.y + b;
    float sign1 = point1.x * k - point1.y + b;
    float sign2 = point2.x * k - point2.y + b;

    if (sign0 >= 0 && sign1 > 0 && sign2 >= 0)
    {
        return true;
    }
    
    if (sign0 <= 0 && sign1 < 0 && sign2 <= 0)
    {
        return true;
    }

    return false;
}
 
bool Generator::isIntersects(Vector2f point0, Vector2f point1, Vector2f point2)
{
    for (size_t i = 0; i < polygon.size() - 1; i++)
    {
        Vector2f line0 = polygon[i];
        Vector2f line1 = polygon[i + 1];

        if (!isSameSide(line0, line1, point0, point1, point2))
        {
            return true;
        }
    }

    return false;
}

void Generator::generate(int wPadding, int hPadding, int number)
{
    this->wPadding = wPadding;
    this->hPadding = hPadding;

    polygon.clear();

    while ((int)polygon.size() < number)
    {
        bool OK = false;

        for (int i = 0; i < 100; i++)
        {
            Vector2f point = getFieldPoint();

            if (isOnField(point))
            {
                if (polygon.size() > 2)
                {
                    if (!isIntersects(polygon[0], point, polygon[polygon.size() - 1]))
                    {
                        OK = true;
                        polygon.push_back(point);
                        break;
                    }
                }
                else
                {
                    OK = true;
                    polygon.push_back(point); 
                    break;
                }
            }
        }

        if (!polygon.empty() && !OK)
        {
            polygon.pop_back();
        }
    }
}

vector < Vector2f > Generator::getPolygon() const
{
    return polygon;
}

Generator::~Generator() {}
