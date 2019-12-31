package Algorithm;

import java.util.*;
import java.awt.*;
import javax.swing.*;

public class App implements Runnable
{
    private Sueue queue;
    private DynamicController dynamicController;
    private Controller controller;
    private Interface inter;
	private Menu menu;
	private Pseudocode pseudocode;
    
	private JFrame frame;
	private Pane pane;

    public App()
    {
        frame = new JFrame("Queue on six stacks");
        frame.setSize(800, 600);
		frame.setLocation(100, 50);
		frame.setResizable(false);
        
		pane = new Pane();

        controller = new Controller();
		pseudocode = new Pseudocode(frame, controller);
        queue = new Sueue(pseudocode);
        inter = new Interface(frame, pane, controller, queue, pseudocode);
		menu = new Menu(frame, pane, controller);
        dynamicController = new DynamicController(controller, inter.getGrid(), pseudocode);
        
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

        Thread dynamicThread = new Thread(dynamicController, "Dynamic");
        dynamicThread.start();
        
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
					inter.unhide();
					pane.setStart();
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
				if (!inter.getGrid().getPushText().equals(""))
				{
					queue.push(inter.getGrid().getPushText());
				}
			}
			else if (controller.getWhat().equals("Pop"))
			{
				if (!queue.empty())
				{
					queue.pop();
				}
			}

			controller.clear();
		}

		try
		{
			interThread.join();
			dynamicThread.join();
		}
		catch (InterruptedException ex)
		{
			System.out.println("Error: " + ex);
		}
	}
}
