#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Localizer
{
    private:
        static constexpr float epsilon = 0.00001;

        vector < pair < Vector2f, bool > > points;

        int width, height;
        int wPadding, hPadding;
        
        Vector2f getFieldPoint();
        pair < Vector2f, Vector2f > getAABB(Vector2f point0, Vector2f point1); 
        bool isOnField(Vector2f point);
        Vector2f intersect(Vector2f point00, Vector2f point01, Vector2f point10, Vector2f point11);
        bool isInside(vector < Vector2f > polygon, Vector2f point);

    public:
        Localizer(int width, int height);

        void generate(vector < Vector2f > polygon, int wPadding, int hPadding, int number);

        vector < pair < Vector2f, bool > > getPoints() const;

        ~Localizer();
};
