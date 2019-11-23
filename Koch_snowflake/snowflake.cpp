#include "snowflake.h"

using namespace std;
using namespace std;

Koch::Koch(int n, double w, double h)
{
    depth = n;
    width = w;
    height = h;
    area = w*w * sqrt(3) / 4.0;
    first_area = w*w * sqrt(3) / 4.0;
}

void Koch::init()
{
    lines.resize(3);

    for (int i = 0; i < 3; i++)
    {
        lines[i].w = width;
        lines[i].h = height;
        lines[i].c = Color(255, 255, 255);
        lines[i].angle = (360 - 120 * i) % 360;

        if (i == 0)
        {
            lines[i].x = double(960 - width / 2.0);
            lines[i].y = 540 + ((sqrt((width * width) - (width / 2.0) * (width / 2.0))) / 3.0);
        }
        else if (i == 1)
        {
            lines[i].x = lines[0].x + lines[0].w;
            lines[i].y = lines[0].y;
        }
        else
        {
            double radangle = lines[i - 1].angle * 3.141592 / 180.0;

            double endx = lines[i - 1].x + lines[i - 1].w * cos(radangle);
            double endy = lines[i - 1].y + lines[i - 1].w * sin(radangle);

            lines[i].x = endx;
            lines[i].y = endy; 
        }
    }

    tarea.font.loadFromFile("./fonts/digital-7.ttf");
    tarea.text.setFont(tarea.font);
    tarea.x = 1500;
    tarea.y = 50;
    tarea.chsize = 64;
    tarea.c = Color::Yellow;
}

void Koch::recursion(RenderWindow &koch, int d, vector < S > l)
{
    vector < S > temp;

    if (d == depth)
        return;

    for (size_t i = 0; i < l.size(); i++)
    {
        double radangle = l[i].angle * 3.141592 / 180.0;

        double endx = l[i].x + l[i].w * cos(radangle);
        double endy = l[i].y + l[i].w * sin(radangle);

        double newx1 = (l[i].x + (1 / 2.0) * endx) / (1 + (1 / 2.0));
        double newy1 = (l[i].y + (1 / 2.0) * endy) / (1 + (1 / 2.0));

        S s1;
        s1.x = l[i].x;
        s1.y = l[i].y;
        s1.w = l[i].w / 3.0;
        s1.h = l[i].h / 1.5;
        s1.c = Color(255, 255, 255);
        s1.angle = l[i].angle;

        temp.push_back(s1);

        S s2;
        s2.x = newx1;
        s2.y = newy1;
        s2.w = l[i].w / 3.0;
        s2.h = l[i].h / 1.5;
        s2.c = Color(255, 255, 255);
        s2.angle = (l[i].angle + 60) % 360;

        temp.push_back(s2);

        double radangle2 = s2.angle * 3.141592 / 180.0;
        double newx2 = s2.x + s2.w * cos(radangle2);
        double newy2 = s2.y + s2.w * sin(radangle2);
            
        S s3;
        s3.x = newx2;
        s3.y = newy2;
        s3.w = l[i].w / 3.0;
        s3.h = l[i].h / 1.5;
        s3.c = Color(255, 255, 255);
        s3.angle = (l[i].angle - 60) % 360;

        temp.push_back(s3);
           
        double radangle3 = s3.angle * 3.141592 / 180.0;
        double newx3 = s3.x + s3.w * cos(radangle3);
        double newy3 = s3.y + s3.w * sin(radangle3);

        S s4;
        s4.x = newx3;
        s4.y = newy3;
        s4.w = l[i].w / 3.0;
        s4.h = l[i].h / 1.5;
        s4.c = Color(255, 255, 255);
        s4.angle = l[i].angle;

        temp.push_back(s4);
    }
        
    lines.clear();
    lines = temp;

    show(koch);

    int d1 = d;
    d1++;
    double a = first_area;

    while (d1)
    {
        a *= (1 / 9.0);
        d1--;
    }

    a *= l.size();

    area += a;
    recursion(koch, ++d, temp);
}

void Koch::draw()
{
    RenderWindow koch(VideoMode(1920, 1080), "Koch");

    koch.setFramerateLimit(2);

    init();
    show(koch);

    recursion(koch, 0, lines);

    tarea.s = to_string(area);

    while (koch.isOpen())
    {
        Event event;

        while (koch.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                koch.close();
                return;
            }
        }

        show(koch);
    }
}

void Koch::show(RenderWindow &koch)
{
    koch.clear();

    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i].line.setFillColor(lines[i].c);
        lines[i].line.setPosition(Vector2f(lines[i].x, lines[i].y));
        lines[i].line.setSize(Vector2f(lines[i].w, lines[i].h));
        lines[i].line.setOrigin(0, lines[i].h / 2.0);
        lines[i].line.setRotation(lines[i].angle);
    

        koch.draw(lines[i].line);
    }
        
    tarea.text.setPosition(Vector2f(tarea.x, tarea.y));
    tarea.text.setCharacterSize(tarea.chsize);
    tarea.text.setColor(tarea.c);
    tarea.text.setString(tarea.s);

    koch.draw(tarea.text);

    koch.display();
}

Koch::~Koch(){};
