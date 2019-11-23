#include "PTree.hpp"

int main(int argc, char** argv)
{
    /* if wrong arguments */
    if (argc < 3 || argc > 5)
    {
        cout << "Wrong set of arguments provided\n";
        cout << "There are: window size, recursion depth\n";
        return 0;
    }

    /* out tree */
    PTree tree;

    /* check if angle argument was provided and construct the tree */
    if (argc == 3)
    {
        tree.construct(stod(argv[1]), stoi(argv[2]), 45.0);
    }
    else if (argc == 4)
    {
        tree.construct(stod(argv[1]), stoi(argv[2]), stod(argv[3]));
    }

    /* window size of (6 * L; 4 * L) */
    RenderWindow window(VideoMode(stod(argv[1]) * 6, stod(argv[1]) * 4), "Pythagoras tree");
    window.setPosition(Vector2i(100, 100));

    /* not to stress the PC but will affect tree build speed */
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            
            /* if escape - quit */
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear(Color(30, 30, 30));
        /* draw the tree */
        window.draw(tree);
        window.display();
    }

    return 0;
}
