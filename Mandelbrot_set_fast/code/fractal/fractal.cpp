#include "fractal.hpp"

Fractal::Fractal()
{
	window = new Window();

	fractalBuffer = new ColorBuffer();
	fractalBuffer->genBuffer(window->getRenderSize(), {{GL_RGBA16F, GL_RGBA, GL_FLOAT}});

	fractalQuad = new RenderQuad();
	fractalQuad->init();

	fractalShader = new Shader();
	fractalShader->loadShaders(global.path("code/shader/mandelbrotShader.vert"), global.path("code/shader/mandelbrotShader.frag"));

	gauss = new GaussianBlur < ColorBuffer >();
	gauss->genBuffer(window->getRenderSize(), {GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE});

	maxIterations = 70;
	maxAbs = 2.0;

	realBeg = -2.95;
	realEnd = 1.95;
	imagBeg = -1.2;
	imagEnd = 1.2;

	zoom = 1.0;
	realOffset = 0.0;
	imagOffset = 0.0;

	zoomAmount = 1.1;
	precisionAmount = 1.037;

	screenShotNum = 0;

	outputDir = "output/Mandelbrot/";
	prefix = "out0-";
}

bool Fractal::checkEvents()
{
	if (window->isKeyPressedOnce(GLFW_KEY_EQUAL))
	{
		cout << "Zoomin" << endl;
		vec2 point = window->getRenderMousePosition();
		vec2 size = window->getRenderSize();

        double realOld = ((point.x / size.x) * (realEnd - realBeg) + realBeg) / zoom;
        double imagOld = ((point.y / size.y) * (imagEnd - imagBeg) + imagBeg) / zoom;
		
		zoom *= zoomAmount;	
		maxIterations *= precisionAmount;
        
        double realNew = ((point.x / size.x) * (realEnd - realBeg) + realBeg) / zoom;
        double imagNew = ((point.y / size.y) * (imagEnd - imagBeg) + imagBeg) / zoom;

		realOffset -= realNew - realOld;
		imagOffset += imagNew - imagOld;

		return true;
	}

	if (window->isKeyPressedOnce(GLFW_KEY_MINUS))
	{
		cout << "Zoomout" << endl;

		zoom /= zoomAmount;
		maxIterations /= precisionAmount;

		return true;
	}

	return false;
}

void Fractal::compute()
{
	fractalBuffer->use();
	fractalBuffer->clear();

	fractalShader->use();

	fractalShader->setDouble("zoom", zoom);
	fractalShader->setDouble("realOffset", realOffset);
	fractalShader->setDouble("imagOffset", imagOffset);

	fractalShader->setInt("maxIterations", maxIterations);
	fractalShader->setDouble("maxAbs", maxAbs);

	fractalShader->setDouble("realBeg", realBeg);
	fractalShader->setDouble("realEnd", realEnd);
	fractalShader->setDouble("imagBeg", imagBeg);
	fractalShader->setDouble("imagEnd", imagEnd);
	
	fractalQuad->render(fractalShader);
}

void Fractal::blur()
{
	gauss->blur(fractalBuffer->getTexture(), 16.0, 2.0);
}

void Fractal::saveScreenShot()
{
	string output = outputDir + prefix + to_string(screenShotNum) + ".bmp";

	if (!SOIL_save_screenshot(global.path(output).data(), SOIL_SAVE_TYPE_BMP, 0, 0, window->getSize().x, window->getSize().y))
	{
		cout << "Error saving screenshot" << endl;
	}

	screenShotNum++;
}

void Fractal::play()
{
	compute();
	//blur();
	saveScreenShot();

	while (window->isOpen())
	{
		window->pollEvents();
	
		if (checkEvents())
		{
			compute();
			//blur();
			saveScreenShot();
		}

		window->render(fractalBuffer->getTexture());
		//window->render(gauss->getTexture());
	}
}

Fractal::~Fractal()
{
	delete fractalBuffer;
	delete fractalQuad;
	delete fractalShader;

	delete window;
}
