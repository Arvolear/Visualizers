Algorithm = Complex.class FractalComputation.class Fractal.class Mandelbrot.class  
Graphics = Interface.class

CLASSES = Main.class $(addprefix Algorithm/, $(Algorithm)) $(addprefix Graphics/, $(Graphics))

### ALL ###

ALL: $(CLASSES) 

Main.class: Main.java
	javac Main.java

### ALGORITHM ###

Algorithm/FractalComputation.class: Algorithm/FractalComputation.java
	javac Algorithm/FractalComputation.java

Algorithm/Fractal.class: Algorithm/Fractal.java
	javac Algorithm/Fractal.java

Algorithm/Mandelbrot.class: Algorithm/Mandelbrot.java
	javac Algorithm/Mandelbrot.java

Algorithm/Complex.class: Algorithm/Complex.java
	javac Algorithm/Complex.java

### GRAPHICS ###

Graphics/Interface.class: Graphics/Interface.java
	javac Graphics/Interface.java

clean:
	rm -rf ./Main.class
	rm -rf ./Algorithm/*.class
	rm -rf ./Graphics/*.class
