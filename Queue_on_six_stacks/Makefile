Algorithm = App.class Interface.class Controller.class SpeedController.class Grid.class Sueue.class DrawableStack.class Element.class 

CLASSES = Main.class $(addprefix Algorithm/, $(Algorithm))

OUTPUTDIR = ./build 

### ALL ###

Main: $(CLASSES) 

Main.class: Main.java
	javac Main.java

### ALGORITHM ###

$(OUTPUTDIR)/App.class: Algorithm/App.java
	javac Algorithm/App.java

$(OUTPUTDIR)/Interface.class: Algorithm/Interface.java
	javac Algorithm/Interface.java

$(OUTPUTDIR)/Controller.class: Algorithm/Controller.java
	javac Algorithm/Controller.java

$(OUTPUTDIR)/SpeedController.class: Algorithm/SpeedController.java
	javac Algorithm/SpeedController.java

$(OUTPUTDIR)/Grid.class: Algorithm/Grid.java
	javac Algorithm/Grid.java

$(OUTPUTDIR)/Sueue.class: Algorithm/Sueue.java
	javac Algorithm/Sueue.java

$(OUTPUTDIR)/DrawableStack.class: Algorithm/DrawableStack.java
	javac Algorithm/DrawableStack.java

$(OUTPUTDIR)/Element.class: Algorithm/Element.java
	javac Algorithm/Element.java

clean:
	rm -rf Main.class
	rm -rf build/.*class
