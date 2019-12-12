#include "poisson.hpp"
#include "convexhull.hpp"
#include "interface.hpp"

Interface::Interface(unsigned int width, unsigned int height)
{
    this->height = height;
    this->width = width;

    radius = 60;
    padding = 200;

    window = nullptr;
    PD = new PoissonDisk(height, width);
    convexHull = new ConvexHull();
}

void Interface::generate(int x, int y)
{
    PD->setPadding(padding);
    PD->generate(radius, x, y);

    vector < PoissonDisk::GridInfo > disk = PD->getDisk();
    vector < PoissonDisk::GridInfo > conv = convexHull->generate(disk);

    for (size_t i = 0; i < disk.size(); i++)
    {
        Point* point = new Point();

        point->x = disk[i].x;
        point->y = disk[i].y;
        point->w = 10;
        point->h = 10;
        point->orx = point->w / 2;
        point->ory = point->h / 2;
        point->c = Color(0, 134, 237);

        poissonPoints.push_back(point);
    }
    
    for (size_t i = 0; i < conv.size(); i++)
    {
        Point* point = new Point();

        point->x = conv[i].x;
        point->y = conv[i].y;
        point->w = 10;
        point->h = 10;
        point->orx = point->w / 2;
        point->ory = point->h / 2;
        point->c = Color(219, 0, 44);

        convexHullPoints.push_back(point);
    }

    conv.push_back(conv[0]);

    for (size_t i = 0; i < conv.size() - 1; i++)
    {
        float length = conv[i].distance(conv[i + 1]);
        float rotation = 0.0;
        
        if (conv[i + 1].y - conv[i].y >= 0)
        {
            rotation = acos((conv[i + 1].x - conv[i].x) / length);
        }
        else if (conv[i + 1].y - conv[i].y < 0)
        {
            rotation = -acos((conv[i + 1].x - conv[i].x) / length);
        }
        
        Line* line = new Line();

        line->x = conv[i].x;
        line->y = conv[i].y;
        line->w = length;
        line->h = 2;
        line->orx = 0;
        line->ory = line->h / 2;
        line->r = (rotation * 180.0 / 3.141592);
        line->c = Color(148, 230, 14);

        lines.push_back(line);
    }

    conv.pop_back();
}
        
void Interface::regenerate()
{
    Vector2i pixelpos = Mouse::getPosition(*window);
    Vector2f pos = window->mapPixelToCoords(pixelpos);

    if (pos.x < padding || pos.x > width - padding)
    {
        return;
    }
    
    if (pos.y < padding || pos.y > height - padding)
    {
        return;
    }
    
    for (size_t i = 0; i < poissonPoints.size(); i++)
    {
        delete poissonPoints[i];
    }
   
    for (size_t i = 0; i < convexHullPoints.size(); i++)
    {
        delete convexHullPoints[i];
    }
    
    for (size_t i = 0; i < lines.size(); i++)
    {
        delete lines[i];
    }

    poissonPoints.clear();
    convexHullPoints.clear();
    lines.clear();

    generate(pos.x, pos.y);
}

void Interface::show()
{
    window->clear(Color(30, 30, 30));
    
    for (size_t i = 0; i < poissonPoints.size(); i++)
    {
        poissonPoints[i]->point.setPosition(Vector2f(poissonPoints[i]->x, poissonPoints[i]->y));
        poissonPoints[i]->point.setSize(Vector2f(poissonPoints[i]->w, poissonPoints[i]->h));
        poissonPoints[i]->point.setOrigin(Vector2f(poissonPoints[i]->orx, poissonPoints[i]->ory));
        poissonPoints[i]->point.setFillColor(poissonPoints[i]->c); 

        window->draw(poissonPoints[i]->point);
    }

    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i]->line.setPosition(Vector2f(lines[i]->x, lines[i]->y));
        lines[i]->line.setSize(Vector2f(lines[i]->w, lines[i]->h));
        lines[i]->line.setOrigin(Vector2f(lines[i]->orx, lines[i]->ory));
        lines[i]->line.setRotation(lines[i]->r);
        lines[i]->line.setFillColor(lines[i]->c); 

        window->draw(lines[i]->line);
    }
    
    for (size_t i = 0; i < convexHullPoints.size(); i++)
    {
        convexHullPoints[i]->point.setPosition(Vector2f(convexHullPoints[i]->x, convexHullPoints[i]->y));
        convexHullPoints[i]->point.setSize(Vector2f(convexHullPoints[i]->w, convexHullPoints[i]->h));
        convexHullPoints[i]->point.setOrigin(Vector2f(convexHullPoints[i]->orx, convexHullPoints[i]->ory));
        convexHullPoints[i]->point.setFillColor(convexHullPoints[i]->c); 

        window->draw(convexHullPoints[i]->point);
    }

    window->display();
}

void Interface::play()
{
    generate(width / 2, height / 2);

    window = new RenderWindow(VideoMode(width, height), "Convex Hull");

    window->setFramerateLimit(60);
    window->setPosition(Vector2i(300, 200));

    while (window->isOpen())
    {
        Event event;

        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window->close();
            }

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window->close();
                }
            }
            
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    regenerate();
                }
            }
        }

        show();
    }
}

Interface::~Interface()
{
    for (size_t i = 0; i < poissonPoints.size(); i++)
    {
        delete poissonPoints[i];
    }
   
    for (size_t i = 0; i < convexHullPoints.size(); i++)
    {
        delete convexHullPoints[i];
    }
     
    for (size_t i = 0; i < lines.size(); i++)
    {
        delete lines[i];
    }

    delete window;
    delete PD;
    delete convexHull;
}
