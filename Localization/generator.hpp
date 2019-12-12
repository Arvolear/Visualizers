#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Generator
{
    private:
        vector < Vector2f > polygon;

        int width, height;

        int wPadding, hPadding;

        Vector2f getFieldPoint();
        bool isOnField(Vector2f point);
        bool isSameSide(Vector2f line0, Vector2f line1, Vector2f point0, Vector2f point1, Vector2f point2);
        bool isIntersects(Vector2f point0, Vector2f point1, Vector2f point2);

    public:
        Generator(int width, int height);

        void generate(int wPadding, int hPadding, int number);

        vector < Vector2f > getPolygon() const;

        ~Generator();
};
