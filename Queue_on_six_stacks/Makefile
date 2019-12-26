Algorithm = App.class Interface.class Controller.class SpeedController.class Grid.class Sueue.class DrawableStack.class Element.class 

CLASSES = Main.class $(Algorithm)

### ALL ###

ALL: $(CLASSES) 

Main.class: Main.java
	javac Main.java

### ALGORITHM ###

App.class: Algorithm/App.java
	javac Algorithm/App.java

Interface.class: Algorithm/Interface.java
	javac Algorithm/Interface.java

Controller.class: Algorithm/Controller.java
	javac Algorithm/Controller.java

SpeedController.class: Algorithm/SpeedController.java
	javac Algorithm/SpeedController.java

Grid.class: Algorithm/Grid.java
	javac Algorithm/Grid.java

Sueue.class: Algorithm/Sueue.java
	javac Algorithm/Sueue.java

DrawableStack.class: Algorithm/DrawableStack.java
	javac Algorithm/DrawableStack.java

Element.class: Algorithm/Element.java
	javac Algorithm/Element.java

clean:
	rm -rf ./Main.class
	rm -rf ./Algorithm/*.class
