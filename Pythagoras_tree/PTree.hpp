#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <climits>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/* our PTree class that is derived from sf::Drawable */
class PTree : public Drawable
{
    private:
        /* little inner private helper Square struct */
        struct Square
        {
            ConvexShape polygon;
            double length;
            double angle;
        };

        /* output depth of the tree */
        int depth;
        /* input angle of the tree */
        double angle;

        /* here we hold final tree version */
        vector < Square > tree;
        
        /* private recursive function to build the tree */
        void build(int depth, const vector < PTree::Square > &prev); 

    public:
        /* constructor */
        PTree();

        /* construct base function that calls build function */
        void construct(double length, int depth, double angle);

        /* overrided draw function from sf::Drawable */
        void draw(RenderTarget& target, RenderStates states) const override;

        /* destructor */
        ~PTree();
};
