#pragma once

//native
#include <climits>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>

//opengl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

class Global
{
    private:
        random_device rd;
        mt19937* gen;
        uniform_real_distribution < float >* dis;
        
    public:
        Global();

        string path(string p);
        
        float cutFloat(float from, int precision);

        float getRandomNumber();
        vec3 getRandomVec3();

        double toRads(double angle);
        double toDegs(double rads);

        unsigned int getTime() const;

        ~Global();
};
