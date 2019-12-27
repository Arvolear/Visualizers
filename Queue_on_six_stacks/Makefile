Algorithm = App.class Interface.class Controller.class SpeedController.class Grid.class Sueue.class DrawableStack.class Element.class 

CLASSES = Main.class $(addprefix Algorithm/, $(Algorithm))

### ALL ###

ALL: $(CLASSES) 

Main.class: Main.java
	javac Main.java

### ALGORITHM ###

Algorithm/App.class: Algorithm/App.java
	javac Algorithm/App.java

Algorithm/Interface.class: Algorithm/Interface.java
	javac Algorithm/Interface.java

Algorithm/Controller.class: Algorithm/Controller.java
	javac Algorithm/Controller.java

Algorithm/SpeedController.class: Algorithm/SpeedController.java
	javac Algorithm/SpeedController.java

Algorithm/Grid.class: Algorithm/Grid.java
	javac Algorithm/Grid.java

Algorithm/Sueue.class: Algorithm/Sueue.java
	javac Algorithm/Sueue.java

Algorithm/DrawableStack.class: Algorithm/DrawableStack.java
	javac Algorithm/DrawableStack.java

Algorithm/Element.class: Algorithm/Element.java
	javac Algorithm/Element.java

clean:
	rm -rf ./Main.class
	rm -rf ./Algorithm/*.class
