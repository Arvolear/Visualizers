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

        vector < Point* > polygonPoints;
        vector < Point* > testPoints;
        vector < Line* > lines;

        unsigned int height, width; 
 
        Generator* generator;
        Localizer* localizer;
        RenderWindow* window;
    
        float padding;

        void generate(int x, int y);
        void show();
        void regenerate();

    public:
        Interface(unsigned int width, unsigned int height);

        void play(); 

        ~Interface();
};
