.PHONY: release all clean cleanall

FLAGS = -std=c++11 -Wall -O3

LIBS = -lGLEW -lGL -lSOIL -lglfw3 -lX11 -lpthread -ldl 

RELEASE = -Wl,-rpath,./lib

INPUTDIR = ./code
OUTPUTDIR = ./build

MAIN = main.o 
GLOBAL = global.o gaussianblur.o
SHADER = shader.o 
FRAMEBUFFER = framebuffer.o colorbuffer.o
WINDOW = window.o glfwevents.o renderquad.o 
FRACTAL = fractal.o

OBJECTFILES = $(addprefix $(OUTPUTDIR)/, $(MAIN) $(GLOBAL) $(SHADER) $(FRAMEBUFFER) $(WINDOW) $(FRACTAL)) 

### ALL ###

all: Zoomer

Zoomer: $(OBJECTFILES)
	g++ -o Zoomer $(OBJECTFILES) $(LIBS) $(FLAGS) 

### RELEASE ###

release: $(OBJECTFILES)
	g++ -o Zoomer $(OBJECTFILES) $(RELEASE) $(LIBS) $(FLAGS)

### MAIN ###

$(OUTPUTDIR)/main.o: $(INPUTDIR)/main.cpp
	g++ -c $(INPUTDIR)/main.cpp -o $@ $(FLAGS)

### GLOBAL ###

$(OUTPUTDIR)/global.o: $(INPUTDIR)/global/global.cpp $(INPUTDIR)/global/global.hpp
	g++ -c $(INPUTDIR)/global/global.cpp -o $@ $(FLAGS)

$(OUTPUTDIR)/gaussianblur.o: $(INPUTDIR)/global/gaussianblur.cpp $(INPUTDIR)/global/gaussianblur.hpp
	g++ -c $(INPUTDIR)/global/gaussianblur.cpp -o $@ $(FLAGS)

### SHADER ###

$(OUTPUTDIR)/shader.o: $(INPUTDIR)/shader/shader.cpp $(INPUTDIR)/shader/shader.hpp
	g++ -c $(INPUTDIR)/shader/shader.cpp -o $@ $(FLAGS)

### FRAMEBUFFER ###

$(OUTPUTDIR)/framebuffer.o: $(INPUTDIR)/framebuffer/framebuffer.cpp $(INPUTDIR)/framebuffer/framebuffer.hpp
	g++ -c $(INPUTDIR)/framebuffer/framebuffer.cpp -o $@ $(FLAGS)

$(OUTPUTDIR)/colorbuffer.o: $(INPUTDIR)/framebuffer/colorbuffer.cpp $(INPUTDIR)/framebuffer/colorbuffer.hpp
	g++ -c $(INPUTDIR)/framebuffer/colorbuffer.cpp -o $@ $(FLAGS)

### WINDOW ###

$(OUTPUTDIR)/window.o: $(INPUTDIR)/window/window.cpp $(INPUTDIR)/window/window.hpp
	g++ -c $(INPUTDIR)/window/window.cpp -o $@ $(FLAGS)

$(OUTPUTDIR)/glfwevents.o: $(INPUTDIR)/window/glfwevents.cpp $(INPUTDIR)/window/glfwevents.hpp
	g++ -c $(INPUTDIR)/window/glfwevents.cpp -o $@ $(FLAGS)

$(OUTPUTDIR)/renderquad.o: $(INPUTDIR)/window/renderquad.cpp $(INPUTDIR)/window/renderquad.hpp
	g++ -c $(INPUTDIR)/window/renderquad.cpp -o $@ $(FLAGS)

### FRACTAL ###

$(OUTPUTDIR)/fractal.o: $(INPUTDIR)/fractal/fractal.cpp $(INPUTDIR)/fractal/fractal.hpp
	g++ -c $(INPUTDIR)/fractal/fractal.cpp -o $@ $(FLAGS)

### CLEAN ###

clean:
	rm -rf $(OUTPUTDIR)/*.o

### CLEANALL ###

cleanall:
	rm -rf Zoomer
	rm -rf $(OUTPUTDIR)/*.o
