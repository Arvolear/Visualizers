#include "backend.h"
#include "meter.h"
#include "frontend.h"

using namespace std;
using namespace sf;

UI::UI(Field *f, Meter *m)
{
    field = f;
    meter = m;

    all._lin = -1;
    all._col = -1;
    all._amount = 100000;
    all._winSize = 2;
    all._visualize = 0;
}

UI::~UI()
{
    delete field;
    delete meter;
}

void UI::visualize()
{
    all._visualize = (all._visualize + 1) % 2;

    if (all._visualize)
    {
        all.texts[1].s = "Visualization Enabled";
        all.texts[1].x += 2;
    }
    else
    {
        all.texts[1].s = "Visualization Disabled";
        all.texts[1].x -= 2;
    }
}

void UI::count(RenderWindow &window)
{ 
    float sx = window.getSize().x;
    float sy = window.getSize().y;

    int size = sy;

    cout << size << endl;

    Image image = window.capture();
    image.saveToFile("./1.png");

    float relation = 1000.0 / sx; 

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {  
            Color pixel = image.getPixel(i, j);                

            if (pixel.r + pixel.g + pixel.b < 400)
                if (!field->getDot(i*relation, j*relation))
                {
                    field->setDot(i*relation, j*relation, 1);
                    if (all._winSize == 1)
                    {
                       for (int n = -1; n < 1; n++)
                            for (int m = -1; m < 1; m++)
                                field->setDot(i*relation + n, j*relation + m, 1);
                    }
                }
        }
    }

    for (int i = 0; i < all._amount; i++)
    {
        pair < int, int > a = field->randomDot(0, 0, 565, 564);

        bool in = field->calculatePixels(a.first, a.second);
                    
        if (all._visualize)
            simulate(window, a.first, a.second, in);
    }

    all.dots.clear();
    
    pair < int, pair < int, int > > M;
    M = meter->whatMeter();

    int ml = M.second.second;

    float sqarea = 565.0 / ml * 565.0 / ml;

    float dotsIn = field->displaydotsIn();
    field->dotsInNull();

    float fiarea = sqarea * dotsIn / float(all._amount);


    if (M.first == -4)
    {
        fiarea /= 10.0;

        all.texts[2].s = "Area: " + to_string(fiarea) + "(mm)";
    }
    if (M.first == -3)
    {
        all.texts[2].s = "Area: " + to_string(fiarea) + "(mm)";
    }
    if (M.first == -2)
    {
        all.texts[2].s = "Area: " + to_string(fiarea) + "(cm)";
    }
    if (M.first == -1)
    {
        all.texts[2].s = "Area: " + to_string(fiarea) + "(dm)";
    }
    if (M.first == 0)
    {
        all.texts[2].s = "Area: " + to_string(fiarea) + "(m)";
    }
    if (M.first == 1)
    {
        fiarea *= 10.0;

        all.texts[2].s = "Area: " + to_string(fiarea) + "(m)";
    }
    if (M.first == 2)
    {
        fiarea *= 100.0;

        all.texts[2].s = "Area: " + to_string(fiarea) + "(m)";
    }
    if (M.first == 3)
    {
        all.texts[2].s = "Area: " + to_string(fiarea) + "(km)";
    }
    if (M.first == 4)
    {
        fiarea *= 10.0;

        all.texts[2].s = "Area: " + to_string(fiarea) + "(km)";
    }
}

pair < float, float > UI::calculateRotation(float _fromCol, float _fromLin, float posx, float posy)
{
    float length = sqrt((_fromCol - posx) * (_fromCol - posx) + (_fromLin - posy) * (_fromLin - posy));

    float straight = posx - _fromCol;

    float cose;
    
    if (length)
    {
        cose = straight / length;
    }
    else
    {
        cose = 1;
    }

    float angle = acos(cose) * 180.0 / 3.141592;

    if (length)
    {
        return {length + 3, angle};
    }
    else
    {
        return {0, 0};
    }
}

void UI::lineDraw(RenderWindow &window, float _fromLin, float _fromCol)
{
    Vector2i pixelpos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelpos);
    
    int size = field->getSize();

    if (pos.x >= 10 && pos.x < size && pos.y >= 10 && pos.y < size)
    {    
        if (all._lin != -1 && all._col != -1)
        {
            if (_fromLin > pos.y && _fromCol > pos.x)
            {
                swap(pos.y, _fromLin);
                swap(pos.x, _fromCol);
            }
            else if (_fromLin > pos.y && _fromCol < pos.x)
            {
                swap(pos.x, _fromCol);
                swap(pos.y, _fromLin);
            }

            pair < float, float > a = calculateRotation(_fromCol, _fromLin, pos.x, pos.y);

            all.lines.push_back({_fromCol, _fromLin, a.first, 5, Color(200, 0, 0), a.second});
        }
    }
}

void UI::remLine(RenderWindow &window)
{
    int size = field->getSize();

    Vector2i pixelpos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelpos);

    if (pos.x >= 10 && pos.x < size && pos.y >= 10 && pos.y < size)
    {
        all._lin = pos.y;
        all._col = pos.x;
    }
}


void UI::Fill(RenderWindow &window)
{ 
    Vector2i pixelpos = Mouse::getPosition(window);
    Vector2f pos = window.mapPixelToCoords(pixelpos);
    
    float sx = window.getSize().x;
    float sy = window.getSize().y;

    int size = sy;

    cout << size << endl;

    Image image = window.capture();
    image.saveToFile("./1.png");

    float relation = 1000.0 / sx;

    int posx = pos.x;
    int posy = pos.y;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {  
            Color pixel = image.getPixel(i, j);                

            if (pixel.r + pixel.g + pixel.b < 400)
                if (!field->getDot(i*relation, j*relation))
                {
                    field->setDot(i*relation, j*relation, 1);
                    if (all._winSize == 1)
                    {
                       for (int n = -1; n < 1; n++)
                            for (int m = -1; m < 1; m++)
                                field->setDot(i*relation + n, j*relation + m, 1);
                    }
                }
        }
    }

    field->fillIn(posx, posy, 1);

    struct LINES M = all.lines[1];

    all.lines.clear();
    all.lines.push_back({0, 0, 565, 564, Color(240, 240, 240), 0});
    all.lines.push_back(M);

    for (int i = 0; i < size; i++)
    {
        float x;
        float y = i;
        float l;
        float w = 1;
        Color c;
        c = Color(200, 0, 0);
        float r = 0;

        bool f = false;

        for (int j = 0; j < size; j++)
        {
            if (field->getDot(i*relation, j*relation))
            { 
                if (!f)
                {
                    x = j;
                    f = true;
                }
            }
            
            if (!field->getDot(i*relation, j*relation) || j == size - 1)
            {
                if (f)
                {
                    l = j - x - 1;
                    f = false;
                    
                    all.lines.push_back({y*relation, x*relation, w*relation, l*relation, c, r});
                }
            }
        }
    }
}

void UI::simulate(RenderWindow &window, int _lin, int _col, bool _in)
{
    Color c;

    if (_in)
        c = Color(230, 218, 0);
    else
        c = Color(128, 0, 255);

    all.dots.push_back({float(_lin), float(_col), 1.0, 1.0, c, 0});

    if (all.dots.size() % (all._amount / 10) == 0)
        show(window);
}

void UI::whatAmount(RenderWindow &window, int _param, int _shift)
{
    int a = 0;

    if (all._amount <= 400000 && all._amount >= 0)
    {
        if (_param == 1)
        {
            a += 100;
            if (_shift)
            {
                a -= 100;
                a += 10000;
            }

            if (all._amount + a > 400000)
            {
                a = 400000 - all._amount;
            }
        }
        if (_param == -1)
        {
            a -= 100;
            if (_shift)
            {
                a += 100;
                a -= 10000;
            }

            if (all._amount + a < 0)
            {
                a = -all._amount;
            }
        }
    }
    all._amount += a;

    all.texts[3].s = "Dots Amount: " + to_string(all._amount);

    if (all._amount == 400000)
    {
        all.texts[3].c = Color(200, 0, 0);
    }
    else if (all._amount == 0)
    {
        all.texts[3].c = Color(0, 200, 0);
    }
    else
    {
        all.texts[3].c = Color(240, 240, 240);
    }
}

void UI::whatMeter(RenderWindow &window, int _param, int _shift)
{
    pair < int, pair < int, int > > M;

    if (!_shift)
        M = meter->calculateMeter(_param);
    else
        M = meter->calculateMeterShift(_param);

    all.lines[1].y = M.second.first + 158;
    all.lines[1].w = M.second.second;

    if (M.first == -4)
    {
        all.texts[0].s = "0.1(mm)";
    }
    if (M.first == -3)
    {
        all.texts[0].s = "1(mm)";
    }
    if (M.first == -2)
    {
        all.texts[0].s = "1(cm)";
    }
    if (M.first == -1)
    {
        all.texts[0].s = "1(dm)";
    }
    if (M.first == 0)
    {
        all.texts[0].s = "1(m)";
    }
    if (M.first == 1)
    {
        all.texts[0].s = "10(m)";
    }
    if (M.first == 2)
    {
        all.texts[0].s = "100(m)";
    }
    if (M.first == 3)
    {
        all.texts[0].s = "1(km)";
    }
    if (M.first == 4)
    {
        all.texts[0].s = "10(km)";
    }
}

void UI::clearSCR(RenderWindow &window)
{
    field->clearField();

    struct LINES M = all.lines[1];

    all.lines.clear();
    all.lines.push_back({0, 0, 565, 564, Color(240, 240, 240), 0});
    all.lines.push_back(M);
}

void UI::firstShow(RenderWindow &window)
{
    all.lines.push_back({0, 0, 565, 564, Color(240, 240, 240), 0});
    all.lines.push_back({600, 158, 10, 250, Color(230, 218, 0), 0});
    all.texts.push_back({"./fonts/G.ttf", "1(m)", 24, 620, 275, Color(230, 218, 0)});
    all.texts.push_back({"./fonts/G.ttf", "Visualization Disabled", 24, 670, 80, Color(128, 0, 255)});
    all.texts.push_back({"./fonts/G.ttf", "Area:", 24, 670, 500, Color(200, 0, 0)});
    all.texts.push_back({"./fonts/G.ttf", "Dots Amount: 100000", 20, 670, 460, Color(240, 240, 240)});
}

void UI::show(RenderWindow &window)
{
    window.clear(Color(0, 2, 31));


    struct LINES SHEET = all.lines[0];
    RectangleShape sheet;

    sheet.setPosition(SHEET.x, SHEET.y);
    sheet.setSize(Vector2f(SHEET.l, SHEET.w));
    sheet.setFillColor(SHEET.c);

    window.draw(sheet);
    
    struct LINES METERR = all.lines[1];
    RectangleShape meterr;

    meterr.setPosition(METERR.x, METERR.y);
    meterr.setSize(Vector2f(METERR.l, METERR.w));
    meterr.setFillColor(METERR.c);

    window.draw(meterr);


    vector < LINES > REDONCE = all.lines;

    for (int i = 2; i < REDONCE.size(); i++)
    {
        RectangleShape redonce;

        redonce.setPosition(REDONCE[i].x, REDONCE[i].y);
        redonce.setSize(Vector2f(REDONCE[i].l, REDONCE[i].w));
        redonce.setFillColor(REDONCE[i].c);
        redonce.setRotation(REDONCE[i].r);

        window.draw(redonce);
    }

    vector < DOTS > PURONCE = all.dots;

    for (int i = 0; i < PURONCE.size(); i++)
    {
        RectangleShape puronce;

        puronce.setPosition(PURONCE[i].x, PURONCE[i].y);
        puronce.setSize(Vector2f(PURONCE[i].l, PURONCE[i].w));
        puronce.setFillColor(PURONCE[i].c);
        puronce.setRotation(PURONCE[i].r);

        window.draw(puronce);
    }


    vector < TEXTS > WRITE = all.texts;

    for (int i = 0; i < WRITE.size(); i++)
    {
        Text write;
        Font style;

        style.loadFromFile(WRITE[i].font);
        write.setFont(style);
        write.setString(WRITE[i].s);
        write.setCharacterSize(WRITE[i].chsize);
        write.setPosition(WRITE[i].x, WRITE[i].y);
        write.setColor(WRITE[i].c);

        window.draw(write);
    }

    window.display();
}

void UI::start()
{
    RenderWindow window(VideoMode(1000, 565), "Area", 4);
    ContextSettings settings;

    window.setFramerateLimit(120);

    firstShow(window);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (Mouse::isButtonPressed(Mouse::Left))
            {
                lineDraw(window, all._lin, all._col);
                remLine(window);
            }
            if (!Mouse::isButtonPressed(Mouse::Left))
            {
                all._lin = -1;
                all._col = -1;
            }
            if (!Keyboard::isKeyPressed(Keyboard::LShift))
                if (Mouse::isButtonPressed(Mouse::Right))
                {
                    Fill(window);
                }
            if (Keyboard::isKeyPressed(Keyboard::LShift))
                if (Mouse::isButtonPressed(Mouse::Right))
                {
                    count(window);
                }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == 21)
                    visualize();

                if (event.key.code == 2)
                    clearSCR(window);

                if (event.key.code == 27)
                {
                    window.setSize(Vector2u(640, 362));
                    all._winSize = 1;
                }
                if (event.key.code == 28)
                {
                    window.setSize(Vector2u(1000, 565)); 
                    all._winSize = 2;
                }
                if (event.key.code == 29)
                {
                    window.setSize(Vector2u(1920, 1085)); 
                    all._winSize = 3;
                }
                if (event.key.code == 71)
                {
                    if (!Keyboard::isKeyPressed(Keyboard::LShift))
                        whatAmount(window, -1, 0);

                    if (Keyboard::isKeyPressed(Keyboard::LShift))
                        whatAmount(window, -1, 1);
                }
                if (event.key.code == 72)
                {
                    if (!Keyboard::isKeyPressed(Keyboard::LShift))
                        whatAmount(window, 1, 0);

                    if (Keyboard::isKeyPressed(Keyboard::LShift))
                        whatAmount(window, 1, 1);
                }
                if (event.key.code == 73)
                {
                    if (!Keyboard::isKeyPressed(Keyboard::LShift))
                        whatMeter(window, -1, 0);

                    if (Keyboard::isKeyPressed(Keyboard::LShift))
                        whatMeter(window, -1, 1);
                }
                if (event.key.code == 74)
                {
                    if (!Keyboard::isKeyPressed(Keyboard::LShift))
                        whatMeter(window, 1, 0);

                    if (Keyboard::isKeyPressed(Keyboard::LShift))
                        whatMeter(window, 1, 1);
                }
                //cout << event.key.code << endl;
            }
        }

        show(window);
    }
}
