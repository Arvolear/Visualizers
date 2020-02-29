package Algorithm;

import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.util.ArrayList;

@SuppressWarnings("serial")
class Interface extends JPanel implements Runnable
{
    private JFrame frame;
	private Pane pane;
    private Controller controller;
    private ArrayList < Sueue > queues;
	private Pseudocode pseudocode;

    private Grid grid;

    Interface(JFrame frame, Pane pane, Controller controller, ArrayList < Sueue > queues, Pseudocode pseudocode)
    {
		this.frame = frame;
		this.pane = pane;
        this.controller = controller;
        this.queues = queues;
		this.pseudocode = pseudocode;

        grid = new Grid(pane, controller, queues);
		
		init();
    }

    void init()
    {
        grid.init();
		pseudocode.init();

		pane.add(this, 10);
    }

	void unhide()
	{
		grid.unhide();
	}

    public void paint(Graphics g)
    {
        g.setColor(new Color(30, 30, 30));
        g.fillRect(0, 0, 800, 600);

        queues.get(queues.size() - 1).paint(g);
        grid.paint(g);

		pseudocode.update();
    }

    public void run()
    {
        while (controller.isOpen())
        {
            try
            {
                Thread.sleep(5);
            }
            catch (InterruptedException ex)
            {
                System.out.println("Error: " + ex);
            }

            grid.update();

            frame.revalidate();
            frame.repaint();
        }
    }

    Grid getGrid()
    {
        return grid;
    }
}
