#include "fractal/fractal.hpp"

int main()
{
	Fractal* F = new Fractal();

	F->play();

    delete F;

    return 0;
}
