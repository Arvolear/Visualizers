package Algorithm;

import java.util.*;
import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
class Interface extends JPanel implements Runnable
{
    private JFrame frame;
    private Controller controller;
    private Sueue queue;

    private Grid grid;

    Interface(Controller controller, Sueue queue)
    {
        Element.setSpeed(5);

        this.controller = controller;
        this.queue = queue;

        frame = new JFrame();
        frame.setSize(800, 600);
		frame.setResizable(false);
        
        frame.addWindowListener(controller);
        frame.setVisible(true);

        grid = new Grid(frame, controller, queue);
       
        init();

        frame.add(this);
    }

    void init()
    {
        grid.init();
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
