package Algorithm;

import java.util.Random;

class ElementClearer implements Runnable
{
	private Element elem;

	ElementClearer(Element elem)
	{
		this.elem = elem;
	}

	public void run()
	{
		double angle = Math.random() * 2 * 3.141592;
		
		double newX = 400 + 550 * Math.cos(angle); 	
		double newY = 300 + 550 * Math.sin(angle);

		elem.moveNoAxis((int)newX, (int)newY);
	}
}
