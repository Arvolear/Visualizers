package Algorithm;

import java.util.*;
import java.awt.*;
import javax.swing.*;

public class App implements Runnable
{
    private Sueue queue;
    private SpeedController speedController;
    private Controller controller;
    private Interface inter;
	private Menu menu;
    
	private JFrame frame;
	private Pane pane;

    public App()
    {
        frame = new JFrame("Queue on six stacks");
        frame.setSize(800, 600);
		frame.setResizable(false);
        

		pane = new Pane();

        controller = new Controller();
        queue = new Sueue();
        inter = new Interface(frame, pane, controller, queue);
		menu = new Menu(frame, pane, controller);
        speedController = new SpeedController(controller, inter.getGrid());
        
		frame.addWindowListener(controller);
        frame.setVisible(true);

		pane.setInter(inter);
		pane.setMenu(menu);

        frame.add(pane);
    }

    public void run()
    {
        Thread interThread = new Thread(inter, "Interface");
        interThread.start();

        Thread speedThread = new Thread(speedController, "Speed");
        speedThread.start();
        
        while (controller.isOpen())
        {
			while (true)
			{
				try
				{
					Thread.sleep(5);
				}
				catch (InterruptedException ex)
				{
					System.out.println("Error: " + ex);
				}

				if (controller.isStart())
				{
					menu.open();
					break;
				}
			}

			try
			{
				Thread.sleep(5);
			}
			catch (InterruptedException ex)
			{
				System.out.println("Error: " + ex);
			}

			if (controller.getWhat().equals("Push"))
			{
				if (inter.getGrid().getPushText().equals(""))
				{
					continue;
				}

				queue.push(inter.getGrid().getPushText());
			}
			else if (controller.getWhat().equals("Pop"))
			{
				if (queue.empty())
				{
					continue;
				}

				queue.pop();
			}

			controller.clear();
		}

		try
		{
			interThread.join();
			speedThread.join();
		}
		catch (InterruptedException ex)
		{
			System.out.println("Error: " + ex);
		}
	}
}
