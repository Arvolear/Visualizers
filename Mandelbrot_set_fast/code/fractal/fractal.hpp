#pragma once

#include "../window/window.hpp"
#include "../framebuffer/colorbuffer.hpp"
#include "../global/gaussianblur.hpp"
#include "../global/gaussianblur.cpp"

#include <SOIL/SOIL.h>

#include <iostream>
#include <stack>

using namespace std;

class Fractal
{
	private:
		Window* window;

		ColorBuffer* fractalBuffer;
		RenderQuad* fractalQuad;
		Shader* fractalShader;

		GaussianBlur < ColorBuffer >* gauss; 

		int screenShotNum;
		string outputDir;
		string prefix;

		bool isBlur;

		double sensitivity;

		bool checkEvents();
		void compute();
		void blur();
		void saveScreenShot();

		int maxIterations;
		double maxAbs;

		double realBeg;
		double realEnd;
		double imagBeg;
		double imagEnd;

		double zoom;
		double realOffset;
		double imagOffset;

		stack < pair < double, double > > unZoomUndo;

		double zoomAmount;
		double precisionAmount;

	public:
		Fractal();

		void play();

		~Fractal();
};
