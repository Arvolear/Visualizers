#include <random>

using namespace std;
    
static random_device rd;
static mt19937 gen(rd());
static uniform_real_distribution<> dis(0, 1);

static float getRandomNumber()
{
    return dis(gen);
}
