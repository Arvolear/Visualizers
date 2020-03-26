#include "global.hpp"

Global::Global() 
{
    gen = new mt19937(rd());
    dis = new uniform_real_distribution < float >(0.0, 1.0);
}

string Global::path(string p)
{
    char realPath[PATH_MAX];
    char* ptr;

    ptr = realpath(p.c_str(), realPath);

    /* error */
    if (ptr)
    {
        return ptr;
    }

    return {realPath};
}

float Global::cutFloat(float from, int precision)
{
    stringstream ss;

    ss << fixed << setprecision(precision);

    ss << from;

    return stof(ss.str());
}


float Global::getRandomNumber()
{
    return (*dis)(*gen);
}

vec3 Global::getRandomVec3()
{
    return vec3((*dis)(*gen), (*dis)(*gen), (*dis)(*gen));
}

double Global::toRads(double angle)
{
    return angle / 180.0 * 3.14159265;
}

double Global::toDegs(double rads)
{
    return rads * 180.0 / 3.14159265;
}

unsigned int Global::getTime() const
{
    auto now = chrono::system_clock::now();
    unsigned long long time = chrono::duration_cast < chrono::milliseconds >(now.time_since_epoch()).count();

    return time % 1000000;
}

Global::~Global() 
{
    delete gen;
    delete dis;
}
