#include "randomnumber.hpp"
#include "poisson.hpp"
#include "interface.hpp"

Interface::Interface(unsigned int width, unsigned int height)
{
    this->height = height;
    this->width = width;

    radius = 60;

    grass = nullptr;
    window = nullptr;
    PD = nullptr;
}

void Interface::init()
{
    grass = new Element();
    
    grass->texture.loadFromFile("./textures/grass.png");
    grass->sprite.setTexture(grass->texture, true);
    grass->x = width / 2.0;
    grass->y = height / 2.0;
    grass->w = grass->texture.getSize().x;
    grass->h = grass->texture.getSize().y;
    grass->sch = height / grass->h;
    grass->scw = width / grass->w;
    grass->orx = grass->w / 2.0;
    grass->ory = grass->h / 2.0;
    grass->angle = 0.0;

    PD = new PoissonDisk(height, width);

    PD->generate(radius, width / 2.0, height / 2.0);

    vector < PoissonDisk::GridInfo > disk = PD->getDisk();

    for (size_t i = 0; i < disk.size(); i++)
    {
        Element* flower = new Element();

        flower->texture.loadFromFile("./textures/sunflower.png");
        flower->sprite.setTexture(flower->texture, true);
        flower->x = disk[i].x;
        flower->y = disk[i].y;
        flower->w = flower->texture.getSize().x;
        flower->h = flower->texture.getSize().y;

        float scale = getRandomNumber() + 0.5;

        flower->sch = radius * scale / flower->h;
        flower->scw = radius * scale / flower->w;
        flower->orx = flower->w / 2.0;
        flower->ory = flower->h / 2.0;
        flower->angle = rand() % 360;

        flowers.push_back(flower);
    }
}

void Interface::regenerate()
{
    Vector2i pixelpos = Mouse::getPosition(*window);
    Vector2f pos = window->mapPixelToCoords(pixelpos);

    if (pos.x < radius || pos.x > width - radius)
    {
        return;
    }
    
    if (pos.y < radius || pos.y > height - radius)
    {
        return;
    }

    PD->generate(radius, pos.x, pos.y);

    vector < PoissonDisk::GridInfo > disk = PD->getDisk();

    for (size_t i = 0; i < flowers.size(); i++)
    {
        delete flowers[i];
    }

    flowers.clear();

    for (size_t i = 0; i < disk.size(); i++)
    {
        Element* flower = new Element();

        flower->texture.loadFromFile("./textures/sunflower.png");
        flower->sprite.setTexture(flower->texture, true);
        flower->x = disk[i].x;
        flower->y = disk[i].y;
        flower->w = flower->texture.getSize().x;
        flower->h = flower->texture.getSize().y;

        float scale = getRandomNumber() + 0.5;

        flower->sch = radius * scale / flower->h;
        flower->scw = radius * scale / flower->w;
        flower->orx = flower->w / 2.0;
        flower->ory = flower->h / 2.0;
        flower->angle = rand() % 360;

        flowers.push_back(flower);
    }
}

void Interface::show()
{
    window->clear();

    grass->sprite.setPosition(Vector2f(grass->x, grass->y));
    grass->sprite.setScale(Vector2f(grass->scw, grass->sch));
    grass->sprite.setOrigin(Vector2f(grass->orx, grass->ory));

    window->draw(grass->sprite);

    for (size_t i = 0; i < flowers.size(); i++)
    {
        flowers[i]->sprite.setPosition(Vector2f(flowers[i]->x, flowers[i]->y));
        flowers[i]->sprite.setScale(Vector2f(flowers[i]->scw, flowers[i]->sch));
        flowers[i]->sprite.setOrigin(Vector2f(flowers[i]->orx, flowers[i]->ory));
        flowers[i]->sprite.setRotation(flowers[i]->angle);

        window->draw(flowers[i]->sprite);
    }

    window->display();
}

void Interface::play()
{
    init();

    window = new RenderWindow(VideoMode(width, height), "Poisson Disk");

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
    delete grass;

    for (size_t i = 0; i < flowers.size(); i++)
    {
        delete flowers[i];
    }

    delete window;
    delete PD;
}
