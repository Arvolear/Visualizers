#include <SFML/Graphics.hpp>

using namespace sf;

class Interface
{
    private:
        struct Element
        {
            Texture texture;
            Sprite sprite;

            float x, y;
            float w, h;
            float sch, scw;
            float orx, ory;

            float angle;
        };

        Element* grass;
        vector < Element* > flowers;

        unsigned int height, width; 
        
        RenderWindow* window;
        PoissonDisk* PD;
    
        float radius;

        void init();
        void show();
        void regenerate();

    public:
        Interface(unsigned int width, unsigned int height);

        void play(); 

        ~Interface();
};
