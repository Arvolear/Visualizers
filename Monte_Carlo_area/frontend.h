#ifndef FRONTEND_H
#define FRONTEND_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;
using namespace sf;

class UI
{
    private:
        Field *field;
        Meter *meter;

        struct LINES
        {
            float x, y;
            float l, w;
            Color c;
            float r;
        };

        struct DOTS
        {
            float x, y;
            float l, w;
            Color c;
            float r;
        };

        struct TEXTS
        {
           string font;
           string s;
           int chsize;
           int x, y;
           Color c;
        };

        struct ALL
        {
            vector < LINES > lines;
            vector < TEXTS > texts;
            vector < DOTS > dots;
            float _lin;
            float _col;
            int _amount;
            int _winSize;
            int _visualize;
        }; 

        struct ALL all;

        void show(RenderWindow &anya);

        void lineDraw(RenderWindow &anya, float _fromLin, float _fromCol);

        void remLine(RenderWindow &anya);

        void Fill(RenderWindow &anya);

        void firstShow(RenderWindow &anya);
    
        pair < float, float > calculateRotation(float _fromLin, float _fromCol, float posx, float posy);

        void whatMeter(RenderWindow &anya, int _param, int _shift);
        
        void whatAmount(RenderWindow &anya, int _param, int _shift);
        
        void clean(RenderWindow &anya);

        void clearSCR(RenderWindow &anya);

        void visualize();
      
        void simulate(RenderWindow &anya, int _lin, int _col, bool _in);

        void count(RenderWindow &anya);

    public:
        UI(Field *f, Meter *m);

        void start();

        ~UI();
};

#endif
