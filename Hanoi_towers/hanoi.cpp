#include "hanoi.h"

using namespace std;
using namespace sf;

Hanoi::Hanoi(int h)
{
    height = h;
}

void Hanoi::init()
{
    srand(time(0));

    towers.resize(3);

    for (int i = 0; i < 3; i++)
    {
        towers[i].x = 420 + 540 * i;
        towers[i].y = 540 - height * 50 / 2;

        towers[i].w = 10;
        towers[i].h = height * 50;
        towers[i].c = Color(255, 255, 255);
    }
    
    for (int i = height - 1; i >= 0; i--)
    {
        c circle;

        circle.number = i;
        circle.x = 420;
        circle.y = (540 - height * 50 / 2 + 20) + 50 * i;
        circle.w = 567 - 27 * (20 - i);
        circle.h = 5;
        circle.c = Color(100 + rand() % 155, 100 + rand() % 155, 100 + rand() % 155);

        one.push_back(circle);
    }
    
    trec.font.loadFromFile("./fonts/digital-7.ttf");
    trec.text.setFont(trec.font);
    trec.x = 1600;
    trec.y = 50;
    trec.chsize = 64;
    trec.c = Color(100 + rand() % 155, 100 + rand() % 155, 100 + rand() % 155);
    
    trec.s = to_string(counter);
}

void Hanoi::setMove(RenderWindow &hanoi, vector < c > &from, vector < c > &to, int z)
{
    Event event;

    while (hanoi.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            hanoi.close();
            exit(0);
        }
    }

    int xcoord = 420 + 540 * (z - 1);

    to.push_back(from[from.size() - 1]);
    from.pop_back();
                
    to[to.size() - 1].x = xcoord;
    to[to.size() - 1].y = 510 + height * 50 / 2 - (to.size() - 1) * 50;
    
    show(hanoi);
}

void Hanoi::recursion(RenderWindow &hanoi, vector < c > &from, vector < c > &help, vector < c > &to, int h, int x, int y, int z)
{
    counter++;
    trec.s = to_string(counter);

    if (h == 1)
    {
        setMove(hanoi, from, to, z);
        return;
    }

    recursion(hanoi, from, to, help, h - 1, x, z, y);
    
    setMove(hanoi, from, to, z);
    
    recursion(hanoi, help, from, to, h - 1, y, x, z);
}

void Hanoi::start()
{
    RenderWindow hanoi(VideoMode(1920, 1080), "Hanoi", 4);

    hanoi.setFramerateLimit(10);

    init();
    
    recursion(hanoi, one, two, three, height, 1, 2, 3);


    while (hanoi.isOpen())
    {
        Event event;

        while (hanoi.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                hanoi.close();
                exit(0);
            }
        }

        show(hanoi);
    }
}

void Hanoi::show(RenderWindow &hanoi)
{
    hanoi.clear();

    for (int i = 0; i < 3; i++)
    {
        towers[i].line.setOrigin(towers[i].w / 2, 0);
        towers[i].line.setPosition(Vector2f(towers[i].x, towers[i].y));
        towers[i].line.setSize(Vector2f(towers[i].w, towers[i].h));
        towers[i].line.setFillColor(towers[i].c);

        hanoi.draw(towers[i].line);
    }

    for (int i = 0; i < one.size(); i++)
    {
        one[i].line.setOrigin(one[i].w / 2, one[i].h / 2);
        one[i].line.setPosition(Vector2f(one[i].x, one[i].y));
        one[i].line.setSize(Vector2f(one[i].w, one[i].h));
        one[i].line.setFillColor(one[i].c);

        hanoi.draw(one[i].line);
    }
    
    for (int i = 0; i < two.size(); i++)
    {
        two[i].line.setOrigin(two[i].w / 2, two[i].h / 2);
        two[i].line.setPosition(Vector2f(two[i].x, two[i].y));
        two[i].line.setSize(Vector2f(two[i].w, two[i].h));
        two[i].line.setFillColor(two[i].c);

        hanoi.draw(two[i].line);
    }
    
    for (int i = 0; i < three.size(); i++)
    {
        three[i].line.setOrigin(three[i].w / 2, three[i].h / 2);
        three[i].line.setPosition(Vector2f(three[i].x, three[i].y));
        three[i].line.setSize(Vector2f(three[i].w, three[i].h));
        three[i].line.setFillColor(three[i].c);

        hanoi.draw(three[i].line);
    }
    
    trec.text.setPosition(Vector2f(trec.x, trec.y));
    trec.text.setCharacterSize(trec.chsize);
    trec.text.setColor(trec.c);
    trec.text.setString(trec.s);

    hanoi.draw(trec.text);

    hanoi.display();
}

Hanoi::~Hanoi(){}
