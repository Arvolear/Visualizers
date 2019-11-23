#ifndef HANOI_H
#define HANOI_H

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Hanoi
{
    private:

        int height;
        int counter = 1;

        struct c
        {
            int number;

            RectangleShape line;
            
            int x, y;
            int w, h;

            Color c;
        };

        struct t
        {
            RectangleShape line;

            int x, y;
            int w, h;

            Color c;
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

        T trec;

        vector < t > towers;

        vector < c > one;
        vector < c > two;
        vector < c > three;

    public:

        Hanoi(int h);

        void init();

        void setMove(RenderWindow &hanoi, vector < c > &from, vector < c > &to, int z);

        void recursion(RenderWindow &hanoi, vector < c > &from, vector < c > &help, vector < c > &to, int h, int x, int y, int z);

        void start();

        void show(RenderWindow &hanoi);

        ~Hanoi();
};


#endif
