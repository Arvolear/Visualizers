#include "PTree.hpp"

/* helper function to convert angles to radians */
static double rad(double angle)
{
    return angle * 3.14159265 / 180.0;
}

PTree::PTree() 
{
    srand(time(0)); // to dye the tree
}

/* recursive build function that build new squares on top
 * of the prev. squares 
 * @param d - current depth
 * @param prev - vector of squares on the prev. recursion 
 *
 * Function fills up tree vector by the end (without base square)
 * */
void PTree::build(int d, const vector < PTree::Square > &prev)
{
    /* base case */
    if (d >= depth)
    {
        return;
    }

    Color randomColor = Color(rand() % 255, rand() % 255, rand() % 255);

    /* new tmp depth vector */
    vector < Square > tmp;
    /* loop through prev. recursion squares */
    for (size_t i = 0; i < prev.size(); i++)
    {
        /* left sqaure */
        Square left; 

        /* calculate its length */
        left.length = prev[i].length * cos(rad(angle)); 
        /* update current rotation angle */
        left.angle = prev[i].angle - angle;

        /* 4 points */
        left.polygon.setPointCount(4);

        /* set those points in the same order as BASE square:
         *
         * 0--------3
         * |        |
         * |        |
         * |        |
         * |        |
         * 1--------2
         *
         * */
        left.polygon.setPoint(0, Vector2f(0, 0));
        left.polygon.setPoint(1, Vector2f(0, left.length));
        left.polygon.setPoint(2, Vector2f(left.length, left.length));
        left.polygon.setPoint(3, Vector2f(left.length, 0));
    
        /* set origin to 1 point */
        left.polygon.setOrigin(0, left.length);
        /* find position of prev. square 0 point */
        left.polygon.setPosition(prev[i].polygon.getTransform().transformPoint(prev[i].polygon.getPoint(0)));
        /* rotate polygon */
        left.polygon.setRotation(left.angle);
        /* dye */
        left.polygon.setFillColor(randomColor);

        tmp.push_back(left); // push to the new vector
        
        /***********************************************************/

        /* right square */
        Square right;

        /* calculate its length */
        right.length = prev[i].length * sin(rad(angle)); 
        /* rotation angle */
        right.angle = prev[i].angle + 90 - angle;

        /* THE SAME AS EVERYWHERE */ 
        right.polygon.setPointCount(4);

        right.polygon.setPoint(0, Vector2f(0, 0));
        right.polygon.setPoint(1, Vector2f(0, right.length));
        right.polygon.setPoint(2, Vector2f(right.length, right.length));
        right.polygon.setPoint(3, Vector2f(right.length, 0));
    
        /* set origin to 2 point */
        right.polygon.setOrigin(right.length, right.length);
        /* get prev. 3 point position */
        right.polygon.setPosition(prev[i].polygon.getTransform().transformPoint(prev[i].polygon.getPoint(3)));
        /* apply rotation */
        right.polygon.setRotation(right.angle);
        /* dye */
        right.polygon.setFillColor(randomColor);

        tmp.push_back(right); // push to the new vector
    }

    build(d + 1, tmp); // recursive call with new vector 

    /* on each recursion exit remember the squares */
    for (size_t i = 0; i < tmp.size(); i++)
    {
        tree.push_back(tmp[i]);
    }
}

/* function that constructs the base square of the tree
 * @param length - length of the base square 
 * @depth - recursion depth
 * @angle - angle of the tree, 45 degrees is default 
 *
 * After the base is constructed, calls build function
 * */
void PTree::construct(double length, int depth, double angle)
{
    /* if depth is zero - nothing to draw */
    if (!depth)
    {
        return;
    }

    Color randomColor = Color(rand() % 255, rand() % 255, rand() % 255);

    /* base square */
    Square base;

    base.length = length;
    base.angle = 0;

    /* set amount of points = 4 
     * those points:
     *
     * 0--------3
     * |        |
     * |        |
     * |        |
     * |        |
     * 1--------2
     *
     * */
    base.polygon.setPointCount(4);
    
    base.polygon.setPoint(0, Vector2f(0, 0));
    base.polygon.setPoint(1, Vector2f(0, base.length));
    base.polygon.setPoint(2, Vector2f(base.length, base.length));
    base.polygon.setPoint(3, Vector2f(base.length, 0));

    /* set origin to 1 point */
    base.polygon.setOrigin(0, base.length);
    /* centrify the square */
    base.polygon.setPosition(base.length * 2.5, base.length * 4);
    /* fill in */
    base.polygon.setFillColor(randomColor);

    this->depth = depth; // remember depth
    this->angle = angle; // remember angle

    /* tmp depth vector */
    vector < Square > tmp; 
    tmp.push_back(base);

    /* call build function */
    build(1, tmp);

    /* the last element in the tree vector is the base square */
    tree.push_back(tmp[0]);
}

void PTree::draw(RenderTarget& target, RenderStates states) const
{
    /* loop through each element (convex shape) 
     * in the tree and draw it 
     * */
    for (size_t i = 0; i < tree.size(); i++)
    {
        target.draw(tree[i].polygon);
    }
}

PTree::~PTree() {}
