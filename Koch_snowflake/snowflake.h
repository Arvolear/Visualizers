#ifndef SNOW_H
#define SHOW_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Koch
{
    private:

        double area;
        double first_area;
        int depth;
        double width;
        double height;

        struct S
        {
            RectangleShape line;
            double x, y;
            double w, h;
            Color c;

            int angle;
        };

        struct T
        {
            Font font;
            Text text;

            int x, y;
            int chsize;
            Color c;
            string s;
        };

        T tarea;

        vector < S > lines;

    public:
       
        Koch(int n, double w, double h);

        void init();
    
        void recursion(RenderWindow &koch, int d, vector < S > l);

        void draw();

        void show(RenderWindow &koch);

        ~Koch();
};

#endif
