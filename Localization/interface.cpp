#include "generator.hpp"
#include "localizer.hpp"
#include "interface.hpp"

Interface::Interface(unsigned int width, unsigned int height)
{
    this->height = height;
    this->width = width;

    padding = 200;

    window = nullptr;
    generator = new Generator(width, height);
    localizer = new Localizer(width, height);
}

void Interface::generate(int x, int y)
{
    generator->generate(padding, padding, 10);
    vector < Vector2f > polygon = generator->getPolygon();

    localizer->generate(polygon, padding, padding, 10);
    vector < pair < Vector2f, bool > > test = localizer->getPoints();

    for (size_t i = 0; i < polygon.size(); i++)
    {
        Point* point = new Point();

        point->x = polygon[i].x;
        point->y = polygon[i].y;
        point->w = 10;
        point->h = 10;
        point->orx = point->w / 2;
        point->ory = point->h / 2;
        point->c = Color(219, 0, 44);

        polygonPoints.push_back(point);
    }
    
    for (size_t i = 0; i < test.size(); i++)
    {
        Point* point = new Point();

        point->x = test[i].first.x;
        point->y = test[i].first.y;
        point->w = 10;
        point->h = 10;
        point->orx = point->w / 2;
        point->ory = point->h / 2;
        point->c = test[i].second ? Color(230, 131, 0) : Color(161, 0, 230);

        testPoints.push_back(point);
    }

    polygonPoints.push_back(polygonPoints[0]);

    for (size_t i = 0; i < polygonPoints.size() - 1; i++)
    {
        float length = sqrt((polygonPoints[i]->x - polygonPoints[i + 1]->x) * (polygonPoints[i]->x - polygonPoints[i + 1]->x) + (polygonPoints[i]->y - polygonPoints[i + 1]->y) * (polygonPoints[i]->y - polygonPoints[i + 1]->y));
        float rotation = 0.0;
        
        if (polygonPoints[i + 1]->y - polygonPoints[i]->y >= 0)
        {
            rotation = acos((polygonPoints[i + 1]->x - polygonPoints[i]->x) / length);
        }
        else if (polygonPoints[i + 1]->y - polygonPoints[i]->y < 0)
        {
            rotation = -acos((polygonPoints[i + 1]->x - polygonPoints[i]->x) / length);
        }
        
        Line* line = new Line();

        line->x = polygonPoints[i]->x;
        line->y = polygonPoints[i]->y;
        line->w = length;
        line->h = 2;
        line->orx = 0;
        line->ory = line->h / 2;
        line->r = (rotation * 180.0 / 3.141592);
        line->c = Color(148, 230, 14);

        lines.push_back(line);
    }
    
    polygonPoints.pop_back();
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
    
    for (size_t i = 0; i < polygonPoints.size(); i++)
    {
        delete polygonPoints[i];
    }
    
    for (size_t i = 0; i < testPoints.size(); i++)
    {
        delete testPoints[i];
    }
   
    for (size_t i = 0; i < lines.size(); i++)
    {
        delete lines[i];
    }

    polygonPoints.clear();
    testPoints.clear();
    lines.clear();

    generate(pos.x, pos.y);
}

void Interface::show()
{
    window->clear(Color(30, 30, 30));
    
    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i]->line.setPosition(Vector2f(lines[i]->x, lines[i]->y));
        lines[i]->line.setSize(Vector2f(lines[i]->w, lines[i]->h));
        lines[i]->line.setOrigin(Vector2f(lines[i]->orx, lines[i]->ory));
        lines[i]->line.setRotation(lines[i]->r);
        lines[i]->line.setFillColor(lines[i]->c); 

        window->draw(lines[i]->line);
    }
    
    for (size_t i = 0; i < polygonPoints.size(); i++)
    {
        polygonPoints[i]->point.setPosition(Vector2f(polygonPoints[i]->x, polygonPoints[i]->y));
        polygonPoints[i]->point.setSize(Vector2f(polygonPoints[i]->w, polygonPoints[i]->h));
        polygonPoints[i]->point.setOrigin(Vector2f(polygonPoints[i]->orx, polygonPoints[i]->ory));
        polygonPoints[i]->point.setFillColor(polygonPoints[i]->c); 

        window->draw(polygonPoints[i]->point);
    }
    
    for (size_t i = 0; i < testPoints.size(); i++)
    {
        testPoints[i]->point.setPosition(Vector2f(testPoints[i]->x, testPoints[i]->y));
        testPoints[i]->point.setSize(Vector2f(testPoints[i]->w, testPoints[i]->h));
        testPoints[i]->point.setOrigin(Vector2f(testPoints[i]->orx, testPoints[i]->ory));
        testPoints[i]->point.setFillColor(testPoints[i]->c); 

        window->draw(testPoints[i]->point);
    }

    window->display();
}

void Interface::play()
{
    generate(width / 2, height / 2);

    window = new RenderWindow(VideoMode(width, height), "Localizer");

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
    for (size_t i = 0; i < polygonPoints.size(); i++)
    {
        delete polygonPoints[i];
    }
    
    for (size_t i = 0; i < testPoints.size(); i++)
    {
        delete testPoints[i];
    }
     
    for (size_t i = 0; i < lines.size(); i++)
    {
        delete lines[i];
    }

    delete window;
    delete generator;
    delete localizer;
}
