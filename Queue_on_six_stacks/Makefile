Algorithm = App.class Interface.class Controller.class SpeedController.class Grid.class Sueue.class DrawableStack.class Element.class 

CLASSES = Main.class $(addprefix Algorithm/, $(Algorithm))

OUTPUTDIR = ./build 

### ALL ###

Main: $(CLASSES) 

Main.class: Main.java
	javac Main.java

### ALGORITHM ###

App.class: Algorithm/App.java
	javac -d $(OUTPUTDIR) Algorithm/App.java

Interface.class: Algorithm/Interface.java
	javac -d $(OUTPUTDIR) Algorithm/Interface.java

Controller.class: Algorithm/Controller.java
	javac -d $(OUTPUTDIR) Algorithm/Controller.java

SpeedController.class: Algorithm/SpeedController.java
	javac -d $(OUTPUTDIR) Algorithm/SpeedController.java

Grid.class: Algorithm/Grid.java
	javac -d $(OUTPUTDIR) Algorithm/Grid.java

Sueue.class: Algorithm/Sueue.java
	javac -d $(OUTPUTDIR) Algorithm/Sueue.java

DrawableStack.class: Algorithm/DrawableStack.java
	javac -d $(OUTPUTDIR) Algorithm/DrawableStack.java

Element.class: Algorithm/Element.java
	javac -d $(OUTPUTDIR) Algorithm/Element.java

clean:
	rm -rf Main.class
	rm -rf build/.*class
