package Algorithm;

import java.util.*;
import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
class Interface extends JPanel implements Runnable
{
    private JFrame frame;
	private Pane pane;
    private Controller controller;
    private Sueue queue;

    private Grid grid;

    Interface(JFrame frame, Pane pane, Controller controller, Sueue queue)
    {
		this.frame = frame;
		this.pane = pane;
        this.controller = controller;
        this.queue = queue;

        grid = new Grid(pane, controller, queue);
		
		init();
    }

    void init()
    {
        grid.init();
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

        queue.paint(g);
        grid.paint(g);
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
