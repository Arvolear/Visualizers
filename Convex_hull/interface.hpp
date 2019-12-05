#include <SFML/Graphics.hpp>

using namespace sf;

class Interface
{
    private:
        struct Point
        {
            RectangleShape point;

            float x, y;
            float w, h;
            float orx, ory;
            Color c;
        };

        struct Line
        {
            RectangleShape line;

            float x, y;
            float w, h;
            float orx, ory;
            float r;
            Color c;
        };

        vector < Point* > poissonPoints;
        vector < Point* > convexHullPoints;
        vector < Line* > lines;

        unsigned int height, width; 
        
        RenderWindow* window;
        PoissonDisk* PD;
        ConvexHull* convexHull;
    
        float radius;
        float padding;

        void generate(int x, int y);
        void show();
        void regenerate();

    public:
        Interface(unsigned int width, unsigned int height);

        void play(); 

        ~Interface();
};
