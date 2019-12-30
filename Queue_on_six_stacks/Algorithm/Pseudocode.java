package Algorithm;

import java.util.Vector;
import java.awt.*;
import javax.swing.*;

class Pseudocode extends JPanel
{
	private JFrame mainFrame, frame;
	private Controller controller;

	private Vector < String > code;

	Pseudocode(JFrame mainFrame, Controller controller)
	{
		this.controller = controller;
		this.mainFrame = mainFrame;

        frame = new JFrame("Pseudocode");
        frame.setSize(300, 500);
		frame.setLocation(mainFrame.getLocation().x + 800, mainFrame.getLocation().y);
		frame.addWindowListener(controller);
		frame.setResizable(false);
	}

	void init()
	{
		frame.setVisible(false);
		frame.add(this);
	}

	void toggle(boolean action)
	{
		if (frame.isVisible() != action)
		{
			frame.setVisible(action);

			if (action)
			{
				frame.setLocation(mainFrame.getLocation().x + 800, mainFrame.getLocation().y);
			}
		}
	}

	public void paint(Graphics g)
	{
		g.setColor(new Color(50, 50, 50));
		g.fillRect(0, 0, 300, 500);	
	}
}
