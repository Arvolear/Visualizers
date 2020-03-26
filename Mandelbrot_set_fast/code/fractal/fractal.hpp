#pragma once

#include "../window/window.hpp"
#include "../framebuffer/colorbuffer.hpp"

#include <SOIL/SOIL.h>

#include <iostream>

using namespace std;

class Fractal
{
	private:
		Window* window;

		ColorBuffer* fractalBuffer;
		RenderQuad* fractalQuad;
		Shader* fractalShader;

		int screenShotNum;
		string outputDir;
		string prefix;

		bool checkEvents();
		void compute();
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

		double zoomAmount;
		double precisionAmount;

	public:
		Fractal();

		void play();

		~Fractal();
};
